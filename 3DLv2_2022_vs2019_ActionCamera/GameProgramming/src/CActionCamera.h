#pragma once
#include "CVector.h"
#include "CCharacter.h"
#include "CMatrix.h"

/*
�J�����N���X
*/
class CActionCamera : public CCharacter {
public:
	static const CMatrix& ModelViewInverse();
	static const CMatrix& ModelView();
	CActionCamera(float distance);
	CActionCamera(float distance, float xaxis, float yaxis);
	static CActionCamera* Instance();

	//�J�����X�V
	void CameraUpdate();
	//�J�����K�p
	void CameraRender();
	//�������Ȃ�
	void Render() {}
private:
	static CMatrix mModelViewInverse;
	static CMatrix mModelView;
	static CActionCamera* spInstance;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
};
