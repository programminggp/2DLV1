#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"

void CCollider::Matrix(CMatrix* m)
{
	mpMatrix = m;
}

CCharacter* CCollider::Parent()
{
	return mpParent;
}

CCollider::CCollider()
: mpParent(nullptr)
, mpMatrix(&mMatrix)
, mType(ESPHERE)
, mTag(EBODY)
, mRadius(0)
{
	//コリジョンマネージャに追加
	CCollisionManager::Get()->Add(this);
}

//コンストラクタ
//CCollider(親, 位置, 回転, 拡縮, 半径)
CCollider::CCollider(CCharacter *parent, CMatrix *matrix,
	const CVector& position, float radius)
	: CCollider()
{
	//親設定
	mpParent = parent;
	//親行列設定
	mpMatrix = matrix;
	//CTransform設定
	mPosition = position; //位置
	//半径設定
	mRadius = radius;
}

//描画
void CCollider::Render() {
	glPushMatrix();
	//コライダの中心座標を計算
	//自分の座標×親の変換行列を掛ける
	CVector pos = mPosition * *mpMatrix;
	//中心座標へ移動
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}

CCollider::~CCollider()
{
	CCollisionManager::Get()->Remove(this);
}
//衝突判定
//Collision(コライダ1, コライダ2)
//retrun:true（衝突している）false(衝突していない)
bool CCollider::Collision(CCollider *m, CCollider *o) {
	//各コライダの中心座標を求める
	//原点×コライダの変換行列×親の変換行列
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//中心から中心へのベクトルを求める
	mpos = mpos - opos;
	//中心の距離が半径の合計より小さいと衝突
	if (m->mRadius + o->mRadius > mpos.Length()) {
		//衝突している
		return  true;
	}
	//衝突していない
	return false;
}

bool CCollider::CollisionTriangleLine(CCollider *t, CCollider *l, CVector *a) {
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//三角の頂点から線分始点へのベクトルを求める
	CVector v0sv = sv - v[0];
	//三角の頂点から線分終点へのベクトルを求める
	CVector v0ev = ev - v[0];
	//線分が面と交差しているか内積で確認する
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//プラスは交差してない
	if (dots * dote >= 0.0f) {
		//衝突してない（調整不要）
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//線分は面と交差している

	//面と線分の交点を求める
	//交点の計算
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));

	//交点が三角形内なら衝突している
	//頂点1頂点2ベクトルと頂点1交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点2頂点3ベクトルと頂点2交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//課題３２
	//頂点3頂点1ベクトルと頂点3交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//調整値計算（衝突しない位置まで戻す）
	if (dots < 0.0f) {
		//始点が裏面
		*a = normal * -dots; //斜面を滑る
		*a = cross - sv; //斜面を滑らない
	}
	else {
		//終点が裏面
		*a = normal * -dote; //斜面を滑る
		*a = cross - ev; //斜面を滑らない
	}
	return true;
}
//CollisionTriangleSphere(三角コライダ, 球コライダ, 調整値)
//retrun:true（衝突している）false(衝突していない)
//調整値:衝突しない位置まで戻す値
bool CCollider::CollisionTriangleSphere(CCollider *t, CCollider *s, CVector *a)
{
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//線コライダをワールド座標で作成
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(NULL, NULL, sv, ev);
	//三角コライダと線コライダの衝突処理
	return CollisionTriangleLine(t, &line, a);
}

//優先度の変更
void CCollider::ChangePriority()
{
	//自分の座標×親の変換行列を掛ける
	CVector pos = mPosition * *mpMatrix;
	//ベクトルの長さが優先度
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //一旦削除
	CCollisionManager::Get()->Add(this); //追加
}

CCollider::EType CCollider::Type()
{
	return mType;
}

CCollider::ETag CCollider::Tag()
{
	return mTag;
}

void CCollider::Tag(ETag tag)
{
	mTag = tag;
}

//カプセルコライダ同士の衝突判定
//CollisionCapsule(コライダ1, コライダ2, 調整ベクトル)
bool CCollider::CollisionCapsule(CCollider* m, CCollider* o, CVector* adjust)
{
	CVector mV0 = m->mV[0] * *m->mpMatrix;
	CVector mV1 = m->mV[1] * *m->mpMatrix;
	CVector oV0 = o->mV[0] * *o->mpMatrix;
	CVector oV1 = o->mV[1] * *o->mpMatrix;
	CVector r1 = (mV1 - mV0).Normalize() * m->mRadius;
	CVector r2 = (oV1 - oV0).Normalize() * o->mRadius;
	//最短のベクトルを求める
	*adjust = VectorLineMinDist(mV0 + r1, mV1 - r1, oV0 + r2, oV1 - r2);
	if (adjust->Length() == 0.0f)
		return true;
	if (adjust->Length() < m->mRadius + o->mRadius)
	{
		*adjust = adjust->Normalize() * (m->mRadius + o->mRadius) - *adjust;
		return true;
	}
	return false;
}
//おおよそゼロか？
bool NearZero(float f)
{
	if (fabs(f) <= 0.001f)
		return true;
	return false;
}
//2線間の最短ベクトルを求める
//VectorLineMinDist(線1始点, 線1終点, 線2始点, 線2終点)
CVector CCollider::VectorLineMinDist(const CVector& Start1, const CVector& End1, const CVector& Start2, const CVector& End2)
{
	CVector   u = End1 - Start1;
	CVector   v = End2 - Start2;
	CVector   w = Start1 - Start2;
	float    a = u.Dot(u);         // always >= 0
	float    b = u.Dot(v);
	float    c = v.Dot(v);         // always >= 0
	float    d = u.Dot(w);
	float    e = v.Dot(w);
	float    D = a * c - b * b;        // always >= 0
	float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

								   // compute the line parameters of the two closest points
	if (NearZero(D)) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (NearZero(sN) ? 0.0f : sN / sD);
	tc = (NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	CVector dP = w + (u * sc) - (v * tc);  // =  S1(sc) - S2(tc)

	return dP;   // return the closest distance 

}

