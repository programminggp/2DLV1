#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include <vector>
#include "CTriangle.h"
#include "CMatrix.h"
//CMaterialのインクルード
#include "CMaterial.h"
/*
モデルクラス
モデルデータの入力や表示
*/
class CModel {
public:
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	//三角形の可変長配列
	std::vector<CMaterial> mMaterials;
	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(char *obj, char *mtl);
	//描画
	void Render();
	void Render(const CMatrix &m);
};

#endif
