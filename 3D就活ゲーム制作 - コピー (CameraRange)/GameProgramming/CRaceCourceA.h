#ifndef CRACECOURCEA_H
#define CRACECOURCEA_H
#include "CSceneRace.h"
#include "CModel.h"


class CRaceCourceA : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif