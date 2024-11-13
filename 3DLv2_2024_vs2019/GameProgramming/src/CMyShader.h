#ifndef CMYSHADER_H
#define CMYSHADER_H

#include "CShader.h"
#include <vector>

class CModelX;
class CMaterial;
class CMesh;
class CMatrix;
class CModel;

class CMyShader : public CShader {
	//ƒ}ƒeƒŠƒAƒ‹‚Ìİ’è
	void SetShader(CMaterial* material);
	//•`‰æˆ—
	void Render(CModelX* model, CMesh* mesh, CMatrix* pCombinedMatrix);
public:
	//•`‰æˆ—
	void Render(CModelX* model, CMatrix* combinedMatrix);
	//	void Render(CModel *mesh);
};

class CMyShader2 : public CShader
{
public:
	void Update(
		int FrameSize,
		CMatrix* pSkinningMatrix,
		std::vector<CMaterial*>* pMaterials,
		GLuint VertexBufferId
	);
	void Render(
		int FrameSize,
		CMatrix* pSkinningMatrix,
		std::vector<CMaterial*>* pMaterials,
		GLuint VertexBufferId
	);
	void Render();
private:
	int mFrameSize;
	GLuint mVertexBufferId;
	CMatrix* mpSkinningMatrix;
	std::vector<CMaterial*>* mpMaterials;
	//int mVertexSize;
	//CVertex* mpVertex;
};

#endif
