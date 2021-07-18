#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"
#include "CMatrix.h"

/*
三角形クラス
*/
class CTriangle {
private:
	CVector mV[3]; //頂点座標
	CVector mN[3]; //法線
	CVector mUv[3]; //テクスチャマッピング
	int mMaterialIdx; //マテリアル番号
public:
	void MaterialIdx(int idx);
	int MaterialIdx();
	//頂点座標を得る
	const CVector& V0() const;
	const CVector& V1() const;
	const CVector& V2() const;
	//法線を得る
	const CVector& N0() const;
	const CVector& N1() const;
	const CVector& N2() const;
	//UVを得る
	const CVector& UV0() const;
	const CVector& UV1() const;
	const CVector& UV2() const;
	//UV設定
	//SetUV(const CVector &v0, const CVector &v1, const CVector &v2)
	void SetUv(const CVector& v0, const CVector& v1, const CVector& v2);
	//頂点座標設定
	//SetVertex(頂点1, 頂点2, 頂点3)
	void SetVertex(const CVector &v0, const CVector &v1, const CVector &v2);
	//法線設定
	//SetNormal(法線ベクトル)
	void SetNormal(const CVector &n);
	//SetNormal(法線ベクトル1, 法線ベクトル2, 法線ベクトル3)
	void SetNormal(const CVector &v0, const CVector &v1, const CVector &v2);
	//描画
	void Render();
	//描画
	void Render(const CMatrix &m);
};

#endif
