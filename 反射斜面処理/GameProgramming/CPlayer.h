#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
//06
#include "CCollider.h"

class CPlayer : public CCharacter {
public:
	//12
	float mVelovcityJump;
	
	//06
	//コライダの追加
	CCollider mColBody;
	//コンストラクタで初期設定
	CPlayer();

	void Update();

	void Collision(CCollider *mycol, CCollider *youcol);

//	void Render(){}

};

#endif
