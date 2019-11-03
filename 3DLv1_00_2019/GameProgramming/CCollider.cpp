#include "CCollider.h"
//
#include "CCollisionManager.h"

//RXgN^
//CCollider(e, Êu, ñ], gk, ¼a)
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

//`æ
void CCollider::Render() {
	glPushMatrix();
	glMultMatrixf((mMatrix * mpParent->mMatrix).mM[0]);
	//DIFFUSEÔFÝè
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//`æ
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}
