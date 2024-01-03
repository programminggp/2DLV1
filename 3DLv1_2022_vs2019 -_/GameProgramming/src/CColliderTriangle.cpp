#include "CColliderTriangle.h"
#include "CColliderManager.h"

void CColliderTriangle::ChangePriority()
{
	CColliderManager::Instance()->Remove(this);
	//三角形の中心を求める
	mCenter = (mV[0] * *mpMatrix + mV[1] * *mpMatrix
		+ mV[2] * *mpMatrix) * (1.0f / 3.0f);
	CColliderManager::Instance()->Add(this);
}

CColliderTriangle::CColliderTriangle(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1, const CVector& v2)
{
	Set(parent, matrix, v0, v1, v2);
}

void CColliderTriangle::Set(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1, const CVector& v2) {
	mType = ETRIANGLE;//三角コライダ
	mpParent = parent;//親設定
	if (matrix)
		mpMatrix = matrix;//親行列あれば設定
	//三角形頂点設定
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
	ChangePriority();
}

void CColliderTriangle::Render()
{
	//行列退避
	glPushMatrix();
	//行列適用
	glMultMatrixf(mpMatrix->M());
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//ライトオフ
	glDisable(GL_LIGHTING);

	//DIFFUSE赤色設定
	float c[] = { 1.0f,0.0f,0.0f,0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//三角形描画
	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
	glEnd();

	//ライトオン
	glEnable(GL_LIGHTING);
	//アルファブレンド無効
	glDisable(GL_ALPHA);
	//行列復帰
	glPopMatrix();
}

//void CColliderTriangle::Update()
//{
//	CCollider::mV[0] = mV[0] * *mpMatrix;
//	CCollider::mV[1] = mV[1] * *mpMatrix;
//	CCollider::mV[2] = mV[2] * *mpMatrix;
//	CCollider::mV[3] = (mV[1] - mV[0]).Cross(mV[2] - mV[0]).Normalize();
//	ChangePriority();
//}