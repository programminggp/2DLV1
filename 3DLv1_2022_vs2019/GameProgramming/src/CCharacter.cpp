#include"CCharacter.h"
//�^�X�N�}�l�[�W���N���X�̃C���N���[�h
#include"CTaskManager.h"

CCharacter::CCharacter() 
	:mTag(EZERO)
{
	//�^�X�N���X�g�ɒǉ�
	CTaskManager::Get()->Add(this);
}

CCharacter::ETag CCharacter::Tag()
{
	return mTag;
}

void CCharacter::Model(CModel* m)
{
	mpModel = m;
}

//�`�揈��
void CCharacter::Render()
{
	mpModel->Render(mMatrix);
}

CCharacter::~CCharacter() {
	//�^�X�N���X�g����폜
	CTaskManager::Get()->Remove(this);
}