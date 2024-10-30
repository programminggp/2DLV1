#include "CColliderCapsule.h"

CColliderCapsule::CColliderCapsule(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius)
{
	Set(parent, matrix, v0, v1, radius);
}

void CColliderCapsule::Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius)
{
	mType = CCollider::EType::ECAPSULE;
	mpParent = parent;
	mpMatrix = matrix;
	mSp = v0;
	mEp = v1;
	mRadius = radius;
}

void CColliderCapsule::Update()
{
	//ワールド座標に更新し、線の向きを求める
	mV[0] = mSp * *mpMatrix;
	mV[1] = mEp * *mpMatrix;
	mV[2] = mV[1] - mV[0];
	ChangePriority();
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

	//行列退避
	glPushMatrix();
	CVector center;
	center = mV[0];// -(v1 - v0).Normalize() * mRadius;
	glTranslatef(center.X(), center.Y(), center.Z());
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
	//行列退避
	glPushMatrix();
	center = mV[1];// +(v1 - v0).Normalize() * mRadius;
	glTranslatef(center.X(), center.Y(), center.Z());
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();

	//円柱描画
	CVector line = (mV[1] - mV[0]);
	center = mV[0] + line * 0.5f;
	CVector lineXZ = line;
	lineXZ.Y(0.0f);
	if (lineXZ.Length() > 0.0)
	{
		lineXZ = lineXZ.Normalize();
	}
	line = line.Normalize();
	float lineLength = (mV[1] - mV[0]).Length();// -mRadius * 2;
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

void CColliderCapsule::ChangePriority()
{
	//mV[0]とmV[1]の中心を求める
	CVector pos = (mV[0] + mV[1]) * (0.5f);
	//ベクトルの長さが優先度
	CCollider::ChangePriority(pos.Length());
}
