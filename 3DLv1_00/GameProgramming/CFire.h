#ifndef CFIRE
#define CFIRE

#include "CTriangle.h"
#include "CCharacter.h"
#include "CMaterial.h"

class CFire : public CCharacter {
public:
	CTriangle mT[2];
	CMaterial mMaterial;
	void SetSize(float w, float h);
	void Render();
	void SetTexture(char *tga);
	void SetDiffuse(float r, float g, float b, float a);
	CFire();
	void Update();
};

#endif
