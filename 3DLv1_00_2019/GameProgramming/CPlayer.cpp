//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"

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
	//CCharacterの更新
	CCharacter::Update();
}
