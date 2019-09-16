#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"
#include "CMatrix.h"

/*
三角形クラス
*/
class CTriangle {
public:
	CVector mV[3]; //頂点座標
	CVector mN; //法線
	//頂点座標設定
	//SetVertex(頂点1, 頂点2, 頂点3)
	void SetVertex(const CVector &v0, const CVector &v1, const CVector &v2);
	//法線設定
	//SetNormal(法線ベクトル)
	void SetNormal(const CVector &n);
	//描画
	void Render();
	//Render(行列)
	void Render(const CMatrix &m);
};

#endif
