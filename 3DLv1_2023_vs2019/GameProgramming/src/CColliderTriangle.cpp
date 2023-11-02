#include "CColliderTriangle.h"

CColliderTriangle::CColliderTriangle(
	CCharacter3* parent, 
	CMatrix* matrix, 
	const CVector& v0, 
	const CVector& v1, 
	const CVector& v2)
{
	Set(parent, matrix, v0, v1, v2);
}

void CColliderTriangle::Set(
	CCharacter3* parent, 
	CMatrix* matrix, 
	const CVector& v0, 
	const CVector& v1, 
	const CVector& v2)
{
	mType = EType::ETRIANGLE;//三角コライダ
	mpParent = parent;//親設定
	if (matrix)
		mpMatrix = matrix;//親行列あれば設定
	//三角形頂点設定
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
	Update();
}

void CColliderTriangle::Render()
{
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//ライトオフ
	glDisable(GL_LIGHTING);

	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//三角形描画
	glBegin(GL_TRIANGLES);
	glVertex3f(CCollider::mV[0].X(), CCollider::mV[0].Y(), CCollider::mV[0].Z());
	glVertex3f(CCollider::mV[1].X(), CCollider::mV[1].Y(), CCollider::mV[1].Z());
	glVertex3f(CCollider::mV[2].X(), CCollider::mV[2].Y(), CCollider::mV[2].Z());
	glEnd();

	//ライトオン
	glEnable(GL_LIGHTING);
	//アルファブレンド無効
	glDisable(GL_ALPHA);
}

void CColliderTriangle::Update()
{
	CCollider::mV[0] = mV[0] * *mpMatrix;
	CCollider::mV[1] = mV[1] * *mpMatrix;
	CCollider::mV[2] = mV[2] * *mpMatrix;
	CCollider::mV[3] = (CCollider::mV[1] - CCollider::mV[0]).Cross(CCollider::mV[2] - CCollider::mV[0]).Normalize();
	ChangePriority();
}

void CColliderTriangle::ChangePriority()
{
	//mV[0]とmV[1]とmV[2]の中心を求める
	CVector pos = (CCollider::mV[0] + CCollider::mV[1] + CCollider::mV[2]) * (1.0f / 3.0f);
	//ベクトルの長さが優先度
	CCollider::ChangePriority(pos.Length());
}