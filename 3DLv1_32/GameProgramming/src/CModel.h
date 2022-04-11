#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include<vector>
//CTriangleのインクルード
#include"CTriangle.h"
//マテリアルクラスのインクルード
#include"CMaterial.h"
//マトリックスクラスのインクルード
#include"CMatrix.h"
/*
モデルクラス
モデルデータの入力や表示
*/
class CModel {
public:
	//モデルファイルの入力
	//Load(モデルファイル名、マテリアルファイル名）
	void Load(char* obj, char* mtl);
	//描画
	//Render(行列)
	void Render();
	//描画
	//Render(行列)
	void Render(const CMatrix& m);
	//デストラクタ
	~CModel();
	//デフォルトコンストラクタ
	CModel();
private:
	//三角形の可変長配列
	std::vector<CTriangle>mTriangles;
	//マテリアルポインタの可変長配列
	std::vector<CMaterial*>mpMaterials;
	//頂点配列
	float* mpVertex;//頂点座標
	float* mpNormal;//法線
	float* mpTextureCoord;//テクスチャマッピング
};

#endif 

