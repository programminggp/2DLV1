#ifndef CBOX
#define CBOX

#include "CTriangle.h"
#include "CMaterial.h"

class CBox {
public:
	CTriangle mT[12];

	CMaterial mMaterial;

	void Render(const CMatrix &m);
	void Set(float x, float y, float z, float w, float h, float d);
};


#endif
