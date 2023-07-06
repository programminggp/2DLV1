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
	CActionCamera();
	//�C���X�^���X�̎擾
	static CActionCamera* Instance();
	//�J������X���擾
	CVector VectorX();
	//�J������Z���擾
	CVector VectorZ();
	//�ݒ胁�\�b�h(����, X��],Y��])
	void Set(float distance, float xaxis, float yaxis);
	//�J�����X�V
	void Update();
	//�J�����K�p
	void Render();
private:
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
	//
	CInput mInput;
};

#endif

