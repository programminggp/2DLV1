#include "CEnemy2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160	//テクスチャマッピング

int CEnemy2::mNum = 0; //敵の数

//コンストラクタ
CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
}

//デストラクタ
CEnemy2::~CEnemy2()
{

}

//敵の数を設定
void CEnemy2::Num(int num)
{
	mNum = num;
}

//敵の数を取得
int CEnemy2::Num()
{
	return mNum;
}

//衝突判定2
void CEnemy2::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

//衝突判定4
void CEnemy2::Collision(CCharacter* m, CCharacter* o)
{

}

//更新処理
void CEnemy2::Update()
{
	mState = EState::EMOVE;
	CCharacter::Update();
}
