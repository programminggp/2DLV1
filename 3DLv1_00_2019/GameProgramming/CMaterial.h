#ifndef CMATERIAL_H
#define CMATERIAL_H
/*
マテリアルクラス
マテリアルのデータを扱う
*/
class CMaterial {
public:
	char mName[64];
	//diffuse
	float mDiffuse[4];
	//
	CMaterial();
	//マテリアルの適用
	void SetMaterial();
};


#endif
