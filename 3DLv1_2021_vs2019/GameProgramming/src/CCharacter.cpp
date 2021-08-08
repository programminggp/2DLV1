#include "CCharacter.h"
#include "CTaskManager.h"

void CCharacter::Model(CModel *m)
{
	mpModel = m;
}

CCharacter::ETag CCharacter::Tag()
{
	return mTag;
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

CCharacter::CCharacter()
	: mpModel(nullptr)
	, mTag(EZERO)
{
	//�^�X�N���X�g�ɒǉ�
	CTaskManager::Get()->Add(this);
}

