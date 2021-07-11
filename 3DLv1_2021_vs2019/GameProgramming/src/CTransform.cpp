#include "CTransform.h"

//行列更新処理
void CTransform::Update() {
	//拡大縮小行列の設定
	mMatrixScale.Scale(mScale.mX, mScale.mY, mScale.mZ);
	//回転行列の設定
	mMatrixRotate =
		CMatrix().RotateZ(mRotation.mZ) *
		CMatrix().RotateX(mRotation.mX) *
		CMatrix().RotateY(mRotation.mY);
	//平行移動行列の設定
	mMatrixTranslate.Translate(mPosition.mX, mPosition.mY, mPosition.mZ);
	//合成行列の設定
	mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;
}

