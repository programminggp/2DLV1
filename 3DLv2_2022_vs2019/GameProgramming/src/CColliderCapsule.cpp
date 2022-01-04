#include "CColliderCapsule.h"
#include "CCollisionManager.h"

CColliderCapsule::CColliderCapsule(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius)
{
	Set(parent, matrix, v0, v1, radius);
}

void CColliderCapsule::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius) {
	mType = ECAPSUL;//カプセルコライダ
	mpParent = parent;//親設定
	if (matrix)
		mpMatrix = matrix;//親行列あれば設定
	//三角形頂点設定
	mV[0] = v0;
	mV[1] = v1;
	mRadius = radius;
}

void CColliderCapsule::Render()
{
	//行列退避
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//行列適用
	glMultMatrixf(mpMatrix->M());

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

	GLUquadric* mesh;
	mesh = gluNewQuadric();
	gluCylinder(mesh, mRadius, mRadius, (mV[0]-mV[1]).Length()- mRadius*2, 16, 16);

	//三角形描画
	//glBegin(GL_LINES);
	//glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	//glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	//glEnd();

	//ライトオン
	glEnable(GL_LIGHTING);
	//アルファブレンド無効
	glDisable(GL_ALPHA);
	//行列復帰
	glPopMatrix();
}
//優先度の変更
void CColliderCapsule::ChangePriority()
{
	//mV[0]とmV[1]の中心を求める
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix) * (0.5f);
	//ベクトルの長さが優先度
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //一旦削除
	CCollisionManager::Get()->Add(this); //追加
}
