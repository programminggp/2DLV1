#include "CCollider.h"
#include "CColliderLine.h"
#include "CApplication.h"

void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CApplication::CollisionManager()->Remove(this); //一旦削除
	CApplication::CollisionManager()->Add(this); //追加
}

bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a)
{
	/*CVector v[3], sv, ev;*/
	////各コライダの頂点をワールド座標へ変換
	//v[0] = t->mV[0];
	//v[1] = t->mV[1];
	//v[2] = t->mV[2];
	////面の法線を、外積を正規化して求める
	//CVector normal = t->mV[3];
	//線コライダをワールド座標で作成
	CVector sv = s->mV[0] + t->mV[3] * s->mRadius;
	CVector ev = s->mV[0] - t->mV[3] * s->mRadius;
	CColliderLine line(nullptr, nullptr, sv, ev);
	//三角コライダと線コライダの衝突処理
	return CollisionTriangleLine(t, &line, a);
}

CCollider::CCollider()
	: mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(EType::ESPHERE)
	, mRadius(0)
{
	//コリジョンマネージャに追加
	CApplication::CollisionManager()->Add(this);
}

//衝突判定
//Collision(コライダ1, コライダ2)
//retrun:true（衝突している）false(衝突していない)
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//各コライダの中心座標を求める
	//原点×コライダの変換行列×親の変換行列
//	CVector mpos = m->mPosition * *m->mpMatrix;
//	CVector opos = o->mPosition * *o->mpMatrix;
	//中心から中心へのベクトルを求める
	CVector mpos = m->mV[0] - o->mV[0];
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
	CApplication::CollisionManager()->Remove(this);
}

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
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

CCharacter3* CCollider::Parent()
{
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix(); //行列退避
	//中心座標へ移動
	glMultMatrixf(CMatrix().Translate(mV[0].X(), mV[0].Y(), mV[0].Z()).M());
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix(); //行列復帰
}

void CCollider::Update()
{
	mV[0] = mPosition * *mpMatrix;
	ChangePriority();
}

CCollider::EType CCollider::Type()
{
	return mType;
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0];
	v[1] = t->mV[1];
	v[2] = t->mV[2];
	sv = l->mV[0];
	ev = l->mV[1];
	//面の法線を、外積を正規化して求める
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

//優先度の変更
void CCollider::ChangePriority()
{
	//ベクトルの長さが優先度
	ChangePriority(mV[0].Length());
}
