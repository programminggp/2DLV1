#include "CCollider.h"

//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//CCollider(e, ˆÊ’u, ‰ñ“], Šgk, ”¼Œa)
CCollider::CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius) {
	mpParent = parent;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	mRadius = radius;
}
//•`‰æ
void CCollider::Render() {
	glPushMatrix();
	glMultMatrixf(mMatrix.mM[0]);
	//DIFFUSEÔFİ’è
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//‹…•`‰æ
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}
