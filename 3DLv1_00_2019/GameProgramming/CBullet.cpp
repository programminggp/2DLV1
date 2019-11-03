#include "CBullet.h"
//
#include "CTaskManager.h"

//幅と奥行きの設定
//Set(幅, 奥行)
void CBullet::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update() {
	//生存時間の判定
	if (mLife-- > 0) {
		CCharacter::Update();
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	else {
		//無効にする
		mEnabled = false;
	}
}

//描画
void CBullet::Render() {
	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画
	mT.Render(mMatrix);
}
//22
CBullet::CBullet()
: mLife(50)
, mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{
}

void CBullet::Collision(CCollider *m, CCollider *y) {
	if (CCollider::Collision(m, y)) {
		mEnabled = false;
//		printf("Bullet Hit!\n");
	}
}