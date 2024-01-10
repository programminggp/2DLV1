#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CCharacter.h"
#include "CInput.h"

/*
�J�����N���X
*/
class CCamera : public CCharacter {
public:
	static CCamera* Get();
	CCamera(const CVector& pos, const CVector& rot, float distance);
	
	//���_���W�̎擾
	const CVector& Eye() const;
	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	void Update();
	//�J�����K�p
	void Render();
	//
	const CVector& VectorZ();
	const CVector& VectorX();

private:
	CInput mInput;
	float mMousePosX, mMousePosY;
	static CCamera* spInstance;
	CMatrix mModelView;
	CMatrix mProjection;
	CVector mVectorZ;
	CVector mVectorX;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
};

//�J�����̊O���Q��
//extern CCamera Camera;
#endif
