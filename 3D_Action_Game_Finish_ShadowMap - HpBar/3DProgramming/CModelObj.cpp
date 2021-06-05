#include "CModelObj.h"
#include "CCollision.h"
#include <string.h>

/*
CMaterialObj::CMaterialObj() : m_pTex(NULL) ,m_TexDirectory(""){
}

void CMaterialObj::Map() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

	if (m_pTex) {
		glBindTexture(GL_TEXTURE_2D, m_pTex->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
}

void CMaterialObj::Unmap() {
	if (m_pTex) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
}

void CMaterialObj::Release() {
	if (m_pTex) {
		glDeleteTextures(1, &m_pTex->id);
		delete m_pTex;
		m_pTex = NULL;
	}
}
*/

bool CModelObj::LoadMaterial(char *path) {
	return LoadMaterial(path, 0);
}

bool CModelObj::LoadMaterial(char *path, char *newmtl) {
	char key[32];
	FILE* fp = fopen(path, "r");
	//ファイルが開けなかった場合はエラーを表示しfalseを返す
	if (fp == NULL) {
		printf("ファイルがありません%s\n", path);
		return false;
	}

	fscanf(fp, "%s", key);
	while (!feof(fp)) {
		CMaterial *m_material = new CMaterial();
		if (strcmp(key, "newmtl") == 0) {
			fscanf(fp, "%s", key);
			m_material->mpName = new char[strlen(key) + 1];
			strcpy(m_material->mpName, key);
			fscanf(fp, "%s", key);
			while (!feof(fp)) {
				if (strcmp(key, "newmtl") == 0) {
					break;
				}
				if (strcmp(key, "Ka") == 0) {
					fscanf(fp, "%f %f %f", &m_material->mAmbient[0], &m_material->mAmbient[1], &m_material->mAmbient[2]);
					m_material->mAmbient[3] = 1.0f;
				}
				else if (strcmp(key, "Kd") == 0) {
					fscanf(fp, "%f %f %f", &m_material->mDiffuse[0], &m_material->mDiffuse[1], &m_material->mDiffuse[2]);
					m_material->mDiffuse[3] = 1.0f;
				}
				else if (strcmp(key, "Ks") == 0) {
					fscanf(fp, "%f %f %f", &m_material->mSpecular[0], &m_material->mSpecular[1], &m_material->mSpecular[2]);
				}
				else if (strcmp(key, "Ns") == 0) {
					fscanf(fp, "%f", &m_material->mPower);
				}
				else if (strcmp(key, "d") == 0) {
					float aplha;
					fscanf(fp, "%f", &aplha);
					m_material->mAmbient[3] = aplha;
					m_material->mDiffuse[3] = aplha;
				}
				else if (strcmp(key, "map_Kd") == 0) {
					char str[128];
					fscanf(fp, "%s\n", str);
					m_material->mTexture.load(str);
					m_material->mTextureId = m_material->mTexture.id;
				}
				fscanf(fp, "%s", key);
			}
			mMaterial.push_back(m_material);
		}
		else {
			fscanf(fp, "%s", key);
		}
	}
	fclose(fp);
	return true;
}

CModelObj::CModelObj()
	:mpVertex(NULL), m_vertexNum(0), mMyVertexBufferId(0)
{
}

CModelObj::~CModelObj() {
	SAFE_DELETE_ARRAY(mpVertex);
	for (int i = 0; i < mMaterial.size(); i++) {
		delete mMaterial[i];
	}
//	Release();
}

bool CModelObj::Load(const char *path) {
	mTriangle.clear();
	//ファイルポインタ(fp)の作成し開いたファイルのハンドルを渡す。
	FILE* fp = fopen(path, "r");
	//ファイルが開けなかった場合はエラーを表示しfalseを返す
	if (fp == NULL) {
		printf("ファイルがありません%s\n", path);
		return false;
	}
	//座標データ用カウンター
	int	VCnt = 0;
	//法線データ用カウンター
	int	NCnt = 0;
	//テクスチャーコード用カウンター
	int	TCnt = 0;
	//面データ用カウンター
	int	FCnt = 0;
	//キーワード格納用
	char key[64];
	//ファイルの末尾でなければ繰り返す
	while (!feof(fp)) {
		//keyをクリア
		key[0] = 0;
		//1単語　文字列を読み込み
		fscanf(fp, "%s", key);
		//読み込んだキーワードが「v」なら座標データカウンターをカウントアップ
		if (strcmp(key, "v") == 0) {
			VCnt++;
		}
		else
			//読み込んだキーワードが「f」なら面データカウンターをカウントアップ
			if (strcmp(key, "f") == 0) {
				FCnt++;
			}
			else
				//読み込んだキーワードが「vn」なら法線データカウンターをカウントアップ
				if (strcmp(key, "vn") == 0) {
					NCnt++;
				}
				else
					//読み込んだキーワードが「vt」ならテクスチャーコードデータカウンターをカウントアップ
					if (strcmp(key, "vt") == 0) {
						TCnt++;
					}
					else
						//読み込んだキーワードが「mtllib」ならマテリアルファイルの読み込み
						if (strcmp(key, "mtllib") == 0) {
							char str[64];
							fscanf(fp, "%s\n", str);
							LoadMaterial(str);
						}
	}
	//printf("VCnt %d\n", VCnt);

	//座標データの数だけ配列を作成
	CVector3 *pVertex = new CVector3[VCnt];
	//法線データの数だけ配列を作成
	CVector3 *pNormal = new CVector3[NCnt];
	//テクスチャーコードデータの数だけ配列を作成
	CVector2 *pTexCoord = new CVector2[TCnt];
	//当たり判定用三角形
	CTriangle t;
	//描画用の頂点データの頂点数を計算　3*面の数
	m_vertexNum = 3 * FCnt;
//	m_vertexNum = 6 * FCnt;
	//描画用頂点配列を作成
	//m_pVertexAry = new CVector3[m_vertexNum];
	////描画用法線配列を作成
	//m_pNormalAry = new CVector3[m_vertexNum];
	////描画用テクスチャーコード配列を作成
	//m_pTexCoordAry = new CVector2[m_vertexNum];
	mpVertex = new CVertex[m_vertexNum];
	//読み込んだ座標データを0から順番に格納するため、カウンターを0に戻す
	VCnt = 0;
	NCnt = 0;
	TCnt = 0;
	//読み書きの位置をファイルの先頭に戻す
	fseek(fp, 0, SEEK_SET);
	//ファイルの末尾でなければ繰り返す
	while (!feof(fp)) {
		//keyをクリア
		key[0] = 0;
		//キーワードの読み込み
		fscanf(fp, "%s", key);
		//「ｖ」を読み込んだら、座標データを読み込む
		if (strcmp(key, "v") == 0) {
			fscanf(fp, "%f %f %f", &pVertex[VCnt].x, &pVertex[VCnt].y, &pVertex[VCnt].z);
			//読み込み先を次のデータへ
			VCnt++;
		}
		else//「vn」を読み込んだら、法線データを読み込む
		if (strcmp(key, "vn") == 0) {
			fscanf(fp, "%f %f %f", &pNormal[NCnt].x, &pNormal[NCnt].y, &pNormal[NCnt].z);
			//読み込み先を次のデータへ
			NCnt++;
		}
		else//「vt」を読み込んだら、テクスチャーコードデータを読み込む
		if (strcmp(key, "vt") == 0) {
			fscanf(fp, "%f %f", &pTexCoord[TCnt].x, &pTexCoord[TCnt].y);
			pTexCoord[TCnt].y = 1.0f - pTexCoord[TCnt].y;
			//読み込み先を次のデータへ
			TCnt++;
		}
	}
	//描画用頂点配列への座標データ格納先番号
	int idx = 0, cnt = 0;
	for (int i = 0; i < mMaterial.size(); i++) {
		//読み書きの位置をファイルの先頭に戻す
		fseek(fp, 0, SEEK_SET);
		//keyをクリア
		key[0] = 0;
		//キーワードの読み込み
		fscanf(fp, "%s", key);
		//ファイルの末尾でなければ繰り返す
		while (!feof(fp)) {
			if (strcmp(key, "usemtl") == 0) {
				//キーワードの読み込み
				fscanf(fp, "%s", key);
				if (strcmp(key, mMaterial[i]->mpName) == 0) {
					//keyをクリア
					key[0] = 0;
					//キーワードの読み込み
					fscanf(fp, "%s", key);
					//ファイルの末尾でなければ繰り返す
					while (!feof(fp)) {
						if (strcmp(key, "usemtl") == 0) {
							break;
						}
						if (strcmp(key, "f") == 0) {
							int v1, v2, v3;
							int n1, n2, n3;
							int t1, t2, t3;
							if (TCnt > 0) {
								fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

								mpVertex[idx].mPosition = pVertex[v1 - 1];
								mpVertex[idx].mNormal = pNormal[n1 - 1];
								mpVertex[idx++].mTextureCoords = pTexCoord[t1 - 1];

								//m_pVertexAry[idx] = pVertex[v1 - 1];		//頂点１の座標データ
								//m_pNormalAry[idx] = pNormal[n1 - 1];		//頂点１の法線データ
								//m_pTexCoordAry[idx++] = pTexCoord[t1 - 1];	//頂点１のテクスチャーコードデータ

								mpVertex[idx].mPosition = pVertex[v2 - 1];
								mpVertex[idx].mNormal = pNormal[n2 - 1];
								mpVertex[idx++].mTextureCoords = pTexCoord[t2 - 1];

								//m_pVertexAry[idx] = pVertex[v2 - 1];		//頂点２の座標データ
								//m_pNormalAry[idx] = pNormal[n2 - 1];		//頂点２の法線データ
								//m_pTexCoordAry[idx++] = pTexCoord[t2 - 1];	//頂点２のテクスチャーコードデータ

								mpVertex[idx].mPosition = pVertex[v3 - 1];
								mpVertex[idx].mNormal = pNormal[n3 - 1];
								mpVertex[idx++].mTextureCoords = pTexCoord[t3 - 1];

								//m_pVertexAry[idx] = pVertex[v3 - 1];
								//m_pNormalAry[idx] = pNormal[n3 - 1];
								//m_pTexCoordAry[idx++] = pTexCoord[t3 - 1];
							}
							else {
								fscanf(fp, "%d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);

								mpVertex[idx].mPosition = pVertex[v1 - 1];
								mpVertex[idx++].mNormal = pNormal[n1 - 1];

								//m_pVertexAry[idx] = pVertex[v1 - 1];			//頂点１の座標データ
								//m_pNormalAry[idx++] = pNormal[n1 - 1];			//頂点１の法線データ

								mpVertex[idx].mPosition = pVertex[v2 - 1];
								mpVertex[idx++].mNormal = pNormal[n2 - 1];

								//m_pVertexAry[idx] = pVertex[v2 - 1];		//頂点２の座標データ
								//m_pNormalAry[idx++] = pNormal[n2 - 1];		//頂点２の法線データ

								mpVertex[idx].mPosition = pVertex[v3 - 1];
								mpVertex[idx++].mNormal = pNormal[n3 - 1];

								//m_pVertexAry[idx] = pVertex[v3 - 1];
								//m_pNormalAry[idx++] = pNormal[n3 - 1];
							}
							/*三角形設定*/
							t.SetVertex(mpVertex[idx - 3].mPosition, mpVertex[idx - 2].mPosition, mpVertex[idx - 1].mPosition);
							mTriangle.push_back(t);
						}
						//キーワードの読み込み
						fscanf(fp, "%s", key);
					}
				}
				else {
					//キーワードの読み込み
					fscanf(fp, "%s", key);
				}
			}
			else {
				//キーワードの読み込み
				fscanf(fp, "%s", key);
			}
		}
		mMaterialVertexCount.push_back(idx - cnt);
		cnt = idx;
	}
	m_vertexNum = idx;
	//シェーダー読み込み
//	mShader.load("skinmesh.vert", "skinmesh.flag");
	mShader.load("shadow.vert", "shadow.flag");
	CreateVertexBuffer();
	//一時データ解放
	delete[] pVertex;
	delete[] pNormal;
	delete[] pTexCoord;
	return true;
}

void CModelObj::Render() {

	mShader.Render(this);

	return;

	glPushMatrix();

	glMultMatrixf(mMatrix.f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	int offset = 0;
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)mpVertex);
	offset += sizeof(mpVertex->mPosition);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), ((unsigned char*)mpVertex) + offset);
	offset += sizeof(mpVertex->mNormal);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex), ((unsigned char*)mpVertex) + offset);

	if (mMaterial[0]->mTextureId > 0) {
	}

//	glDrawArrays(GL_TRIANGLES, 0, m_vertexNum);
	int idx = 0;
	for (int i = 0; i < mMaterial.size(); i++) {
		mMaterial[i]->SetMaterial();
		glDrawArrays(GL_TRIANGLES, idx, mMaterialVertexCount[i]);
		idx += mMaterialVertexCount[i];
		mMaterial[i]->UnSetMaterial();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPopMatrix();

}

void CModelObj::Release() {
	//if (m_pVertexAry) { delete[] m_pVertexAry; m_pVertexAry = NULL; }
	//if (m_pNormalAry) { delete[] m_pNormalAry; m_pNormalAry = NULL; }
	//if (m_pTexCoordAry) { delete[] m_pTexCoordAry; m_pTexCoordAry = NULL; }
}

/*三角形当たり判定追加*/
void CModelObj::AddCollisionManager() {
	for each (CTriangle triangle in mTriangle)
	{
		//三角形コライダを生成する
		new CTriangleCollider(CCollider::EGROUND, triangle.mVertex[0], triangle.mVertex[1], triangle.mVertex[2]);
	}
}

/*
頂点バッファを作成する
*/
void CModelObj::CreateVertexBuffer() {
	//メッシュ毎に一回作成すればよい
	if (mMyVertexBufferId > 0)
		return;
	//頂点バッファの作成
	glGenBuffers(1, &mMyVertexBufferId);
	//頂点バッファをバインド
	glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBufferId);
	//バインドしたバッファにデータを転送
	glBufferData(GL_ARRAY_BUFFER, sizeof(CMyVertex)*m_vertexNum, mpVertex, GL_STATIC_DRAW);
	//バインド解除
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//配列解放
//	delete[] mpVertex;
}
