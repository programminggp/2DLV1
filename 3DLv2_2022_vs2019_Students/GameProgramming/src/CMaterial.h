#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"
#include "CModelX.h"
#include "CMyShader.h"

#define MATERIAL_NAME_LEN 64

/*
マテリアルクラス
マテリアルのデータを扱う
*/
class CMaterial {
	friend CMyShader;
public:
	CMaterial(CModelX* model);
	~CMaterial();

//	void Diffuse(float r, float g, float b, float a);
	//頂点数の設定
	//VertexNum(頂点数)
	void VertexNum(int num);
	//頂点数の取得
	int VertexNum();
	//mDiffuse配列の取得
	float* Diffuse();
	//マテリアルの名前の取得
	char* Name();
	//マテリアルの名前を設定する
	//Name(マテリアルの名前)
	void Name(char* name);
	//テクスチャの取得
	CTexture* Texture();
	//デフォルトコンストラクタ
	CMaterial();
	//マテリアルを有効にする
	void Enabled();
	//テクスチャを読み込む
//	void LoadTexture(char *file);
	//マテリアルを無効にする
	void Disabled();
private:
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//テクスチャファイル名
	char* mpTextureFilename;

	//マテリアル毎の頂点数
	int mVertexNum;
	//テクスチャ
	CTexture mTexture;
	//マテリアル名
	char mName[MATERIAL_NAME_LEN];
	//拡散光の色RGBA
	float mDiffuse[4];
};

#endif
