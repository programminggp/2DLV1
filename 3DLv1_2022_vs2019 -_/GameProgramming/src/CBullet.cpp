#include "CBullet.h"
#include"CApplication.h"

void CBullet::Collision()
{
	mCollider.ChangePriority();
	CCollisionManager::Instance()->Collision(&mCollider, 30);
}

//衝突処理
//Collision(コライダ１、 コライダ２)
void CBullet::Collision(CCollider* m, CCollider* o)
{
	//コライダのmとoが衝突しているか判定
	if (CCollider::Collision(m, o)) {
		//衝突している時は無効にする
		mEnabled = false;
	}
}

CBullet::CBullet()
	:mLife(50)
	,mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.1f)
{}

//幅と奥行の設定
//Set(幅、奥行)
void CBullet::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.Vertex(CVector(-w, 0.0f, 0.0f), CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d));
	//三角形の法線設定
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update(){
	if (mLife-- > 0) {
		CTransform::Update();
		//位置更新
		mPosition = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	}
	else {
		//無効にする
		mEnabled = false;
	}
}

void CBullet::Render() {
	/*mCollider.Render();*/
	//DIFFUSE黄色設定
	float c[] = { 1.0f,1.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画
	mT.Render(mMatrix);
}