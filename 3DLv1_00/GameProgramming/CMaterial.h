#ifndef CMATERIAL
#define CMATERIAL

class CMaterial {
public:
	char *mpName;
	float mAmbient[4];
	float mDiffuse[4];
	float mSpecular[4];
	float mEmission[4];
	float mShinness;
	int mVertexNo;

	CMaterial();
	~CMaterial();
	void SetMaterial();
};

#endif
