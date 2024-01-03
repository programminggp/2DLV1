#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#include "CCollisionManager2.h"

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
	//コリジョンマネージャｙに追加
//	CCollisionManager::Instance()->Add(this);
	ChangePriority();
}

void CCollider::ChangePriority()
{
	CCollisionManager2::Instance()->Remove(this);
	//自分の座標x親の変更行列をかけてワールド座標を求める
	mCenter = mPosition * *mpMatrix;
	CCollisionManager2::Instance()->Add(this);
}

void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this); //　一旦解散
	CCollisionManager::Instance()->Add(this); //追加
}

//CollisionTriangleSphere(三角コライダ、球コライダ、調整値)
//return:true(衝突している)false(衝突していない)
// 調整値:衝突いない位置まで戻す値
bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a)
{
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//線コライダをワールド座標で作成
	sv = s-> mPosition** s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(nullptr, nullptr, sv, ev);
	//三角コライダと線コライダの衝突処理
	return CollisionTriangleLine(t, &line, a);
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a){
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
	//線分が面と　交差しているか内積で確認する
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//プラスは交差していない
	if (dots * dote >= 0.0f) {
		//衝突してない(調整不要)
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//線分は面と交差している
	
	//面と線分の交点を求める
	// 交点の計算
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dots)));

	//交点が三角形内なら衝突している
	// 頂点1頂点２ベクトルと頂点交点ベクトルとの外積を求め、
	// 法線との内積がマイナスなら、三角形の外
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//衝突していない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点２頂点３ベクトルト頂点２交点ベクトルとの外積を求め、
	// 法羽扇との内積がマイナスなら、三角形の外
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//衝突していない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	// 頂点３頂点１ベクトル頂点３交点ベクトルとの外積を求め、
	// 法線との内積がマイナスなら、三角形の外
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//衝突していない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//調整値計算(衝突しない位置まで戻す)
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

bool CCollider::CollisionTriangleBotan(CCollider* t, CCollider* b, CVector* a)
{
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//線コライダをワールド座標で作成
	sv = b->mPosition * *b->mpMatrix + normal * b->mRadius;
	ev = b->mPosition * *b->mpMatrix - normal * b->mRadius;
	CColliderLine botan(nullptr, nullptr, sv, ev);
	//三角コライダと線コライダの衝突処理
	return CollisionTriangleLine(t, &botan, a);
}

CCollider::EType CCollider::Type()
{
	return mType;
}

CCollider::CCollider()
	: mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(ESPHERE)
	, mRadius(0)
{
	for (int i = 0; i < COLLIDERTASK_SIZE; i++)
	{
		mpColliderTask[i] = nullptr;
	}
	//コリジョンマネージャに追加
//	CCollisionManager::Instance()->Add(this);
	CCollisionManager2::Instance()->Add(this);
}

//衝突判定
	//Collision(コライダ１、コライダ２)
	//return:ture(衝突している)false(衝突していない)
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//各コライダの中心座標を求める
	//原点×コライダの変換行列×親の変換行列
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//中心から中心へのベクトルを求める
	mpos = mpos - opos;
	//中心の距離が半径の合計より小さいと衝突
	if (m ->mRadius + o->mRadius > mpos.Length()) {
		//衝突している
		return true;
	}
	//衝突していない
	return false;
}

CCollider::~CCollider() {
	//コリジョンから削除
//	CCollisionManager::Get()->Remove(this);
	CCollisionManager2::Instance()->Delete(this);
}

CCharacter3* CCollider::Parent()
{
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	//コライダの中心座標を計算
	//自分の座標ｘ親の変換行列を掛ける
	CVector pos = mPosition * *mpMatrix;
	//中心座標へ移動
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE赤色設定
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球の描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}