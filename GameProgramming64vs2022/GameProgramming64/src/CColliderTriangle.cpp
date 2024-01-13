#include "CColliderTriangle.h"
#include "CCollisionManager.h"
#include "CColliderManager.h"

CColliderTriangle::CColliderTriangle(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, const CVector &v2)
{
	Set(parent, matrix, v0, v1, v2);
}

void CColliderTriangle::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, const CVector &v2) {
	mType = ETRIANGLE;//三角コライダ
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
	glDisable(GL_DEPTH_TEST);

	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//三角形描画
	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
	glEnd();

	glEnable(GL_DEPTH_TEST);
	//ライトオン
	glEnable(GL_LIGHTING);
	//アルファブレンド無効
	glDisable(GL_ALPHA);
	//行列復帰
	glPopMatrix();
}
//優先度の変更
void CColliderTriangle::ChangePriority()
{
	CColliderManager::Instance()->Remove(this);
	//mV[0]とmV[1]とmV[2]の中心を求める
	mCenter = (CCollider::mV[0] + CCollider::mV[1] + CCollider::mV[2]) * (1.0f/3.0f);
	CColliderManager::Instance()->Add(this);
}

void CColliderTriangle::Mesh(CCharacter* parent, CMatrix* matrix, CModel* model)
{
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{	//三角コライダの設定
		CColliderTriangle *p = new CColliderTriangle(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2()
		);
		p->ChangePriority();
	}
}

void CColliderTriangle::Update()
{
	CCollider::mV[0] = mV[0] * *mpMatrix;
	CCollider::mV[1] = mV[1] * *mpMatrix;
	CCollider::mV[2] = mV[2] * *mpMatrix;
	CCollider::mV[3] = (mV[1] - mV[0]).Cross(mV[2] - mV[0]).Normalize();
	ChangePriority();
}
