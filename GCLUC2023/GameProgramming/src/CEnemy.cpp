#include "CEnemy.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160	//�e�N�X�`���}�b�s���O

int CEnemy::mNum = 0; //�G�̐�

//�R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{

}

//�G�̐���ݒ�
void CEnemy::Num(int num)
{
	mNum = num;
}

//�G�̐����擾
int CEnemy::Num()
{
	return mNum;
}

//�Փ˔���2
void CEnemy::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

//�Փ˔���4
void CEnemy::Collision(CCharacter* m, CCharacter* o)
{

}

//�X�V����
void CEnemy::Update()
{
	mState = EState::EMOVE;
	CCharacter::Update();
}
