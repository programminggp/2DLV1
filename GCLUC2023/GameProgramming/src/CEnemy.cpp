#include "CEnemy.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160	//テクスチャマッピング

int CEnemy::mNum = 0; //敵の数

//コンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
}

//デストラクタ
CEnemy::~CEnemy()
{

}

//敵の数を設定
void CEnemy::Num(int num)
{
	mNum = num;
}

//敵の数を取得
int CEnemy::Num()
{
	return mNum;
}

//衝突判定2
void CEnemy::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

//衝突判定4
void CEnemy::Collision(CCharacter* m, CCharacter* o)
{

}

//更新処理
void CEnemy::Update()
{
	mState = EState::EMOVE;
	CCharacter::Update();
}
