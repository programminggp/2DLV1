#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"

/*
モデルクラス
モデルデータの入力や表示
*/
class CModel {
public:

	//デフォルトコンストラクタ
	CModel();
	~CModel();

	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(char *obj, char *mtl);
	//描画
	void Render();
	//描画
	//Render(行列)
	void Render(const CMatrix &m);

	std::vector<CTriangle> Triangles() const;
private:
	//頂点配列
	float* mpVertex; //頂点座標
	float* mpNormal; //法線
	float* mpTextureCoord; //テクスチャマッピング
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	//マテリアルポインタの可変長配列
	std::vector<CMaterial*> mpMaterials;
	//テクスチャマッピングの保存(CVector型)
	std::vector<CVector> uv;
};

#endif
