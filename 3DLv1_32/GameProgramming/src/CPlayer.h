#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタークラスのインクルード
#include"CCharacter.h"
//弾クラスのインクルード
#include"CBullet.h"
//線分コライダクラスのインクルード
#include"CColliderLine.h"


/*
プレイヤークラス
キャラクタークラスを継承
*/

class CPlayer : public CCharacter {
public:
	//CBulletクラスのインスタンス変数
	/*CBullet bullet;*/
	CPlayer();
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider* m, CCollider* o);
private:

	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2; //線分コライダ2
	CColliderLine mLine3; //線分コライダ3
};
#endif 

