#ifndef CCHARACTER_H
#define CCHARACTER_H
//変換行列クラスのインクルード
#include "CTransform.h"
//モデルクラスのインクルード
#include "CModel.h"
//
#include "CTask.h"
//コライダクラスの宣言
class CCollider;

/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/
class CCharacter : public CTransform ,public CTask {
public:
	enum ETag 
	{
		EZERO,		//初期値
		EPLAYER,	//プレイヤー
		EENEMY,		//敵
		EBULLETPLAYER,	//プレイヤー弾
		EBULLETENEMY,	//敵弾
	};
	ETag mTag;
	CModel *mpModel; //モデルのポインタ
	//描画処理
	void Render();
	//デストラクタ
	~CCharacter();
	//コンストラクタ
	CCharacter();
	//衝突処理
	virtual void Collision(CCollider *m, CCollider *o) {}

};

#endif
