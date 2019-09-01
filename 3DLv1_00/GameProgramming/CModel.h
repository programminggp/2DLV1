#ifndef CMODEL
#define CMODEL

#include "CTriangle.h"
#include "CMaterial.h"
#include <vector>

class CModel {
public:
	std::vector<CTriangle*> mTriangles;
	std::vector<CMaterial*> mMaterials;

	float *mpVertex;
	float *mpNormal;
	float *mpTextureCoord;

	CModel();
	~CModel();

	void Load(char *obj, char *mtl);
	void Render(const CMatrix &matrix);

};


#endif
