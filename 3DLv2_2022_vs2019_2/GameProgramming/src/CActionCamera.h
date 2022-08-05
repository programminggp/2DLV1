#pragma once
#include "CVector.h"
#include "CCharacter.h"
/*
�J�����N���X
*/
class CActionCamera : public CCharacter {
public:
	CActionCamera(float distance);
	void Center(CVector& center);
	static CActionCamera* Instance();

	//�J�����X�V
	void CameraUpdate();
	//�J�����K�p
	void CameraRender();
	//�������Ȃ�
	void Render() {}
private:
	static CActionCamera* spInstance;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
};
