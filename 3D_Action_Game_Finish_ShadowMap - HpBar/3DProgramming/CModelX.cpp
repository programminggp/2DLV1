#include "glew.h"
#include "glut.h"
#include "CModelX.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h>	//文字列関数のインクルード


void CModelX ::Load(char *file) {
	//
	//ファイルサイズを取得する
	//
	FILE *fp;	//ファイルポインタ変数の作成
	fp = fopen(file, "rb");	//ファイルをオープンする
	if (fp == NULL) {	//エラーチェック
		printf("fopen error\n");
		return;
	}
	//ファイルの最後へ移動
	fseek(fp, 0L, SEEK_END);
	//ファイルサイズの取得
	int size = ftell(fp);
	//ファイルサイズ+1バイト分の領域を確保
	char *buf = mpPointer = new char[size + 1];
	//ファイルの先頭へ移動
	fseek(fp, 0L, SEEK_SET);
	//確保した領域にファイルサイズ分データを読み込む
	fread(buf, size, 1, fp);
	//最後に\0を設定する（文字列の終端）
	buf[size] = '\0';
	fclose(fp);	//ファイルをクローズする

	//printf("%s", buf);

	//文字列の最後まで繰り返し
	while (*mpPointer != '\0') {
		GetToken();	//単語の取得
		//template 読み飛ばし
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//Material の時
		else if (strcmp(mToken, "Material") == 0) {
			AddMaterial(this, new CMaterial());
		}
		//単語がFrameの場合
		else if (strcmp(mToken, "Frame") == 0) {
			//フレーム名取得
			GetToken();
			if (strchr(mToken, '{')) {
				//フレーム名なし：スキップ
				SkipNode();
				GetToken(); //}
			}
			else {
				if (mFrame.size()) {
					//フレームが無ければ
					if (FindFrame(mToken) == 0) {
						//フレームを作成する
						mFrame[0]->mChild.push_back(new CModelXFrame(this));
					}
				}
				else {
					mFrame.push_back(new CModelXFrame());
					mFrame[0]->mpName = new char[1];
					mFrame[0]->mpName[0] = '\0';
					mFrame[0]->mChild.push_back(new CModelXFrame(this));
				}
					////フレームを作成する
					//p->mChild.push_back(
					//	new CModelXFrame(this));
			}

		}
		//単語がAnimationSetの場合
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}

	SAFE_DELETE_ARRAY(buf);	//確保した領域を開放する
	//スキンウェイトのフレーム番号設定
	SetSkinWeightFrameIndex();

	//37
	//頂点バッファの作成
	for (int i = 0; i < mFrame.size(); i++) {
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			mFrame[i]->mMesh.CreateVertexBuffer();
		}
	}
	//スキンマトリックスのエリア作成
	mpSkinningMatrix = new CMatrix44[mFrame.size()];
	//シェーダー読み込み
	mShader.load("shadow.vert", "shadow.flag");
}
/*
GetToken
文字列データから、単語を1つ取得する
*/
void CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	//空白( )タブ(\t)改行(\r)(\n)，；”以外の文字になるまで読み飛ばす
	while (*p != '\0' && strchr(" \t\r\n,;\"", *p)) p++;

	if (*p == '{' || *p == '}') {
		//{または}ならmTokenに代入し次の文字へ
		*q++ = *p++;
	}
	else {
		//空白( )タブ(\t)改行(\r)(\n)，；”}の文字になるまでmTokenに代入する
		while (*p != '\0' && !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0';	//mTokenの最後に\0を代入
	mpPointer = p;	//次の読み込むポイントを更新する
	//もしmTokenが//の場合は、コメントなので改行まで読み飛ばす
	if (!strcmp("//", mToken)) {
		//改行まで読み飛ばす
		while (*p != '\0' && !strchr("\r\n", *p)) p++;
		//読み込み位置の更新
		mpPointer = p;
		//単語を取得する（再帰呼び出し）
		GetToken();
	}
}

/*
SkipNode
ノードを読み飛ばす
*/
void CModelX::SkipNode() {
	//文字が終わったら終了
	while (*mpPointer != '\0') {
		GetToken();	//次の単語取得
		//{が見つかったらループ終了
		if (strchr(mToken, '{')) break;
	}
	int count = 1;
	//文字が終わるか、カウントが0になったら終了
	while (*mpPointer != '\0' && count > 0) {
		GetToken();	//次の単語取得
		//{を見つけるとカウントアップ
		if (strchr(mToken, '{')) count++;
		//}を見つけるとカウントダウン
		else if (strchr(mToken, '}')) count--;
	}
}

/*
CModelXFrame
model：CModelXインスタンスへのポインタ
フレームを作成する
読み込み中にFrameが見つかれば、フレームを作成し、
子フレームに追加する
*/
CModelXFrame::CModelXFrame(CModelX* model) {
	//現在のフレーム配列の要素数を取得し設定する
	mIndex = model->mFrame.size();
	//CModelXのフレーム配列に追加する
	model->mFrame.push_back(this);
	//変換行列を単位行列にする
	mTransformMatrix.identity();
	//次の単語（フレーム名の予定）を取得する
//	model->GetToken(); // frame name
	//フレーム名分エリアを確保する
	mpName = new char[strlen(model->mToken) + 1];
	//フレーム名をコピーする
	strcpy(mpName, model->mToken);
	//次の単語（{の予定）を取得する
	model->GetToken();  // {
	//文字が無くなったら終わり
	while (*model->mpPointer != '\0') {
		//次の単語取得
		model->GetToken(); // Frame
		//}かっこの場合は終了
		if (strchr(model->mToken, '}')) break;
		//新なフレームの場合は、子フレームに追加
		if (strcmp(model->mToken, "Frame") == 0) {
			model->GetToken(); //}
			if (strchr(model->mToken, '{')) {
				//フレーム名なし：スキップ
				model->SkipNode();
				model->GetToken(); //}
			}
			else {
				//フレームが無ければ
				if (model->FindFrame(model->mToken) == 0) {
					//フレームを作成し、子フレームの配列に追加
					mChild.push_back(new CModelXFrame(model));
				}
			}
			////フレームを作成し、子フレームの配列に追加
			//mChild.push_back(
			//	new CModelXFrame(model));
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0) {
			model->GetToken(); // {
			for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.f); i++) {
				mTransformMatrix.f[i] = model->GetFloatToken();
			}
			model->GetToken(); // }
		}
		else if (strcmp(model->mToken, "Mesh") == 0) {
			mMesh.Init(model);
		}
		else {
			//上記以外の要素は読み飛ばす
			model->SkipNode();
		}
	}
}
/*
GetFloatToken
単語を浮動小数点型のデータで返す
*/
float CModelX::GetFloatToken() {
	GetToken();
	//atof
	//文字列をfloat型へ変換
	return atof(mToken);
}
/*
GetIntToken
単語を整数型のデータで返す
*/
int CModelX::GetIntToken() {
	GetToken();
	return atoi(mToken);
}
/*
Init
Meshのデータを取り込む
*/
void CMesh::Init(CModelX *model) {
	model->GetToken();	// { or 名前
	if (!strchr(model->mToken, '{')) {
		//名前の場合、次が{
		model->GetToken();	// {
	}
	//頂点数の取得
	mVertexNum = model->GetIntToken();
#ifdef _DEBUG
//	printf("VertexNum:%d\n", mVertexNum);
#endif
	//頂点数分エリア確保
	mpVertex = new CVector3[mVertexNum];
	mpAnimateVertex = new CVector3[mVertexNum];
	//頂点数分データを取り込む
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].x = model->GetFloatToken();
		mpVertex[i].y = model->GetFloatToken();
		mpVertex[i].z = model->GetFloatToken();
#ifdef _DEBUG
//		printf("%12f %12f %12f \n", mpVertex[i].x, mpVertex[i].y, mpVertex[i].z);
#endif
	}
	mFaceNum = model->GetIntToken();	//面数読み込み
#ifdef _DEBUG
//	printf("FaceNum:%d\n", mFaceNum);
#endif
	//頂点数は1面に3頂点
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3) {
		model->GetToken();	//頂点数読み飛ばし
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
#ifdef _DEBUG
//		printf("%3d %3d %3d \n", mpVertexIndex[i], mpVertexIndex[i+1], mpVertexIndex[i+2]);
#endif
	}
	//文字が無くなったら終わり
	while (model->mpPointer != '\0') {
		model->GetToken();	//MeshNormals
		//}かっこの場合は終了
		if (strchr(model->mToken, '}'))
			break;
		if (strcmp(model->mToken, "MeshNormals") == 0) {
			model->GetToken();	// {
			//法線データ数を取得
			mNormalNum = model->GetIntToken();
			//法線のデータを配列に取り込む
			CVector3 *pNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i++) {
				pNormal[i].x = model->GetFloatToken();
				pNormal[i].y = model->GetFloatToken();
				pNormal[i].z = model->GetFloatToken();
			}
			//法線数=面数×３
			mNormalNum = model->GetIntToken() * 3; //FaceNum
			int ni;
			//頂点毎に法線データを設定する
			mpNormal = new CVector3[mNormalNum];
			mpAnimateNormal = new CVector3[mNormalNum];

			for (int i = 0; i < mNormalNum; i += 3) {
				model->GetToken(); // 3
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 1] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[] pNormal;
			model->GetToken();	// }
		}
		// MeshMaterialListのとき
		else if (strcmp(model->mToken, "MeshMaterialList") == 0) {
			model->GetToken(); // {
			// Materialの数
			mMaterialNum = model->GetIntToken();
			// FaceNum
			mMaterialIndexNum = model->GetIntToken();
			//マテリアルインデックスの作成
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++) {
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//マテリアルデータの作成
			for (int i = 0; i < mMaterialNum; i++) {
				model->GetToken();	// Material
				if (strcmp(model->mToken, "Material") == 0) {
					CMaterial *p = new CMaterial();
					model->AddMaterial(model, p);
					mMaterial.push_back(p);
				}
				else {
					// {  既出
					model->GetToken();	//MaterialName
					mMaterial.push_back(
						model->FindMaterial(model->mToken)); model->GetToken();	// }
				}
			}
			model->GetToken();	// } //End of MeshMaterialList
		}
		//SkinWeightsのとき
		else if (strcmp(model->mToken, "SkinWeights") == 0) {
			//CSkinWeightsクラスのインスタンスを作成し、配列に追加
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		//テクスチャ座標の時
		else if (strcmp(model->mToken, "MeshTextureCoords") == 0) {
			model->GetToken();	// {
			//テクスチャ座標数を取得
			int textureCoordsNum = model->GetIntToken();
			//テクスチャ座標のデータを配列に取り込む
			mpTextureCoords = new CVector2[textureCoordsNum];
			for (int i = 0; i < textureCoordsNum; i++) {
				mpTextureCoords[i].x = model->GetFloatToken();
				mpTextureCoords[i].y = model->GetFloatToken();
			}
			model->GetToken();	// }
		}
		else {
			//以外のノードは読み飛ばし
			model->SkipNode();
		}
	}
#ifdef _DEBUG
	//printf("NormalNum:%d\n", mNormalNum);
	//for (int i = 0; i < mNormalNum; i++) {
	//	printf("%12f %12f %12f \n", mpNormal[i].x, mpNormal[i].y, mpNormal[i].z);

	//}
#endif
}

/*
Render
画面に描画する
*/
void CMesh::Render() {
	/* 頂点データ，法線データの配列を有効にする */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	/* 頂点データ，法線データの場所を指定する */
//	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
//	glNormalPointer(GL_FLOAT, 0, mpNormal);
	glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);
	/* 頂点のインデックスの場所を指定して図形を描画する */
	//glDrawElements(GL_TRIANGLES, 3 * mFaceNum,
	//	GL_UNSIGNED_INT, mpVertexIndex);
	/* 頂点のインデックスの場所を指定して図形を描画する */
	for (int i = 0; i < mFaceNum; i++) {
		//マテリアルを適用する
		mMaterial[mpMaterialIndex[i]]->SetMaterial();
		glDrawElements(GL_TRIANGLES, 3,
			GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		//マテリアルを解除する
		mMaterial[mpMaterialIndex[i]]->UnSetMaterial();
	}

	/* 頂点データ，法線データの配列を無効にする */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
/*
Render
メッシュの面数が0以外なら描画する
*/
void CModelXFrame::Render() {
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}
/*
Render
全てのフレームの描画処理を呼び出す
*/
void CModelX::Render() {
	for (int i = 0; i < mFrame.size(); i++) {
		mFrame[i]->Render();
	}
}

/*
CSkinWeights
スキンウェイトの読み込み
*/
CSkinWeights::CSkinWeights(CModelX *model)
: mpFrameName(0)
, mFrameIndex(0)
, mIndexNum(0)
, mpIndex(0)
, mpWeight(0)
{
	model->GetToken();	// {
	model->GetToken();	// FrameName
	//フレーム名エリア確保、設定
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//頂点番号数取得
	mIndexNum = model->GetIntToken();
	//頂点番号数が0を超える
	if (mIndexNum > 0) {
		//頂点番号と頂点ウェイトのエリア確保
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//頂点番号取得
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		//頂点ウェイト取得
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
	}
	//オフセット行列取得
	for (int i = 0; i < 16; i++) {
		mOffset.f[i] = model->GetFloatToken();
	}
	model->GetToken();	// }

}
/*
CAnimationSet
*/
CAnimationSet::CAnimationSet(CModelX *model)
: mpName(0)
, mTime(0)
, mWeight(0)
, mMaxTime(0)
{
	model->mAnimationSet.push_back(this);
	model->GetToken();	// Animation Name
	//アニメーションの名前を退避
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken(); // {
	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or Animation
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Animation") == 0) {
			//Animation要素読み込み
			mAnimation.push_back(new CAnimation(model));
		}
	}
	//終了時間設定
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
}
/*
FindFrame
フレーム名に該当するフレームのアドレスを返す
*/
CModelXFrame* CModelX::FindFrame(char* name) {
	//イテレータの作成
	std::vector<CModelXFrame*>::iterator itr;
	//先頭から最後まで繰り返す
	for (itr = mFrame.begin(); itr != mFrame.end(); itr++) {
		if ((*itr)->mpName) {
			//名前が一致したか？
			if (strcmp(name, (*itr)->mpName) == 0) {
				//一致したらそのアドレスを返す
				return *itr;
			}
		}
	}
	//一致するフレーム無い場合はNULLを返す
	return NULL;
}

CAnimation::CAnimation(CModelX *model)
: mpFrameName(0)
, mFrameIndex(0)
, mKeyNum(0)
, mpKey(0)
{
	model->GetToken(); // { or Animation Name
	if (strchr(model->mToken, '{')) {
		model->GetToken(); // {
	}
	else {
		model->GetToken(); // {
		model->GetToken(); // {
	}

	model->GetToken(); //FrameName
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex =
		model->FindFrame(model->mToken)->mIndex;
	model->GetToken(); // }

	//キーの配列を保存しておく配列
	CMatrix44 *key[4] = { 0, 0, 0, 0 };
	//時間の配列を保存しておく配列
	float *time[4] = { 0, 0, 0, 0 };

	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or AnimationKey
		if (strchr(model->mToken, '}')) break;
		if (strcmp(model->mToken, "AnimationKey") == 0) {
			model->GetToken(); // {
			//データのタイプ取得
			int type = model->GetIntToken();
			//時間数取得
			mKeyNum = model->GetIntToken();
			switch (type) {
			case 0: // Rotation Quaternion
				//行列の配列を時間数分確保
				key[type] = new CMatrix44[mKeyNum];
				//時間の配列を時間数分確保
				time[type] = new float[mKeyNum];
				//時間数分繰り返す
				for (int i = 0; i < mKeyNum; i++) {
					//時間取得
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 4を読み飛ばし
					//w,x,y,zを取得
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//クォータニオンから回転行列に変換
					key[type][i].SetQuaternion(x, y, z, w);
				}
				break;
			case 1: //拡大・縮小の行列作成
				key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].m00 = x;
					key[type][i].m11 = y;
					key[type][i].m22 = z;
				}
				break;
			case 2: //移動の行列作成
				key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					CVector3 vec(x, y, z);
					key[type][i].translate(vec);
				}
				break;
			case 4: //行列データを取得
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					mpKey[i].mTime = model->GetFloatToken(); // Time
					model->GetToken(); // 16
					for (int j = 0; j < 16; j++) {
						mpKey[i].mMatrix.f[j] = model->GetFloatToken();
					}
				}
				break;
			}
			model->GetToken(); // }
		}
		else {
			model->SkipNode();
		}
	}	//whileの終わり
	//行列データではない時
	if (mpKey == 0) {
		//時間数分キーを作成
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			//時間設定
			mpKey[i].mTime = time[2][i]; // Time
			//行列作成 Position * Rotation * Size
			mpKey[i].mMatrix = key[2][i] * key[0][i] * key[1][i];
		}
	}
	//確保したエリア解放
	for (int i = 0; i < ARRAY_SIZE(key); i++) {
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(key[i]);
	}
}

/*
AnimateFrame
フレームの変換行列をアニメーションデータで更新する
*/
void CModelX::AnimateFrame() {
	//アニメーションで適用されるフレームの
	//変換行列をゼロクリアする
	for (int i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0) continue;
		//フレーム分（Animation分）繰り返す
		for (int j = 0; j < anim->mAnimation.size(); j++) {
			CAnimation* animation = anim->mAnimation[j];
			//該当するフレームの変換行列をゼロクリアする
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix44));
		}
	}
	//アニメーションに該当するフレームの変換行列を
	//アニメーションのデータで設定する
	for (int i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0) continue;
		//フレーム分（Animation分）繰り返す
		for (int j = 0; j < anim->mAnimation.size(); j++) {
			//フレームを取得する
			CAnimation* animation = anim->mAnimation[j];
			CModelXFrame* frame = mFrame[animation->mFrameIndex];
			//キーがない場合は飛ばず
			if (animation->mpKey == 0) continue;
			//時間を取得
			float time = anim->mTime;
			//最初の時間より小さい場合
			if (time < animation->mpKey[0].mTime) {
				//変換行列を0コマ目の行列で更新
				frame->mTransformMatrix += animation->mpKey[0].mMatrix * anim->mWeight;
			}
			//最後の時間より大きい場合
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime) {
				//変換行列を最後のコマの行列で更新
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix * anim->mWeight;
			}
			else {
				//時間の途中の場合
				for (int k = 1; k < animation->mKeyNum; k++) {
					//変換行列を、線形補間にて更新
					if (time < animation->mpKey[k].mTime &&
						animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime) {
						float r = (animation->mpKey[k].mTime - time) /
							(animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
						frame->mTransformMatrix +=
							(animation->mpKey[k - 1].mMatrix * r + animation->mpKey[k].mMatrix * (1 - r)) * anim->mWeight;
						break;
					}
				}
			}
		}
	}
	//デバッグバージョンのみ有効
#ifdef _DEBUG
	//for (int j = 0; j < mFrame.size(); j++) {
	//	printf("Frame:%s\n", mFrame[j]->mpName);
	//	for (int i = 0; i < ARRAY_SIZE(mFrame[j]->mTransformMatrix.f); i++) {
	//		printf("%10f", mFrame[j]->mTransformMatrix.f[i]);
	//		if (i % 4 == 3)
	//			printf("\n");
	//	}
	//}
#endif

}
/*
Animate
合成行列の作成
*/
void CModelXFrame::Animate(CMatrix44* parent) {
	//親からの変換行列に、自分の変換行列を掛ける
	mCombinedMatrix = (*parent) * mTransformMatrix;
	//子フレームの合成行列を作成する
	for (int i = 0; i < mChild.size(); i++) {
		mChild[i]->Animate(&mCombinedMatrix);
	}
}
/*
SetSkinWeightFrameIndex
スキンウェイトにフレーム番号を設定する
*/
void CModelX::SetSkinWeightFrameIndex() {
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++) {
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//スキンウェイト分繰り返し
			for (int j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++) {
				//フレーム名のフレームを取得する
				CModelXFrame* frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//フレーム番号を設定する
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
			}
		}
	}
}
/* AnimateVertex 頂点にアニメーションを適用 */
void CMesh::AnimateVertex(CModelX *model) {
	//アニメーション用の頂点エリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector3)* mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector3)* mNormalNum);
	//スキンウェイト分繰り返し
	for (int i = 0; i < mSkinWeights.size(); i++) {
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//フレーム合成行列にオフセット行列を合成
		CMatrix44 mSkinningMatrix = model->mFrame[frameIndex]->mCombinedMatrix * mSkinWeights[i]->mOffset;
		//頂点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//法線を正規化する
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].normalize();
	}
}
/* AnimateVertex 頂点にアニメーションを適用 */
void CMesh::AnimateVertex(CMatrix44 *mat) {
	//アニメーション用の頂点エリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector3)* mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector3)* mNormalNum);
	//スキンウェイト分繰り返し
	for (int i = 0; i < mSkinWeights.size(); i++) {
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//フレーム合成行列にオフセット行列を合成
		CMatrix44 mSkinningMatrix = mat[frameIndex] * mSkinWeights[i]->mOffset;
		//頂点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//法線を正規化する
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].normalize();
	}
}
/*
AnimateVertex
頂点にアニメーションを適用する
*/
void CModelX::AnimateVertex() {
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++) {
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//頂点をアニメーションで更新する
			mFrame[i]->mMesh.AnimateVertex(this);
		}
	}
}
void CModelX::AnimateVertex(CMatrix44 *mat) {
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++) {
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//頂点をアニメーションで更新する
			mFrame[i]->mMesh.AnimateVertex(mat);
		}
	}
}
/*
FindMaterial
マテリアル名に該当するマテリアルを返却する
*/
CMaterial* CModelX::FindMaterial(char* name) {
	//マテリアル配列のイテレータ作成
	std::vector<CMaterial*>::iterator itr;
	//マテリアル配列を先頭から順に検索
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
		//名前が一致すればマテリアルのポインタを返却
		if (strcmp(name, (*itr)->mpName) == 0) {
			return *itr;
		}
	}
	//無い時はNULLを返却
	return NULL;
}
/*
FindTexture
nameに該当するファイル名を持つテクスチャを検索して
返却する
*/
CTexture* CModelX::FindTexture(char* name) {
	//テクスチャ配列のイテレータ作成
	std::vector<CTexture*>::iterator itr;
	//テクスチャ配列の先頭から順に検索
	for (itr = mTexture.begin(); itr != mTexture.end(); itr++) {
		//名前が一致すればテクスチャのポインタを返却
		if (strcmp(name, (*itr)->mpName) == 0) {
			return *itr;
		}
	}
	//無い時はNULLを返却
	return NULL;
}

//37
/*
頂点バッファを作成する
*/
void CMesh::CreateVertexBuffer() {
	//メッシュ毎に一回作成すればよい
	if (mMyVertexBufferId > 0)
		return;

	if (mVertexNum > 0) {
		//頂点インデックスを使わず、全ての面データを作成
		CMyVertex *pmyVertex, *vec;
		//頂点数計算
		int myVertexNum = mFaceNum * 3;
		//頂点数分頂点配列作成
		pmyVertex = new CMyVertex[myVertexNum];
		vec = new CMyVertex[mVertexNum];
		for (int j = 0; j < mVertexNum; j++) {
			//頂点座標設定
			vec[j].mPosition = mpVertex[j];
			//テクスチャマッピング設定
			if (mpTextureCoords != NULL)
				vec[j].mTextureCoords = mpTextureCoords[j];
			vec[j].mBoneWeight[0] = 1.0f;
		}
		int wi = 0;
		//スキンウェイト設定
		for (int k = 0; k < mSkinWeights.size(); k++) {
			for (int l = 0; l < mSkinWeights[k]->mIndexNum; l++) {
				int idx = mSkinWeights[k]->mpIndex[l];
				for (int m = 0; m < 4; m++) {
					if (vec[idx].mBoneIndex[m] == 0) {
						vec[idx].mBoneIndex[m] = mSkinWeights[k]->mFrameIndex;
						vec[idx].mBoneWeight[m] = mSkinWeights[k]->mpWeight[l];
						break;
					}
				}
			}
		}

		int k = 0;
		//マテリアル番号の昇順に面の頂点を設定
		for (int i = 0; i < mMaterial.size(); i++) {
			int w = k;
			for (int j = 0; j < mMaterialIndexNum; j++) {
				if (mpMaterialIndex[j] == i) {
					//頂点配列に設定し、法線を設定する
					pmyVertex[k] = vec[mpVertexIndex[j * 3]];
					pmyVertex[k++].mNormal = mpNormal[j * 3];

					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 1]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 1];

					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 2]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 2];

				}
			}
			//マテリアル毎の頂点数を追加する
			mMaterialVertexCount.push_back(k - w);
		}

		//頂点バッファの作成
		glGenBuffers(1, &mMyVertexBufferId);
		//頂点バッファをバインド
		glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBufferId);
		//バインドしたバッファにデータを転送
		glBufferData(GL_ARRAY_BUFFER, sizeof(CMyVertex)*myVertexNum, pmyVertex, GL_STATIC_DRAW);
		//バインド解除
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//配列解放
		delete[] pmyVertex;
		delete[] vec;
		pmyVertex = NULL;
	}
}

//37
void CModelX::RenderShader(CMatrix44 *pCombinedMatrix) {
	mShader.Render(this, pCombinedMatrix);
}

void CModelX::AddMaterial(CModelX* model, CMaterial* material) {
	//CModelXにマテリアルを追加する
	model->mMaterial.push_back(material);
	model->GetToken(); // { ? Name
	if (strcmp(model->mToken, "{") != 0) {
		//{でないときはマテリアル名
		material->mpName = new
			char[strlen(model->mToken) + 1];
		strcpy(material->mpName, model->mToken);
		model->GetToken(); // {
	}

	material->mDiffuse[0] = model->GetFloatToken();
	material->mDiffuse[1] = model->GetFloatToken();
	material->mDiffuse[2] = model->GetFloatToken();
	material->mDiffuse[3] = model->GetFloatToken();
	material->mPower = model->GetFloatToken();

	material->mSpecular[0] = model->GetFloatToken();
	material->mSpecular[1] = model->GetFloatToken();
	material->mSpecular[2] = model->GetFloatToken();

	material->mEmissive[0] = model->GetFloatToken();
	material->mEmissive[1] = model->GetFloatToken();
	material->mEmissive[2] = model->GetFloatToken();

	model->GetToken(); // TextureFilename or }

	if (strcmp(model->mToken, "TextureFilename") == 0) {
		//テクスチャありの場合、テクスチャファイル名取得
		model->GetToken(); // {
		model->GetToken(); // filename
		material->mpTextureFilename = new char[strlen(model->mToken) + 1];
		strcpy(material->mpTextureFilename, model->mToken);
		//テクスチャファイル名でテクスチャを検索する
		CTexture *p = model->FindTexture(model->mToken);
		//テクスチャが在る時
		if (p) {
			//テクスチャIDを取得
			material->mTextureId = p->id;
		}
		else {
			//無い場合、テクスチャ読み込み
			p = new CTexture(model->mToken);
			if (p->mpName) {
				//テクスチャ配列に追加
				model->mTexture.push_back(p);
				//テクスチャIDを取得
				material->mTextureId = p->id;
			}
		}
		model->GetToken(); // }
		model->GetToken(); // }
	}
#ifdef _DEBUG
	//printf("%s\n", mpName);
	//printf("Diffuse: %10f%10f%10f%10f\n", mDiffuse[0], mDiffuse[1], mDiffuse[2], mDiffuse[3]);
	//printf("Power: %10f\n", mPower);
	//printf("Specular: %10f%10f%10f%10f\n", mSpecular[0], mSpecular[1], mSpecular[2], mSpecular[3]);
	//printf("Emissive: %10f%10f%10f%10f\n", mEmissive[0], mEmissive[1], mEmissive[2], mEmissive[3]);
#endif

}

void CModelX::SeparateAnimationSet(int start, int end, char* name) {
	CAnimationSet *anim = mAnimationSet[0];
	CAnimationSet *as = new CAnimationSet();
	as->mpName = new char[strlen(name) + 1];
	strcpy(as->mpName, name);
	as->mMaxTime = end - start;
	for (int i = 0; i < anim->mAnimation.size(); i++) {
		CAnimation* animation = new CAnimation();
		animation->mpFrameName = new char[strlen(anim->mAnimation[i]->mpFrameName) + 1];
		strcpy(animation->mpFrameName, anim->mAnimation[i]->mpFrameName);
		animation->mFrameIndex = anim->mAnimation[i]->mFrameIndex;
		animation->mKeyNum = end - start + 1;
		animation->mpKey = new CAnimationKey[animation->mKeyNum];
		animation->mKeyNum = 0;
		for (int j = start; j <= end && j < anim->mAnimation[i]->mKeyNum; j++) {
			animation->mpKey[animation->mKeyNum] = anim->mAnimation[i]->mpKey[j];
			animation->mpKey[animation->mKeyNum].mTime = animation->mKeyNum++;
		}
		as->mAnimation.push_back(animation);
	}
	mAnimationSet.push_back(as);
}

