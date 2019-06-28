#ifndef CCHARACTER_H
#define CCHARACTER_H

class CCharacter {
public:
	float mX, mY, mW, mH;
	//タグ
	enum ETag {
		ENONE,
		EPLAYER,
		EBACKGROUND,
		EBOSS,
		EPLAYERSHOT,
		ESHOOTBOSS,
		EENEMYSHOT,
		EENEMY
	};
	ETag mTag;

	//ステータス
	enum EState {
		EDELETE,	//無
		EDISABLED,	//無効
		EENABLED,	//有効
	};
	EState mState;
	//コンストラクタ
	CCharacter();
	virtual ~CCharacter();
	void Set(float x, float y, float w, float h);
	//更新処理
	virtual void Update() {};
	//描画処理
	virtual void Render();
	//衝突処理
	virtual void Collision(CCharacter* mc, CCharacter* yc) {};

};

#endif
