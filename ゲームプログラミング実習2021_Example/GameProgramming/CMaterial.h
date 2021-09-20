#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"

#include "CModelX.h"

/*
マテリアルクラス
マテリアルのデータを扱う
*/
class CMaterial {
public:
	//マテリアル毎の頂点数
	int mVertexNum;
	//テクスチャ
	CTexture mTexture;
	//マテリアル名
	char mName[64];
	//拡散光の色RGBA
	float mDiffuse[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//テクスチャファイル名
	char* mpTextureFilename;

	CMaterial(CModelX* model);
	~CMaterial() {
		if (mpTextureFilename) {
			delete[] mpTextureFilename;
		}
		mpTextureFilename = nullptr;
	}

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
