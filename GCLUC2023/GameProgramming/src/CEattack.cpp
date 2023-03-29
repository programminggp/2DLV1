#include "CEattack.h"

#define MU 0, 200, 0, 0　//仮
#define WOLFNTL 1206,1796,433,133 //仮

//コンストラクタ
CEattack::CEattack(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, WOLFNTL);
	mState = EState::EATTACK;
}

//デストラクタ
CEattack::~CEattack()
{
}

//更新処理
void CEattack::Update()
{
	CCharacter::Update();
}