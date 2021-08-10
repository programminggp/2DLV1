#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
/*
�J�����N���X
*/
class CCamera {
private:
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
public:
	//��]
	CVector mRotation;
	//���_���W�̎擾
	const CVector& Eye() const;
	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	//�J�����K�p
	void Render();
};

//�J�����̊O���Q��
extern CCamera Camera;
#endif
