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
	//頂点配列
	float *mpVertex; //頂点座標
	float *mpNormal; //法線
	float *mpTextureCoord; //テクスチャマッピング
	//デフォルトコンストラクタ
	CModel();
	//デストラクタ
	~CModel();
	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(char *obj, char *mtl);
	//描画
	void Render();
	//Render(合成行列)
	void Render(const CMatrix &m);
};

#endif
