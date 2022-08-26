#include "CModel.h"
#include "glut.h"

#define V1 CVector(1.0f, 0.0f, 0.0f)
#define V2 CVector(0.0f, 1.0f, 0.0f)
#define V3 CVector(0.0f, 0.0f, 1.0f)
#define V4 CVector(-1.0f, 0.0f, 0.0f)
#define N1 CVector(0.5412, 0.7071, 0.5412)
#define N2 CVector(-0.5412, 0.7071, 0.5412)

CModelTest::CModelTest()
{
	mVertex[0].mPosition = V1;
	mVertex[0].mNormal = N1;
	mVertex[1].mPosition = V2;
	mVertex[1].mNormal = N1;
	mVertex[2].mPosition = V3;
	mVertex[2].mNormal = N1;

	mVertex[3].mPosition = V2;
	mVertex[3].mNormal = N2;
	mVertex[4].mPosition = V4;
	mVertex[4].mNormal = N2;
	mVertex[5].mPosition = V3;
	mVertex[5].mNormal = N2;

	for (int i = 0; i < 6; i++)
	{
		mVector.push_back(mVertex[i]);
	}
}

void CModelTest::Render()
{
	//頂点座標の位置を設定
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)&mVector[0].mPosition);
	//法線ベクトルの位置を設定
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), (void*)&mVector[0].mNormal);

	//描画位置からのデータで三角形を描画します
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//頂点座標の配列を無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	//法線の配列を無効にする
	glDisableClientState(GL_NORMAL_ARRAY);
}

//モデルファイルの入力
//Load(モデルファイル名, マテリアルファイル名)
void CModel::Load(char* obj, char* mtl) {
	//ファイルポインタ変数の作成
	FILE* fp;
	//ファイルからデータを入力
	//入力エリアを作成する
	char buf[256];

	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープンできない時はNULLを返す
	fp = fopen(mtl, "r");
	//ファイルオープンエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラー出力して戻る
		printf("%s file open error￥n", mtl);
		return;
	}

	//ファイルから1行入力
	//fgets(入力エリア,エリアサイズ,ファイルポインタ)
	//ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//入力した値をコンソールに出力する
		printf("%s", buf);
	}

	//ファイルのクローズ
	fclose(fp);

	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープンできない時はNULLを返す
	fp = fopen(obj, "r");
	//ファイルオープンエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラー出力して戻る
		printf("%s file open error￥n", mtl);
		return;
	}

	//ファイルから1行入力
	//fgets(入力エリア,エリアサイズ,ファイルポインタ)
	//ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//入力した値をコンソールに出力する
		printf("%s", buf);
	}

	//ファイルのクローズ
	fclose(fp);
}
