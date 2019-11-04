#include "CCollider.h"
//コリジョンマネージャのインクルード
#include "CCollisionManager.h"

//コンストラクタ
//CCollider(親, 位置, 回転, 拡縮, 半径)
CCollider::CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius) {
	//親設定
	mpParent = parent;
	//CTransform設定
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	CTransform::Update();//行列更新
	//半径設定
	mRadius = radius;
	//コリジョンリストに追加
	CollisionManager.Add(this);
}

CCollider::~CCollider() {
	//コリジョンリストから削除
	CollisionManager.Remove(this);
}

//描画
void CCollider::Render() {
	glPushMatrix();
	glMultMatrixf((mMatrix * mpParent->mMatrix).mM[0]);
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}

//衝突判定
//Collision(コライダ1, コライダ2)
//retrun:true（衝突している）false(衝突していない)
bool CCollider::Collision(CCollider *m, CCollider *y) {
	//各コライダの中心座標を求める
	//原点×コライダの変換行列×親の変換行列
	CVector mpos = CVector() * m->mMatrix * m->mpParent->mMatrix;
	CVector ypos = CVector() * y->mMatrix * y->mpParent->mMatrix;
	//中心から中心へのベクトルを求める
	mpos = mpos - ypos;
	//中心の距離が半径の合計より小さいと衝突
	if (m->mRadius + y->mRadius > mpos.Length()) {
		//衝突している
		return  true;
	}
	//衝突していない
	return false;
}
