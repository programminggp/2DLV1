//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"

#include "CBullet.h"
extern CBullet Bullet;

//更新処理
void CPlayer::Update() {
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation.mY += 1;
	}
	//Iキー入力で前進
	if (CKey::Push('I')) {
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	//Dキー入力で回転
	if (CKey::Push('D')) {
		//Y軸の回転値を減算
		mRotation.mY -= 1;
	}
	//Sキー入力で上向き
	if (CKey::Push('S')) {
		//X軸の回転値を減算
		mRotation.mX -= 1;
	}
	//Wキー入力で上向き
	if (CKey::Push('W')) {
		//X軸の回転値を加算
		mRotation.mX += 1;
	}
	//Wキー入力で上向き
	if (CKey::Push(VK_SPACE)) {
		Bullet.Set(0.1f, 1.5f);
		Bullet.mPosition = mPosition;
 		Bullet.mRotation = mRotation;
	}
	//CCharacterの更新
	CCharacter::Update();
}
