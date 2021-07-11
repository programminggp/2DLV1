#include "CTransform.h"

//行列更新処理
void CTransform::Update() {
	//拡大縮小行列の設定
	mMatrixScale.Scale(mScale.X(), mScale.Y(), mScale.Z());
	//回転行列の設定
	mMatrixRotate =
		CMatrix().RotateZ(mRotation.Z()) *
		CMatrix().RotateX(mRotation.X()) *
		CMatrix().RotateY(mRotation.Y());
	//平行移動行列の設定
	mMatrixTranslate.Translate(mPosition.X(), mPosition.Y(), mPosition.Z());
	//合成行列の設定
	mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;
}

