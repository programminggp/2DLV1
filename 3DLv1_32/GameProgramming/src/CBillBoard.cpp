#include "CBillBoard.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>
CBillBoard::CBillBoard() {

}

CBillBoard::CBillBoard(CVector pos, float w, float h) {
	Set(pos, w, h);
}

void CBillBoard::Set(CVector pos, float w, float h) {
	//位置
	mPosition = pos;
	//大きさの設定
	mScale = CVector(w, h, 0.0f);
	//三角形の頂点座標設定
	mT[0].Vertex(CVector(1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, -1.0f, 0.0f));
	mT[1].Vertex(CVector(-1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, 1.0f, 0.0f));
	//法線をZ軸方向
	mT[0].Normal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].Normal(CVector(0.0f, 0.0f, 1.0f));
	//色を白色を設定
	mMaterial.Diffuse()[0] = 1.0f;
	mMaterial.Diffuse()[1] = 1.0f;
	mMaterial.Diffuse()[2] = 1.0f;
	mMaterial.Diffuse()[3] = 1.0f;
}

void CBillBoard::Update() {
	//カメラへの方向ベクトルの取得
	CVector dir = Camera.Eye() - mPosition;
	//Y軸の回転値を求める
	//X軸の回転値を求める
	mRotation.Set(asinf(-dir.Y() / dir.Length()) * 180.0f / M_PI, atan2f(dir.X(), dir.Z()) * 180.0f / M_PI, mRotation.Z());
	//行列の更新
	CTransform::Update();
}

void CBillBoard::Render() {
	Render(&mMaterial);
}

//Render(マテリアルのポインタ)
void CBillBoard::Render(CMaterial* mpMaterial) {
	//行列の保存
	glPushMatrix();
	//拡縮,回転,移動される
	glMultMatrixf(mMatrix.M());
	//ライトオフ
	glDisable(GL_LIGHTING);
	//描画色の設定
	glColor4fv(mpMaterial->Diffuse());
	//マテリアル適用
	mpMaterial->Enabled();
	//三角形の描画
	mT[0].Render();
	mT[1].Render();
	//マテリアルの解除
	mpMaterial->Disabled();
	//ライトオン
	glEnable(GL_LIGHTING);
	//行列を戻す
	glPopMatrix();
}

