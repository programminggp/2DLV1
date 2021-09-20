#ifndef CMYSHADER_H
#define CMYSHADER_H

#include "CShader.h"

class CModelX;
class CMaterial;
class CMesh;
class CMatrix44;
class CModelObj;

class CMyShader : public CShader {
	//�}�e���A���̐ݒ�
	void SetShader(CMaterial *material);
	//�`�揈��
	void Render(CModelX *model, CMesh *mesh, CMatrix44 *pCombinedMatrix);
public:
	//�`�揈��
	void Render(CModelX *model, CMatrix44 *combinedMatrix);
	void Render(CModelObj *mesh);
};


#endif
