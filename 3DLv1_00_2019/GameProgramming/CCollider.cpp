#include "CCollider.h"
//
#include "CCollisionManager.h"

//コンストラクタ
//CCollider(親, 位置, 回転, 拡縮, 半径)
CCollider::CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius) {
	mpParent = parent;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	mRadius = radius;
	CTransform::Update();
	//
	CollisionManager.Add(this);
}

CCollider::~CCollider() {
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
