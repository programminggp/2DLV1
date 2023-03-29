#include "CWolfAttackBox.h"

#define MU 0, 200, 0, 0　//仮
#define WOLFNTL 0,0,0,0 //仮

//コンストラクタ
CWolfAttackBox::CWolfAttackBox(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, WOLFNTL);
	mTag = ETag::EATTACK;
}

//デストラクタ
CWolfAttackBox::~CWolfAttackBox()
{
}

//更新処理
void CWolfAttackBox::Update()
{
	CCharacter::Update();
}