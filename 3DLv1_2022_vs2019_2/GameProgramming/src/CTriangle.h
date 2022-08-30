#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"
/*
三角形クラス
*/
class CTriangle {
public:
	//マテリアル番号の取得
	int MaterialIdx();
	//マテリアル番号の設定
	//Material(マテリアル番号)
	void MaterialIdx(int idx);
	//Normal(法線ベクトル1, 法線ベクトル2, 法線ベクトル3)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2);
	//頂点座標設定
	//Vertex(頂点1, 頂点2, 頂点3)
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2);
	//法線設定
	//Normal(法線ベクトル)
	void Normal(const CVector& n);
	//描画
	void Render();
private:
	int mMaterialIdx; //マテリアル番号
	CVector mV[3]; //頂点座標
	CVector mN[3]; //法線
};
#endif
