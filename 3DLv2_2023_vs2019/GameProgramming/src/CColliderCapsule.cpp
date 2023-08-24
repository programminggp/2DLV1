#include "CColliderCapsule.h"

CColliderCapsule::CColliderCapsule(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius)
{
	Set(parent, matrix, v0, v1, radius);
}

void CColliderCapsule::Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius)
{
	CColliderLine::Set(parent, matrix, v0, v1);
	mRadius = radius;
	mType = ECAPSULE;
	mV[2] = v1 - v0;
	mSp = v0;
	mEp = v1;
}

void CColliderCapsule::Render()
{
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//ライトオフ
	glDisable(GL_LIGHTING);
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 0.4f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//行列退避
	glPushMatrix();

//	CVector v0 = mV[0] * *mpMatrix;
//	CVector v1 = mV[1] * *mpMatrix;
	CVector v0 = mSp * *mpMatrix;
	CVector v1 = mEp * *mpMatrix;

	//行列退避
	glPushMatrix();
	CVector center;
	center = v0;// -(v1 - v0).Normalize() * mRadius;
	glTranslatef(center.X(), center.Y(), center.Z());
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();

	//行列退避
	glPushMatrix();
	center = v1;// +(v1 - v0).Normalize() * mRadius;
	glTranslatef(center.X(), center.Y(), center.Z());
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();

	//円柱描画
	CVector line = (v1 - v0);
	center = v0 + line * 0.5f;
	CVector lineXZ = line;
	lineXZ.Y(0.0f);
	if (lineXZ.Length() > 0.0)
	{
		lineXZ = lineXZ.Normalize();
	}
	line = line.Normalize();
	float lineLength = (v1 - v0).Length();// -mRadius * 2;
	glTranslatef(center.X(), center.Y(), center.Z());

	//rotate Y-axis
	CMatrix rot;
	if (lineXZ.Length() > 0.001)
	{
		rot.M()[0] = rot.M()[4 * 2 + 2] = lineXZ.Z();
		rot.M()[2] = -lineXZ.X();
		rot.M()[4 * 2] = lineXZ.X();
	}
	glMultMatrixf(rot.M());

	//rotate X-axis
	rot.Identity();
	float cos = sqrtf(line.X() * line.X() + line.Z() * line.Z());
	rot.M()[4 + 1] = rot.M()[8 + 2] = cos;
	rot.M()[4 + 2] = -line.Y();
	rot.M()[8 + 1] = line.Y();
	glMultMatrixf(rot.M());

	glTranslatef(0.0f, 0.0f, -lineLength / 2.0f);
	GLUquadric* mesh;
	mesh = gluNewQuadric();
	gluCylinder(mesh, mRadius, mRadius, lineLength, 16, 16);

	//ライトオン
	glEnable(GL_LIGHTING);
	//アルファブレンド無効
	glDisable(GL_ALPHA);
	//行列復帰
	glPopMatrix();
}
