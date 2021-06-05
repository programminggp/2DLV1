#ifndef CMATERIAL_H
#define CMATERIAL_H

#include "CTexture.h"
#include "glut.h"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
/*
CMaterial
マテリアルクラス
*/
class CMaterial {
public:
	char *mpName; 	//マテリアル名
	float mAmbient[4];
	float mDiffuse[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//テクスチャファイル名
	char *mpTextureFilename;
	//テクスチャID
	GLuint mTextureId;
	CTexture mTexture;

	CMaterial();

	~CMaterial() {
		SAFE_DELETE_ARRAY(mpName);
		SAFE_DELETE_ARRAY(mpTextureFilename);
	}
	//マテリアルを適用する
	void SetMaterial();
	//テクスチャを無効にする
	void UnSetMaterial();
};


#endif
