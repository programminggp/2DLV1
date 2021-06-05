#ifndef OBJ_H
#define OBJ_H

#include <stdio.h>
#include <stdlib.h>
#include "glew.h"
#include "glut.h"

#include "CTexture.h"
#include "CVector3.h"
#include "CMatrix44.h"
#include "CTriangle.h"
#include <vector>

#include "CMaterial.h"
#include "CVertex.h"

#include "CMyShader.h"

class CModelObj {
private:
	std::vector<CTriangle> mTriangle; //三角形
	CVertex		*mpVertex;	//頂点配列
	int			m_vertexNum;//頂点数
	bool LoadMaterial(char *path);
	bool LoadMaterial(char *path, char *newmtl);

public:
	CMatrix44	mMatrix;//行列
	std::vector<CMaterial*> mMaterial;	//マテリアル
	//マテリアル毎の面数
	std::vector<int> mMaterialVertexCount;
	//頂点バッファ識別子
	GLuint	  mMyVertexBufferId;
	//頂点バッファの作成
	void CreateVertexBuffer();
	CMyShader mShader;

	CModelObj();
	~CModelObj();

	/*ファイル読み込み*/
	bool	Load(const char *path);
	/*描画処理*/
	void	Render();
	/*テクスチャ開放*/
	void	Release();
	//代入のオーバーライド
	CModelObj& operator=(const CModelObj &c) {
		m_vertexNum = c.m_vertexNum;

		if (mpVertex) {
			delete[] mpVertex;
		}
		//描画用頂点配列を作成
		mpVertex = new CVertex[c.m_vertexNum];
		memcpy(mpVertex, c.mpVertex, sizeof(CVertex) * c.m_vertexNum);

		return (*this);
	}

	/*三角形当たり判定追加*/
	void CModelObj::AddCollisionManager();
};

#endif