#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"

#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

/*
�J�����N���X
*/
class CCamera {
public:
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector &eye, const CVector &center, const CVector &up);
	//�J�����K�p
	void Render();
};

//�J�����̊O���Q��
extern CCamera Camera;

#endif
