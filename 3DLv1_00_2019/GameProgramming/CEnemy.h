#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy : public CCharacter {
public:
	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CEnemy(CModel *model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();
};

#endif
