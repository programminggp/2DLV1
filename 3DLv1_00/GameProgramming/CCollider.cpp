#include "CCollider.h"
#include "CCharacter.h"
#include "glut.h"
#include "CSceneGame.h"

CCollider::CCollider()
: mpParent(0)
, mRadius(0)
{
	CollisionManager.Add(this);
}

CCollider::~CCollider() {
	CollisionManager.Remove(this);
}

void CCollider::Render() {
	glPushMatrix();
	glMultMatrixf(CMatrix().Translate(mpParent->mPosition.mX, mpParent->mPosition.mY, mpParent->mPosition.mZ).mM[0]);

	float c[] = {0.0f, 0.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);

	glutWireSphere(mRadius, 16, 16);

	glPopMatrix();
}

bool CCollider::Collision(CCollider *c1, CCollider *c2) {
	CVector pos1 = c1->mV[0] * c1->mpParent->mMatrix;
	CVector pos2 = c2->mV[0] * c2->mpParent->mMatrix;
	pos1 = pos1 + pos2 * -1.0f;
	if (pos1.Length() > c1->mRadius + c2->mRadius) {
		return false;
	}
	return true;
}