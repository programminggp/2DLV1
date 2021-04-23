#ifndef CSCENERACEB_H
#define CSCENERACEB_H

#include "CSceneRace.h"

class CSceneRaceB : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

//	CModel mSum;
};

#endif
