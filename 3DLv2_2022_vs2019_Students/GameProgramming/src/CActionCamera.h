#pragma once
#include "CVector.h"
#include "CTransform.h"
#include "CMatrix.h"
/*
�J�����N���X
*/
class CActionCamera2;

class CActionCamera : public CTransform 
{
	friend CActionCamera2;
public:
	CVector& Eye();
	//���[���h���W���X�N���[�����W�֕ϊ�����
	//WorldToScreen(�X�N���[�����W, ���[���h���W)
	bool WorldToScreen(CVector* screen, const CVector& world);
	//�C���X�^���X�̎擾
	static CActionCamera* Instance();
	//�J������X���擾
	CVector VectorX();
	//�J������Z���擾
	CVector VectorZ();
	//�R���X�g���N�^(����, X��],Y��])
	CActionCamera(float distance, float xaxis, float yaxis);
	//�J�����X�V
	void Update();
	//�J�����K�p
	void Render();
private:
	int mScreenWidth; //��
	int mScreenHeight; //����
	CMatrix mProjection; //�v���W�F�N�V�����s��
	CMatrix mModelView; //���f���r���[�s��
	//�C���X�^���X
	static CActionCamera* spInstance;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
};

class CActionCamera2 : public CActionCamera {
public:
	void TargetEye(const CVector& eye);
	void TargetCenter(const CVector& center);

	//�R���X�g���N�^(����, X��],Y��])
	CActionCamera2(float distance, float xaxis, float yaxis);
	//�J�����X�V
	void Update();
	//�J�����K�p
	//void Render();
private:
	//���_
	CVector mTargetEye;
	//�����_
	CVector mTargetCenter;
	//�����
	CVector mTargetUp;
};
