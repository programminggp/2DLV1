#include "CBillBoard.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>

CBillBoard::CBillBoard()
: mpMaterial(0)
{
}

CBillBoard::CBillBoard(CVector pos, float w, float h)
: mpMaterial(0)
{
	Set(pos, w, h);
}

void CBillBoard::Set(CVector pos, float w, float h)
{
	//位置
	mPosition = pos;
	//大きさの設定
	mScale.mX = w;
	mScale.mY = h;
	//三角形の頂点座標設定
	mT[0].SetVertex(CVector(1.0f, 1.0f, 0.0f), CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, -1.0f, 0.0f));
	mT[1].SetVertex(CVector(-1.0f, 1.0f, 0.0f), CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, 1.0f, 0.0f));
	//法線をZ軸方向
	mT[0].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	//色を白色を設定
	if (mpMaterial)
	{
		mpMaterial->mDiffuse[0] = mpMaterial->mDiffuse[1] = mpMaterial->mDiffuse[2] = mpMaterial->mDiffuse[3] = 1.0f;
	}
}

void CBillBoard::Update() {
	//カメラへの方向ベクトルの取得
	CVector dir = Camera.mEye - mPosition;
	//Y軸の回転値を求める
	mRotation.mY = atan2f(dir.mX, dir.mZ) * 180.0f / M_PI;
	//X軸の回転値を求める
	mRotation.mX = asinf(-dir.mY / dir.Length()) * 180.0f / M_PI;
	//行列の更新
	CCharacter::Update();
}

void CBillBoard::Render() {
	//行列の保存
	glPushMatrix();
	//拡縮、回転、移動させる
	glMultMatrixf(mMatrix.mM[0]);
	//ライトオフ
	glDisable(GL_LIGHTING);
	//描画色の設定
	if (mpMaterial)
		glColor4fv(mpMaterial->mDiffuse);
	else
		glColor4fv(mMaterial.mDiffuse);
	//マテリアル適用
	if (mpMaterial)
		mpMaterial->Enabled();
	else
		mMaterial.Enabled();
	//三角形の描画
	mT[0].Render();
	mT[1].Render();
	//マテリアル解除
	if (mpMaterial)
		mpMaterial->Disabled();
	else
		mMaterial.Disabled();
	//ライトオン
	glEnable(GL_LIGHTING);
	//行列を戻す
	glPopMatrix();
}

