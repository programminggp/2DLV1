#ifndef CMATERIAL
#define CMATERIAL

#include "CTexture.h"

class CMaterial {
public:
	char *mpName;
	float mAmbient[4];
	float mDiffuse[4];
	float mSpecular[4];
	float mEmission[4];
	float mShinness;
	int mVertexNo;

	CTexture mTexture;

	CMaterial();
	~CMaterial();
	void SetMaterial();
	void UnSetMaterial();

	void SetTexture(char *file);

};

#endif
