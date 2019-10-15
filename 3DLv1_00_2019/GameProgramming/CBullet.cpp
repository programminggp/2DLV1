#include "CBullet.h"

#define VELOCITY 1.0f //弾速 2.0f

//幅と奥行きの設定
//Set(幅, 奥行)
void CBullet::Set(float w, float d) {
	mScale = CVector(1.0f, 1.0f, 1.0f);
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update() {
	CCharacter::Update();
	mPosition = CVector(0.0f, 0.0f, VELOCITY) * mMatrix;
}

//描画
void CBullet::Render() {
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);

	mT.Render(mMatrix);
}
