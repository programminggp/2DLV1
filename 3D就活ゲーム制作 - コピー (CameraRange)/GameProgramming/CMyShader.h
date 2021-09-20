#ifndef CMYSHADER_H
#define CMYSHADER_H

#include "CShader.h"

class CModelX;
class CMaterial;
class CMesh;
class CMatrix44;
class CModelObj;

class CMyShader : public CShader {
	//ƒ}ƒeƒŠƒAƒ‹‚Ìİ’è
	void SetShader(CMaterial *material);
	//•`‰æˆ—
	void Render(CModelX *model, CMesh *mesh, CMatrix44 *pCombinedMatrix);
public:
	//•`‰æˆ—
	void Render(CModelX *model, CMatrix44 *combinedMatrix);
	void Render(CModelObj *mesh);
};


#endif
