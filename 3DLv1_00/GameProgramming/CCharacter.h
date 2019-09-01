#ifndef CCHARACTER
#define CCHARACTER

#include "CVector.h"
#include "CMatrix.h"
#include "CModel.h"

class CCharacter {
public:
	CVector mPosition;
	CVector mRotation;
	CVector mScale;
	CMatrix mMatrix;
	CModel* mpModel;

	CCharacter();
	~CCharacter();

	void Init(CModel *model, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	void Update();
	void Render();
};

#endif
