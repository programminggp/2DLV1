#ifndef CACTIONCAMERA_H
#define CACTIONCAMERA_H

#include "CVector.h"
#include "CTransform.h"
#include "CMatrix.h"
/*
�J�����N���X
*/
class CActionCamera : public CTransform {
public:
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
	const CMatrix& ModelView();
	const CMatrix& ModelViewInv();
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
	//CVector sScale; //�g��k���{��
	CMatrix mModelViewInv;
};

//extern CActionCamera ActionCamera;
#endif