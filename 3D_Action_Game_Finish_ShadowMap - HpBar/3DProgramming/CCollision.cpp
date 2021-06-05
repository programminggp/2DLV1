#include "CCollision.h"
/*
球コライダと球コライダの衝突判定
true:衝突している　false:衝突していない
m:自分のコライダ　y:相手のコライダ
*/
bool CCollision::Sphere(CCollider *m, CCollider *y) {
	//中心から中心へのベクトルを求めます
	CVector3 dir = m->mPosition - y->mPosition;
	//中心距離と半径の合計を比較し、中心距離が小さければ
	//衝突しています
	return dir.length() < m->mRadius + y->mRadius;
}
/*
カプセルと三角形コライダの衝突判定
true:衝突している false:衝突していない
capsule:カプセルコライダ triangle:三角形コライダ
adjust:衝突しない位置までの移動量
*/
bool CCollision::CapsuleTriangle(CCollider *capsule, CCollider *triangle, CVector3 *adjust) {
	//カプセルキャストにキャスト
	CCapsuleCollider *c = (CCapsuleCollider*)capsule;
	//三角形コライダにキャスト
	CTriangleCollider *t = (CTriangleCollider*)triangle;
	//線分と三角形の衝突判定を呼ぶ
	if (LineTriangle(c->mV[0], c->mV[1], t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//下の球と三角形の衝突判定
	CVector3 center = (c->mV[1] - c->mV[0]).normalize() * c->mRadius + c->mV[0];
	if (SphereTriangle(center, c->mRadius, t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//上の球と三角形の衝突判定
	center = (c->mV[0] - c->mV[1]).normalize() * c->mRadius + c->mV[1];
	if (SphereTriangle(center, c->mRadius, t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//線分と三角形の衝突判定を呼ぶ
	if (LineTriangle(c->mV[2], c->mV[3], t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//線分と三角形の衝突判定を呼ぶ
	if (LineTriangle(c->mV[4], c->mV[5], t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	return false;
}
/*
線と三角形の衝突判定
true:衝突している false:衝突していない
p0,p1:線 p0下 p1上
v0,v1,v2:三角形
adjust:衝突しない位置までの移動量
*/
bool CCollision::LineTriangle(const CVector3 &p0, const CVector3 &p1, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust) {
	//線と面の交差を判定
	CVector3 v01 = v1 - v0;
	CVector3 v02 = v2 - v0;
	CVector3 normal = v01.Cross(v02); //法線（面の向き）
	CVector3 vp00 = p0 - v0;
	CVector3 vp01 = p1 - v0;
	float dot0 = vp00.dot(normal);
	float dot1 = vp01.dot(normal);
	if (dot0 * dot1 >= 0) {
		//交差していない
		return false;
	}
	//交差する点を算出
	//どちらも絶対値にする
	if (dot0 < 0) {
		dot0 *= -1;
	}
	else {
		dot1 *= -1;
	}
	dot1 += dot0;	//長さを求める
	dot0 = dot0 / dot1;	//p0→面までの割合
	//交点算出
	CVector3 cross = p0 + (p1 - p0) * dot0;
	//交点が三角形内か判定
	if (PointInTriangle(cross, v0, v1, v2, normal)) {
		//三角形内である
		*adjust = normal * (((p1 - p0) * dot0).dot(normal));
		return true;
	}
	//三角形の外
	return false;
}
/*
点が三角形内か判定する
true;三角形内 false:三角形外
p0:点座標
v0v1v2:三角形の頂点座標
n:三角形の法線ベクトル
*/
bool CCollision::PointInTriangle(const CVector3 &p0, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &n) {
	CVector3 pvn;
	//v1←v0の左へ点があれば法線上向き
	pvn = (v1 - v0).Cross(p0 - v0);
	if (pvn.dot(n) < 0) return false;
	//v2←v1の左へ点があれば法線上向き
	pvn = (v2 - v1).Cross(p0 - v1);
	if (pvn.dot(n) < 0) return false;
	//v0←v2の左へ点があれば法線上向き
	pvn = (v0 - v2).Cross(p0 - v2);
	if (pvn.dot(n) < 0) return false;
	return true;
}
//30
/*
球と三角形の衝突判定
true:衝突している false:衝突していない
c:球の中心座標 r:球の半径
v0,v1,v2:三角形
adjust:衝突しない位置までの移動量
*/
bool CCollision::SphereTriangle(const CVector3 &c, float r, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust) {
	//面の法線計算
	CVector3 v01 = v1 - v0;
	CVector3 v02 = v2 - v0;
	CVector3 normal = v01.Cross(v02); //法線（面の向き）
	//球と面との接点が三角形内か判定する
	//球の中心から接点へかけての線分の端を求める
	CVector3 p0 = c + normal * -r;
	CVector3 p1 = c + normal * r;
	//線と三角形の衝突処理
	return LineTriangle(p0, p1, v0, v1, v2, adjust);
}
