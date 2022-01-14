#include"CCharacter.h"
//�^�X�N�}�l�[�W���N���X�̃C���N���[�h
#include"CTaskManager.h"

CCharacter::CCharacter() {
	//�^�X�N���X�g�ɒǉ�
	CTaskManager::Get()->Add(this);
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