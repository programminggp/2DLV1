#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"

/*
モデルクラス
モデルデータの入力や表示
*/
class CModel {
public:
	std::vector<CTriangle> Triangles() const;
	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(char* obj, char* mtl);
	//描画
	void Render();
	~CModel();
	//描画
	//Render(行列)
	void Render(const CMatrix& m);
private:
	//マテリアルポインタの可変長配列
	std::vector<CMaterial*> mpMaterials;
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	//頂点の配列
	CVertex* mpVertexes;
	void CreateVertexBuffer();
};

#include "CVertex.h"
#include <vector>

class CModelTest
{
public:
	CModelTest();
	void Render();

	CVertex mVertex[6];
	std::vector<CVertex> mVector;

};

#endif
