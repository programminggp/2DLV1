#ifndef COBJ_H
#define COBJ_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

#define GROUNDS_LIMIT 128//生成できるオブジェ数の限界値

class CObj :public CCharacter{
public:
	//コライダの追加
	CCollider *mpCollider;
	//コンストラクタで初期設定
	CObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider = true, bool hasshadow = true);
	~CObj();

	void Update();

	static int mObjectNum;//オブジェの番号(生成したオブジェの総数にもなる)
	static int mObject_Limit;//生成できるオブジェ数の限界値
	static CObj *mpGrounds[GROUNDS_LIMIT];
};

#endif