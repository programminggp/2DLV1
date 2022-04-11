//標準入出力のインクルード
#include<string.h>
//CModelのインクルード
#include"CModel.h"
//CVectorのインクルード
#include"CVector.h"
//CTriangleのインクルード
#include"CTriangle.h"

//デフォルトコンストラクタ
CModel::CModel()
:mpVertex(nullptr), mpNormal(nullptr), mpTextureCoord(nullptr)
{

}


//モデルファイルの入力
//Load(モデルファイル名,マテリアルファイル名)
void CModel::Load(char* obj, char* mtl) {
	//頂点データの保存（CVector型）
	std::vector<CVector>vertex;
	//法線データの保存（CVector型）
	std::vector<CVector>normal;
	//テクスチャマッピングの保存 (CVector型)
	std::vector<CVector>uv;
	//ファイルポインタ変数の作成
	FILE* fp;
	//fopen(ファイル名,モード)
	//オープン出来ない時はNULLを返す
	fp = fopen(mtl, "r");
	//ファイルオープンのエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラーを出力して戻る
		printf("%s file open error\n", mtl);
		return;
	}
	//ファイルからデータを入力
	// 入力エリアを作成する
	char buf[256];
	//マテリアルインデックス
	int idx = 0;
	//ファイルから１行入力
	// fgets(入力エリア,エリアサイズ,ファイルポインタ)
	// ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//データを分割する
		char str[4][64] = { "","","","" };
		//文字列からデータを4つ変数へ代入する
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//先頭がnewmtlの時、マテリアルを追加する
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//マテリアル名の設定
			pm->Name(str[1]);
			//マテリアルの可変長配列に追加
			mpMaterials.push_back(pm);
			//配列の長さを取得
			idx = mpMaterials.size() - 1;
		}
	
	
		//先頭がKdの時、Diffuseを設定する
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		//先頭がdの時、a値を設定する
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		//先頭がmap_Kdの時、テクスチャを入力する
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
	}
	//ファイルのクローズ
	fclose(fp);
	
	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープン出来ない時はNULLを返す
	fp = fopen(obj, "r");
	//ファイルオープンのエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラーを出力して戻る
		printf("%s file open error\n", obj);
		return;
	}
//ファイルから１行入力
// fgets(入力エリア,エリアサイズ,ファイルポインタ)
// ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//データを分割する
		char str[4][64] = { "","","","" };
		//文字列からデータを４つ変数へ代入する
		// sscanf(文字列,変換指定子,変数)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//先頭がnewmtlの時、マテリアルを追加する
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//マテリアル名の設定
			pm->Name(str[1]);
			//マテリアルの可変長配列に追加
			mpMaterials.push_back(pm);
			//配列の長さを取得
			idx = mpMaterials.size() - 1;
		}
		//文字列の比較
		//strcmp(文字列１,文字列２)
		//文字列１と文字列２が同じとき0,異なる時０以外を返す
		// 先頭がvnの時、頂点をnormalに追加する
		if (strcmp(str[0], "vn") == 0) {
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		if (strcmp(str[0], "v") == 0) {
			//可変長配列vertexに追加する
			//atof(文字列) 文字列からfloat型の値を返す
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//先頭がvtの時、uvに追加する
		else if (strcmp(str[0], "vt") == 0) {
			//可変長配列uvに追加する
			//atof(文字列)　文字列からfloat型の値を返す
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
		//先頭がusemtlの時、マテリアルインデックスを取得する
		else if (strcmp(str[0], "usemtl") == 0) {
			//可変長配列を後から比較
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//同じ名前のマテリアルがあればループ終了
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) {
					break; //ループから出る
				}
			}
		}
		//先頭がfの時、三角形を作成して追加する
		else if (strcmp(str[0], "f") == 0) {
			//頂点と法線の番号作成
			int v[3], n[3];
			//テクスチャマッピングの有無を判定
			if (strstr(str[1], "//")) {
				//頂点と法線の番号取得
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				//三角形作成
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//マテリアル番号の設定
				t.MaterialIdx(idx);
				//可変長配列mTrianglesに三角形を追加
				mTriangles.push_back(t);
			}
			else {
				//テクスチャマッピング有り
				int u[3];//テクスチャマッピングの番号取得
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				//三角形作成
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//テクスチャマッピングの設定
				t.SetUv(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				//マテリアル番号の設定
				t.MaterialIdx(idx);
				//可変長配列mTrianglesに三角形を追加
				mTriangles.push_back(t);
			}
		}
	}
	//ファイルのクローズ
	fclose(fp);

	//頂点配列の作成
	//全ての座標の値をマテリアルの順番に保存する
	mpVertex = new float[mTriangles.size() * 9];
	//全ての法線の値をマテリアルの順番に保存する
	mpNormal = new float[mTriangles.size() * 9];
	//全てのテクスチャマッピングの値をマテリアルの順番に保存する
	mpTextureCoord = new float[mTriangles.size() * 6];

	int v = 0, t = 0;
	//マテリアル毎に頂点配列に設定する
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		//全ての三角形を比較
		for (int j = 0; j < mTriangles.size(); j++)
		{
			//マテリアル番号が一致する時
			if (i == mTriangles[j].MaterialIdx()) {
				//頂点配列に設定する
				//頂点座標
				mpVertex[v++] = mTriangles[j].V0().X();
				mpVertex[v++] = mTriangles[j].V0().Y();
				mpVertex[v++] = mTriangles[j].V0().Z();
				mpVertex[v++] = mTriangles[j].V1().X();
				mpVertex[v++] = mTriangles[j].V1().Y();
				mpVertex[v++] = mTriangles[j].V1().Z();
				mpVertex[v++] = mTriangles[j].V2().X();
				mpVertex[v++] = mTriangles[j].V2().Y();
				mpVertex[v++] = mTriangles[j].V2().Z();
				v -= 9;
				//法線
				mpNormal[v++] = mTriangles[j].N0().X();
				mpNormal[v++] = mTriangles[j].N0().Y();
				mpNormal[v++] = mTriangles[j].N0().Z();
				mpNormal[v++] = mTriangles[j].N1().X();
				mpNormal[v++] = mTriangles[j].N1().Y();
				mpNormal[v++] = mTriangles[j].N1().Z();
				mpNormal[v++] = mTriangles[j].N2().X();
				mpNormal[v++] = mTriangles[j].N2().Y();
				mpNormal[v++] = mTriangles[j].N2().Z();
				//テクスチャマッピング
				mpTextureCoord[t++] = mTriangles[j].UV0().X();
				mpTextureCoord[t++] = mTriangles[j].UV0().Y();
				mpTextureCoord[t++] = mTriangles[j].UV1().X();
				mpTextureCoord[t++] = mTriangles[j].UV1().Y();
				mpTextureCoord[t++] = mTriangles[j].UV2().X();
				mpTextureCoord[t++] = mTriangles[j].UV2().Y();



			}
		}
		//頂点数を設定
		mpMaterials[i]->VertexNum(v / 3);
	}
}

void CModel::Render()
{
	for (int i = 0; i < mTriangles.size(); i++)
	{
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		mTriangles[i].Render();
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}

//描画
void CModel::Render(const CMatrix& m) {
	//行列の退避
	glPushMatrix();
	//合成行列を掛ける
	glMultMatrixf(m.M());

	//頂点座標の配列を有効にする
	glEnableClientState(GL_VERTEX_ARRAY);
	//法線の配列を有効にする
	glEnableClientState(GL_NORMAL_ARRAY);
	//テクスチャマッピングの配列を有効にする
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//頂点座標の配列を指定する
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	//法線の配列を指定する
	glNormalPointer(GL_FLOAT, 0, mpNormal);
	//テクスチャコードの配列を指定する
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoord);

	int first = 0; //描画位置
	//マテリアル毎に描画する
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		//マテリアルを適用する
		mpMaterials[i]->Enabled();
		//描画位置からのデータで三角形を描画する
		glDrawArrays(GL_TRIANGLES, first, mpMaterials[i]->VertexNum() - first);
		//マテリアルを無効にする
		mpMaterials[i]->Disabled();
		//描画位置を移動
		first = mpMaterials[i]->VertexNum();
	}
	//行列を戻す
	glPopMatrix();

	//頂点座標の配列を無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	//法線の配列を無効にする
	glDisableClientState(GL_NORMAL_ARRAY);
	//テクスチャマッピングの配列を無効にする
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//デストラクタ
CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
	if (mpVertex != nullptr) 
	{
		//頂点座標配列削除
		delete[] mpVertex;
	}
	if (mpNormal != nullptr)
	{
		//法線配列削除
		delete[] mpNormal;
	}
	if (mpTextureCoord != nullptr)
	{
		//テクスチャマッピング配列削除
		delete[] mpTextureCoord;

	}
	
}

