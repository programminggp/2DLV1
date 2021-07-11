#include "CColliderLine.h"
#include "CCollisionManager.h"

CColliderLine::CColliderLine(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1)
{
	Set(parent, matrix, v0, v1);
}

void CColliderLine::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1) {
	mType = ELINE;//線分コライダ
	mpParent = parent;//親設定
	if (matrix)
		mpMatrix = matrix;//親行列あれば設定
	//三角形頂点設定
	mV[0] = v0;
	mV[1] = v1;
}

void CColliderLine::Render()
{
	//行列退避
	glPushMatrix();
	//行列適用
	glMultMatrixf(mpMatrix->mM[0]);

	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//ライトオフ
	glDisable(GL_LIGHTING);

	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//三角形描画
	glBegin(GL_LINES);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glEnd();

	//ライトオン
	glEnable(GL_LIGHTING);
	//アルファブレンド無効
	glDisable(GL_ALPHA);
	//行列復帰
	glPopMatrix();
}
//優先度の変更
void CColliderLine::ChangePriority()
{
	//mV[0]とmV[1]の中心を求める
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix) * (0.5f);
	//ベクトルの長さが優先度
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //一旦削除
	CCollisionManager::Get()->Add(this); //追加
}
