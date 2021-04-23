#ifndef CRACECOURCEA_H
#define CRACECOURCEA_H

#include "CModel.h"
#include "CSceneRace.h"

class CRaceCourceA : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif