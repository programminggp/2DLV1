#ifndef CMODEL_H
#define CMODEL_H
/*
モデルクラス
モデルデータの入力や表示
*/
//vectorのインクルード
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"
#include "CMyShader.h"

class CModel {
	friend CMyShader;
public:
	GLuint mMyVertexBufferId;
	const std::vector<CTriangle>& Triangles() const;
	//モデルファイルの入力
	//Load(モデルファイル名、マテリアルファイル名)
	void Load(char* obj, char* mtl);
	//描画
	void Render();
	~CModel();
	//描画
	//Render(行列)
	void Render(const CMatrix& m);
private:
	CMyShader mShader;
	//頂点の配列
	CVertex* mpVertexes;
	void CreateVertexBuiffer();
	//マテリアルポインタの可変長配列
	std::vector<CMaterial*>mpMaterials;
	//三角形の可変長配列
	std::vector<CTriangle>mTriangles;
};

#endif
