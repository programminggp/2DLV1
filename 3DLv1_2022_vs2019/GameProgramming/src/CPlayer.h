#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタークラスのインクルード
#include"CCharacter.h"
//弾クラスのインクルード
#include"CBullet.h"

#include "CColliderLine.h"

#include "CText.h"

/*
プレイヤークラス
キャラクタークラスを継承
*/

class CPlayer : public CCharacter {
public:
	CPlayer();
	//CBulletクラスのインスタンス変数
	/*CBullet bullet;*/
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider* m, CCollider* o);
	//描画処理
	void Render();

private:
	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2; //線分コライダ
	CColliderLine mLine3; //線分コライダ
	CText mText;
};
#endif 

