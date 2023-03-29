#include "CBossAttackBox.h"

#define MU 0, 200, 0, 0　//仮
#define WOLFNTL 0,0,0,0 //仮

//コンストラクタ
CBossAttackBox::CBossAttackBox(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, WOLFNTL);
	mTag = ETag::EATTACK2;
}

//デストラクタ
CBossAttackBox::~CBossAttackBox()
{
}

//更新処理
void CBossAttackBox::Update()
{
	CCharacter::Update();
}