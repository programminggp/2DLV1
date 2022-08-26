#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include <vector>
#include "CTriangle.h"

/*
モデルクラス
モデルデータの入力や表示
*/
class CModel {
public:
	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(char* obj, char* mtl);
	//描画
	void Render();

private:
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
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
