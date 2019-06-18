#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "CRectangle.h"

class CCharacter : public CRectangle {
public:
	//タグ
	enum ETag {
		ENONE,
		EPLAYER,
		EBACKGROUND,
		EBOSS,
		ESHOOTPLAYER,
		ESHOOTBOSS,
		ESHOOTENEMY,
		EENEMY,
		EBLOCK,
	};
	ETag mTag;

	//ステータス
	enum EState {
		EDISABLED,	//無効
		EENABLED,	//有効
		ECOLLISION,	//衝突済
	};
	EState mState;
	//コンストラクタ
	CCharacter();
	virtual ~CCharacter();
	//更新処理
	virtual void Update() {};
	//描画処理
	virtual void Render() {};
	//衝突処理
	virtual void Collision(CCharacter* mc, CCharacter* yc) {};

};

#endif
