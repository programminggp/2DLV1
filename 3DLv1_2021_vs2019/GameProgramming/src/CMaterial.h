#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"

#define MATERIAL_NAME_LEN 64

/*
マテリアルクラス
マテリアルのデータを扱う
*/
class CMaterial {
private:
	//マテリアル毎の頂点数
	int mVertexNum;
	//テクスチャ
	CTexture mTexture;
	//マテリアル名
	char mName[MATERIAL_NAME_LEN];
	//拡散光の色RGBA
	float mDiffuse[4];
public:
	void Diffuse(float r, float g, float b, float a);
	void VertexNum(int num);
	int VertexNum();
	//mDiffuse配列の取得
	float* Diffuse();
	//マテリアルの名前の取得
	char* Name();
	//マテリアルの名前を設定する
	//Name(マテリアルの名前)
	void Name(char* name);
	CTexture& Texture();
	//デフォルトコンストラクタ
	CMaterial();
	//マテリアルを有効にする
	void Enabled();
	//テクスチャを読み込む
	void LoadTexture(char *file);
	//マテリアルを無効にする
	void Disabled();
};

#endif
