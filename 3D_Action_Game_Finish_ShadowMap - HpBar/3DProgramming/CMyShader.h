#ifndef CMYSHADER_H
#define CMYSHADER_H

#include "CShader.h"

class CModelX;
class CMaterial;
class CMesh;
class CMatrix44;
class CModelObj;

class CMyShader : public CShader {
	//マテリアルの設定
	void SetShader(CMaterial *material);
	//描画処理
	void Render(CModelX *model, CMesh *mesh, CMatrix44 *pCombinedMatrix);
public:
	//描画処理
	void Render(CModelX *model, CMatrix44 *combinedMatrix);
	void Render(CModelObj *mesh);
};


#endif
