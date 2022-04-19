#ifndef CTANK_H
#define CTANK_H
//キャラクタクラスのインクルード
#include "CCharacter.h"


/*
砲塔クラス
*/
class CTank2 : public CCharacter
{
public:
	CTank2(CCharacter* parent);
	void Update();
private:
	static CModel mModel;
	CCharacter* mpParent;
};

/*
戦車クラス
キャラクタクラスを継承
*/
class CTank : public CCharacter {
public:
	//コンストラクタ
	CTank();
	//Tank(位置, 回転, 拡縮)
	CTank(const CVector& position, const CVector& rotation,
		const CVector& scale);
	//更新処理
	void Update();
private:
	//モデルデータ
	static CModel mModel;
};

#endif
