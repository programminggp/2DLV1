#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
//06
#include "CCollider.h"

#include "CXAudio2.h"

class CPlayer : public CCharacter {
public:
	CXAudio2 mAudio;
	CXAudio2 mAudio2;
	//12
	float mVelovcityJump;
	
	//06
	//コライダの追加
	CCollider mColBody;
	//コンストラクタで初期設定
	CPlayer();

	void Update();

	void Collision(CCollider *mycol, CCollider *youcol);

};

#endif
