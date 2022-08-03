#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CCharacter.h"
/*
�J�����N���X
*/
class CCamera : public CCharacter {
public:
	CCamera(float distance);
	void Center(CVector& center);
	//��]
//	CVector mRotation;
	//���_���W�̎擾
	const CVector& Eye() const;
	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	//�J�����K�p
	void Render();
	static CCamera* Instance();
private:
	static CCamera* spInstance;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
	//
	//float mDistance;
};

//�J�����̊O���Q��
//extern CCamera Camera;
#endif
