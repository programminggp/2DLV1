#include "CSlimeAttackBox.h"

#define MU 0, 200, 0, 0　//仮
#define WOLFNTL 0,0,0,0 //仮

//コンストラクタ
CSlimeAttackBox::CSlimeAttackBox(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, WOLFNTL);
	mTag = ETag::EATTACK;
}

//デストラクタ
CSlimeAttackBox::~CSlimeAttackBox()
{
}

//更新処理
void CSlimeAttackBox::Update()
{
	CCharacter::Update();
}