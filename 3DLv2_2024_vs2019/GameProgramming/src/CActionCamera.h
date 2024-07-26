#ifndef CACTIONCAMERA_H
#define CACTIONCAMERA_H

#include "CVector.h"
#include "CTransform.h"
#include "CMatrix.h"
#include "CInput.h"
/*
�J�����N���X
*/
class CActionCamera : public CTransform {
public:
	//���[���h���W���X�N���[�����W�֕ϊ�����
	//WorldToScreen(�X�N���[�����W, ���[���h���W)
	bool WorldToScreen(
		CVector* screen, const CVector& world);

	//�J������X���擾
	CVector VectorX();
	//�J������Z���擾
	CVector VectorZ();

	CActionCamera();
	//�C���X�^���X�̎擾
	static CActionCamera* Instance();

	//�ݒ胁�\�b�h(����, X��],Y��])
	void Set(float distance, float xaxis, float yaxis);
	//�J�����X�V
	void Update();
	//�J�����K�p
	void Render();
private:
	int mScreenWidth; //��
	int mScreenHeight; //����
	CMatrix mProjection; //�v���W�F�N�V�����s��

	//�C���X�^���X
	static CActionCamera* spInstance;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
	//���f���r���[�s��
	CMatrix mModelView;
	//���̓N���X
	CInput mInput;
};
#endif

