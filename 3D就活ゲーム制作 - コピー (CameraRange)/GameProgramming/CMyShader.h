#ifndef CMYSHADER_H
#define CMYSHADER_H

#include "CShader.h"
#include "CVector.h"

class CModelX {};
class CMaterial;
class CMesh;
class CMatrix;
class CModel;

class CMyShader : public CShader {
	//�}�e���A���̐ݒ�
	void SetShader(CMaterial *material);
	//�`�揈��
//	void Render(CModelX *model, CMesh *mesh, CMatrix *pCombinedMatrix);
public:
	static CMyShader* Get()
	{
		static CMyShader shader;
		return &shader;
	}
	void Material(CMaterial* mat)
	{
		SetShader(mat);
	}
	void Enable();
	void Disable();
	//�`�揈��
//	void Render(CModelX *model, CMatrix *combinedMatrix);
//	void Render(CModel *mesh);
};

class CLight
{
	CVector mLight;
public:
	CLight()
		: mLight(0.5f, 1.0f, 0.5f)
	{}
	static CLight* getLight(int num) {
		CLight sLight;
		return &sLight;
	};
	CVector& getDir() {
		return mLight;
	}
};

#endif
