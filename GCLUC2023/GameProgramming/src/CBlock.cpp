#include "CBlock.h"
#include "CApplication.h"

#define TEXCOORD 0,0,0,0//22, 22, 22, 22

//コンストラクタ
CBlock::CBlock(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::EBLOCK)
{
	Set(x, y, w, h* 5);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK;
}

//衝突判定2
void CBlock::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

//衝突判定4
void CBlock::Collision(CCharacter* m, CCharacter* o)
{
	////めり込み調整変数を宣言する
	float x, y;
	switch (o->Tag())
	{
	case ETag::EPLAYER:
		if (CRectangle::Collision(o))
		{
		}
		break;
	}
}

//更新処理
void CBlock::Update()
{
	CCharacter::Update();
}