#ifndef CCHARACTER_H
#define CCHARACTER_H

class CCharacter {
public:
	float mX;//中心のX座標
	float mY;//中心のY座標
	float mW;//幅の半分
	float mH;//高さの半分
	//タグ
	enum ETag {
		ENONE,
		EPLAYER,
		EBACKGROUND,
		EBOSS,
		EPLAYERSHOT,
		ESHOOTBOSS,
		EENEMYSHOT,
		EENEMY,
		EBLOCK,
		EBOMB,
	};
	ETag mTag;

	//ステータス
	enum EState {
		EDELETE,
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
	void Set(int posx, int posy, int width, int height);

};

#endif
