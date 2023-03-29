#include "CEnemy2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160	//�e�N�X�`���}�b�s���O

int CEnemy2::mNum = 0; //�G�̐�

//�R���X�g���N�^
CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
}

//�f�X�g���N�^
CEnemy2::~CEnemy2()
{

}

//�G�̐���ݒ�
void CEnemy2::Num(int num)
{
	mNum = num;
}

//�G�̐����擾
int CEnemy2::Num()
{
	return mNum;
}

//�Փ˔���2
void CEnemy2::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

//�Փ˔���4
void CEnemy2::Collision(CCharacter* m, CCharacter* o)
{

}

//�X�V����
void CEnemy2::Update()
{
	mState = EState::EMOVE;
	CCharacter::Update();
}
