#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollision.h"
#include "CParticle.h"
#include "CHpBar.h"
#include "CSound.h"
#include <vector>
/*
CXPlayerクラス
プレイヤークラス
*/
class CXPlayer : public CXCharacter {
public:
	//プレイヤーポインタ
	static CXPlayer *mpPlayer;
	//コライダリスト
	std::vector<CCollider*> mColliders;

	CHPBar mHpBar;//HPゲージ
	//パーティクルエミッタの宣言
	CEmitter mEmitter;

	CXPlayer()
		: mEmitter("tex_glow.tga", 10)
		, mHpBar(CVector3(), CVector2(30, 2), 100, 100)
	{
		mTag = EPLAYER;	//タグにプレイヤーを設定
	}
	/*
	コンストラクタ
	m:使用するモデルのポインタ
	pos:配置する座標
	*/
	CXPlayer(CModelX *m, CVector3 pos)
		: CXPlayer() 
	{
		Init(m); //初期化処理
		mPosition = pos; //位置設定
		//Taskマネージャに追加
		CTaskManager::Get()->Add(this);
	}
	~CXPlayer() {
		//コライダの削除
		for (int i = 0; i < mColliders.size(); i++) {
			CCollisionManager::Get()->Remove(mColliders[i]);
		}
		mColliders.clear();
	}
	//初期化処理
	void Init(CModelX*);
	//更新処理
	void Update();
	//衝突処理
	bool Collision(CCollider *m, CCollider *y);
	//描画処理
	void Render();
};

#endif
