#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#include "CColliderCapsule.h"

void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this); //一旦削除
	CCollisionManager::Instance()->Add(this); //追加
}

bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a)
{
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	//v[0] = t->mV[0] * *t->mpMatrix;
	//v[1] = t->mV[1] * *t->mpMatrix;
	//v[2] = t->mV[2] * *t->mpMatrix;
	//面の法線を、外積を正規化して求める
	//CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	CVector normal = t->mV[3];
	//線コライダをワールド座標で作成
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(nullptr, nullptr, sv, ev);
	//三角コライダと線コライダの衝突処理
	return CollisionTriangleLine(t, &line, a);
}

CCollider::CCollider()
	: mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(ESPHERE)
	, mRadius(0)
{
	//コリジョンマネージャに追加
	CCollisionManager::Instance()->Add(this);
}

//衝突判定
//Collision(コライダ1, コライダ2)
//retrun:true（衝突している）false(衝突していない)
bool CCollider::Collision(CCollider* m, CCollider* o) {
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

CCollider::~CCollider() {
	//コリジョンリストから削除
	CCollisionManager::Instance()->Remove(this);
}

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius, ETag tag) 
	: CCollider() 
{
	mTag = tag;//タグの設定
	//親設定
	mpParent = parent;
	//親行列設定
	mpMatrix = matrix;
	//CTransform設定
	mPosition = position; //位置
	//半径設定
	mRadius = radius;
	//コリジョンマネージャyに追加
	//CCollisionManager::Instance()->Add(this);
}

CCharacter3* CCollider::Parent()
{
	return mpParent;
}

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

CCollider::ETag CCollider::Tag()
{
	return mTag;
}

CCollider::EType CCollider::Type()
{
	return mType;
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	//v[0] = t->mV[0] * *t->mpMatrix;
	//v[1] = t->mV[1] * *t->mpMatrix;
	//v[2] = t->mV[2] * *t->mpMatrix;
	v[0] = t->mV[0];
	v[1] = t->mV[1];
	v[2] = t->mV[2];
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//面の法線を、外積を正規化して求める
//	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	CVector normal = t->mV[3];
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
		*a = normal * -dots;
	}
	else {
		//終点が裏面
		*a = normal * -dote;
	}
	return true;
}

void CCollider::Matrix(CMatrix* m)
{
	mpMatrix = m;
}



bool CollisionPointTriangle(
	const CVector& p, 
	const CVector& v0, 
	const CVector& v1, 
	const CVector& v2, 
	const CVector& normal
)
{
	if (normal.Dot((v1 - v0).Cross(p - v0)) < 0.0f)
	{
		return false;
	}
	if (normal.Dot((v2 - v1).Cross(p - v1)) < 0.0f)
	{
		return false;
	}
	if (normal.Dot((v0 - v2).Cross(p - v2)) < 0.0f)
	{
		return false;
	}
	return true;
}


bool CCollider::CollisionCapsuleTriangle(CCollider* capsule, CCollider* triangle, CVector* adjust)
{
	float dist;
	dist = triangle->mV[3].Dot(capsule->mV[0] - triangle->mV[0]);
	if (dist < capsule->mRadius)
	{
		if (CollisionPointTriangle((capsule->mV[0] - triangle->mV[3] * dist), triangle->mV[0], triangle->mV[1], triangle->mV[2], triangle->mV[3]))
		{
			float dist2 = triangle->mV[3].Dot(capsule->mV[1] - triangle->mV[0]);
			if (dist2 < capsule->mRadius)
			{
				if (CollisionPointTriangle((capsule->mV[1] - triangle->mV[3] * dist2), triangle->mV[0], triangle->mV[1], triangle->mV[2], triangle->mV[3]))
				{
					if (dist > dist2)
					{
						*adjust = triangle->mV[3] * (capsule->mRadius - dist2);
						return true;
					}
				}
			}
			*adjust = triangle->mV[3] * (capsule->mRadius - dist);
			return true;
		}
	}
	else {
		dist = triangle->mV[3].Dot(capsule->mV[1] - triangle->mV[0]);
		if (dist < capsule->mRadius)
		{
			if (CollisionPointTriangle((capsule->mV[1] - triangle->mV[3] * dist), triangle->mV[0], triangle->mV[1], triangle->mV[2], triangle->mV[3]))
			{
				*adjust = triangle->mV[3] * (capsule->mRadius - dist);
				return true;
			}
		}
	}
	return false;
}
//CalcCalcPointLineDist(点, 始点, 終点, 線上の最短点, 割合)
//点と線（始点、終点）の最短距離を求める
float CalcPointLineDist(const CVector& p, const CVector& s, const CVector& e, CVector* mp, float* t)
{
	*t = 0.0f; //割合の初期化
	CVector v = e - s; //始点から終点へのベクトルを求める
	float dvv = v.Dot(v); //ベクトルの長さの2乗を求める
	if (dvv > 0.0f) {
		*t = v.Dot(p - s) / dvv; //線上の垂線となる点の割合を求める
		// 上の式の説明
		// dot(v, p-sp) は |v||p-sp|cosΘ
		// dvvは|v|の２乗
		// 上の計算で、tは |p-sp|cosΘ / |v|となる。
		// つまりtは「dotで投影した長さ÷vの長さ」という割合になる
	}
	*mp = s + v * *t; //線上の垂線となる点を求める
	return (p - *mp).Length(); //垂線の長さを返す
}

//float calcLineLineDist(CCollider* m, CCollider* o, CVector* mp1, CVector* mp2, float* t1, float* t2)
//CalcLineLineDist(始点1, 終点1, 始点2, 終点2, 交点1, 交点2, 比率1, 比率2)
//2線間の最短距離を返す
float CalcLineLineDist(
	const CVector& s1, //始点1
	const CVector& e1, //終点1
	const CVector& s2, //始点2
	const CVector& e2, //終点2
	CVector* mp1, //交点1
	CVector* mp2, //交点2
	float* t1, //比率1
	float* t2  //比率2
)
{
	CVector v1 = e1 - s1;
	CVector v2 = e2 - s2;

	//2直線が平行
	if (v1.Cross(v2).Length() < 0.000001f) {
		//線分1の始点から直線2までの最短距離問題に帰着する
		*t1 = 0.0f;
		*mp1 = s1;
		float dist = CalcPointLineDist(*mp1, s2, e2, mp2, t2);
		return dist;
	}
	//2直線が平行でない
//互いに垂直になるような最短線の端点mp1,mp2を求める
//次の順で求めていく t1 -> mp1 -> t2 -> mp2
//最初のt1を求める式の詳細は下のコメントにある
/*
両直線の最短距離を結ぶ線は、両直線に共通の垂線となる。。。その垂線の端点mp1,mp2
mp1 = s1.sp + s1.v * t1
mp2 = s2.sp + s2.v * t2

t2を求める式
t2 = dot(s2.v,mp1 - s2.sp) / dot(s2.v,s2.v)
最終的にt1を求めたいので、t2をt1で表現するためmp1を置き換える
t2 = dot(s2.v, s1.sp + s1.v * t1 - s2.sp) / dot(s2.v, s2.v)
分配してt1を計算しやすくしておく
t2 = dot(s2.v, s1.sp - s2.sp + s1.v * t1) / dot(s2.v, s2.v)
t2 = { dot(s2.v, s1.sp - s2.sp) + dot(s2.v, s1.v) * t1 } / dot(s2.v, s2.v)


次の式からt1を導く。バカ丁寧に変形していきます。
0 = dot(s1.v,mp1-mp2)
=dot(s1.v,(s1.sp+s1.v*t1)-(s2.sp+s2.v*t2))
=dot(s1.v, s1.sp-s2.sp + s1.v*t1 - s2.v*t2)
分配してt2を外に出す
=dot(s1.v, s1.sp-s2.sp) + dot(s1.v,s1.v)*t1 - dot(s1.v,s2.v)*t2 )
t2を消す
=dot(s1.v, s1.sp-s2.sp) + dot(s1.v,s1.v)*t1 - dot(s1.v,s2.v)*{ dot(s2.v, s1.sp - s2.sp) + dot(s2.v, s1.v) * t1 } / dot(s2.v, s2.v)
一番右の分母を消す（dot(s2.v, s2.v)を掛ける）
=dot(s2.v,s2.v)*dot(s1.v, s1.sp-s2.sp) + dot(s2.v,s2.v)*dot(s1.v,s1.v)*t1 - dot(s1.v,s2.v) * {dot(s2.v, s1.sp - s2.sp) + dot(s2.v, s1.v) * t1}
中かっこを消す
=dot(s2.v,s2.v)*dot(s1.v, s1.sp-s2.sp) + dot(s2.v,s2.v)*dot(s1.v,s1.v)*t1 - dot(s1.v,s2.v) * dot(s2.v, s1.sp - s2.sp) - dot(s1.v,s2.v) * dot(s2.v,s1.v) * t1
t1でくくる
=dot(s2.v,s2.v)*dot(s1.v, s1.sp-s2.sp)  - dot(s1.v,s2.v) * dot(s2.v, s1.sp - s2.sp) + { dot(s2.v,s2.v)*dot(s1.v,s1.v) - dot(s1.v,s2.v) * dot(s2.v,s1.v) }* t1
移項
-{dot(s2.v,s2.v)*dot(s1.v,s1.v) - dot(s1.v,s2.v) * dot(s2.v,s1.v)}*t1 = dot(s2.v,s2.v)*dot(s1.v, s1.sp-s2.sp)  - dot(s1.v,s2.v) * dot(s2.v, s1.sp - s2.sp)
t1=にして、整理していく
t1 = dot(s2.v,s2.v)*dot(s1.v, s1.sp-s2.sp)  - dot(s1.v,s2.v) * dot(s2.v, s1.sp - s2.sp) / - {dot(s2.v,s2.v)*dot(s1.v,s1.v) - dot(s1.v,s2.v) * dot(s2.v,s1.v)}
t1 = -dot(s2.v,s2.v)*dot(s1.v, s1.sp-s2.sp)  + dot(s1.v,s2.v) * dot(s2.v, s1.sp - s2.sp) / dot(s2.v,s2.v)*dot(s1.v,s1.v) - dot(s1.v,s2.v) * dot(s2.v,s1.v)
t1 = dot(s1.v,s2.v) * dot(s2.v, s1.sp - s2.sp) -　dot(s2.v,s2.v) * dot(s1.v, s1.sp-s2.sp)  / dot(s1.v,s1.v) * dot(s2.v,s2.v) - dot(s1.v,s2.v) * dot(s1.v,s2.v)
*/
	float dv1v2 = v1.Dot(v2);
	float dv1v1 = v1.Dot(v1);
	float dv2v2 = v2.Dot(v2);
	CVector vs2s1 = s1 - s2;
	//比率1を求める
	*t1 = (dv1v2 * v2.Dot(vs2s1) - dv2v2 * v1.Dot(vs2s1))
		/ (dv1v1 * dv2v2 - dv1v2 * dv1v2);
	//交点1を求める
	*mp1 = s1 + v1 * *t1;
	//比率2を求める
	*t2 = v2.Dot(*mp1 - s2) / dv2v2;
	//交点2を求める
	*mp2 = s2 + v2 * *t2;
	//最短距離を返す
	return (*mp2 - *mp1).Length();
}

//0～1の間にクランプ(値を強制的にある範囲内にすること)
void clamp0to1(float& v) {
	if (v < 0.0f)  v = 0.0f;
	else if (v > 1.0f)  v = 1.0f;
}

//2線分間の最短距離
float CalcSegmentSegmentDist
(
//	CCollider& s1,//線分1
//	CCollider& s2,//線分2
	const CVector& s1, const CVector& e1, //線分1
	const CVector& s2, const CVector& e2, //線分2
	CVector* mp1, //最短線の端点1(始点や終点になることもある)
	CVector* mp2 //最短線の端点2(始点や終点になることもある)
//	float& t1, //s1.vの長さを1とした時の「s1.spからmp1までの長さ」の割合
//	float& t2  //s2.vの長さを1とした時の「s2.spからmp2までの長さ」の割合
)
{
	float dist = 0, t1, t2;

	//{
	//	// s1.vが縮退している？
	//	if (s1.v.magSq() < 0.000001f) {
	//		// s2.vも縮退？
	//		if (s2.v.magSq() < 0.000001f) {
	//			// 点と点の距離の問題に帰着
	//			dist = (s2.sp - s1.sp).mag();
	//			mp1 = s1.sp;
	//			mp2 = s2.sp;
	//			t1 = t2 = 0.0f;
	//			segment(mp1, mp2, COLOR(255, 255, 255), 10);
	//			return dist;
	//		}
	//		else {
	//			// s1.spとs2.vの最短問題に帰着
	//			dist = calcPointSegmentDist(s1.sp, s2, mp2, t2);
	//			mp1 = s1.sp;
	//			t1 = 0.0f;
	//			clamp0to1(t2);
	//			segment(mp1, mp2, COLOR(255, 255, 255), 10);
	//			return dist;
	//		}
	//	}
	//	// s2.vが縮退している？
	//	else if (s2.v.magSq() < 0.000001f) {
	//		// s2.spとsv1の最短問題に帰着
	//		float dist = calcPointSegmentDist(s2.sp, s1, mp1, t1);
	//		mp2 = s2.sp;
	//		clamp0to1(t1);
	//		t2 = 0.0f;
	//		segment(mp1, mp2, COLOR(255, 255, 255), 10);
	//		return dist;
	//	}
	//}

	//----------------------------------------------------------------
	//とりあえず2直線間の最短距離,mp1,mp2,t1,t2を求めてみる
	dist = CalcLineLineDist(s1, e1, s2, e2, mp1, mp2, &t1, &t2);
	if (0.0f <= t1 && t1 <= 1.0f &&
		0.0f <= t2 && t2 <= 1.0f) {
		//mp1,mp2が両方とも線分内にあった
		return dist;
	}
	//mp1,mp2の両方、またはどちらかが線分内になかったので次へ

	//----------------------------------------------------------------
	//mp1,t1を求め直す ⇒ t2を0～1にクランプしてmp2からs1.vに垂線を降ろしてみる
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	dist = CalcPointLineDist(*mp2, s1, e1, mp1, &t1);
	if (0.0f <= t1 && t1 <= 1.0f) {
		//mp1が線分内にあった
		return dist;
	}
	//mp1が線分内になかったので次へ

	//----------------------------------------------------------------
	//mp2,t2を求め直す ⇒ t1を0～1にクランプしてmp1からs2.vに垂線を降ろしてみる
	clamp0to1(t1);
	*mp1 = s1 + (e1 - s1) * t1;
	dist = CalcPointLineDist(*mp1, s2, e2, mp2, &t2);
	if (0.0f <= t2 && t2 <= 1.0f) {
		//mp2が線分内にあった
		return dist;
	}
	//mp2が線分内になかったので次へ

	//----------------------------------------------------------------
	//t2をクランプしてmp2を再計算すると、mp1からmp2までが最短
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	return (*mp2 - *mp1).Length();
}

bool CCollider::CollisionCapsuleCapsule(CCollider* m, CCollider* o, CVector* adjust)
{
	//if (m->mV[2].Length() < 0.000001f)
	//{
	//}
	//CCollider s1 = *m;
	//CCollider s2 = *o;
	//s1.mV[0] = s1.mV[0] * *s1.mpMatrix;
	//s1.mV[1] = s1.mV[1] * *s1.mpMatrix;
	//s2.mV[0] = s2.mV[0] * *s2.mpMatrix;
	//s2.mV[1] = s2.mV[1] * *s2.mpMatrix;
	
	//m->mV[0] = ((CColliderCapsule*)m)->Sp() * *m->mpMatrix;
	//m->mV[1] = ((CColliderCapsule*)m)->Ep() * *m->mpMatrix;
	//m->mV[2] = m->mV[1] - m->mV[0];
	//o->mV[0] = ((CColliderCapsule*)o)->Sp() * *o->mpMatrix;
	//o->mV[1] = ((CColliderCapsule*)o)->Ep() * *o->mpMatrix;
	//o->mV[2] = o->mV[1] - o->mV[0];

	CVector mp1, mp2;
	float radius = m->mRadius + o->mRadius;

	*adjust = CVector();
	if (CalcSegmentSegmentDist(m->V(0), m->V(1), o->V(0), o->V(1), &mp1, &mp2) < radius)
	{
		*adjust = mp1 - mp2;
		float len = radius - adjust->Length();
		*adjust = adjust->Normalize() * len;
		return true;
	}
	return false;
}


//優先度の変更
void CCollider::ChangePriority()
{
	//自分の座標×親の変換行列を掛けてワールド座標を求める
	CVector pos = mPosition * *mpMatrix;
	//ベクトルの長さが優先度
	ChangePriority(pos.Length());
	//mPriority = pos.Length();
	//CCollisionManager::Instance()->Remove(this); //一旦削除
	//CCollisionManager::Instance()->Add(this); //追加
}
