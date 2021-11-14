//�L�����N�^�N���X�C���N���[�h
#include "CCharacter.h"
//
#include "CTaskManager.h"

//�X�V����
void CCharacter::Update() {
	//�g��k���s��̐ݒ�
	mMatrixScale.Scale(mScale.mX, mScale.mY, mScale.mZ);
	//��]�s��̐ݒ�
	mMatrixRotate = 
		CMatrix().RotateZ(mRotation.mZ) *
		CMatrix().RotateX(mRotation.mX) *
		CMatrix().RotateY(mRotation.mY);
	//���s�ړ��s��̐ݒ�
	mMatrixTranslate.Translate(mPosition.mX, mPosition.mY, mPosition.mZ);
	//�����s��̐ݒ�
	mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;
}
//�`�揈��
void CCharacter::Render() {
	if (isRender){
		if (mpModel) {
			//���f���̕`��
			mpModel->Render(mMatrix);
		}
	}
}

CCharacter::CCharacter()
: mpModel(0)
, mTag(ENONE)
, mScale(1.0f, 1.0f, 1.0f)
{
	isRender = true;
	SetPriority(1);
	//�^�X�N���X�g�ɒǉ�
	CTaskManager::Get()->Add(this);
}
CCharacter::~CCharacter() {
	//�^�X�N���X�g����폜
	CTaskManager::Get()->Remove(this);
}