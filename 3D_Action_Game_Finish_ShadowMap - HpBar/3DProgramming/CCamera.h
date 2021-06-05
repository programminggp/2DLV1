#pragma once

#include "CVector3.h"

/* �J�����N���X�i���_�̃N���X�j
�ڂ̈ʒu�ƖړI�̈ʒu��ێ����A
�J�����s��i�r���[�ϊ��s��j��ݒ肷��
*/
class CCamera {
public:
	float pos[3];	//�����_ [0]:X���W [1]:Y���W [2]:Z���W
	float eye[3];	//���_ [0]:X���W [1]:Y���W [2]:Z���W
	CVector3 mUp;	//�J�����̏����

	//�J�����̏�����̏�����
	CCamera();

	/* ���_�ƒ����_�̐ݒ�
	void setPos(float x, float y, float z)
	x:�����_��X���W y:�����_��Y���W z:�����_��Z���W
	�K��̎��_�͒����_���Y��+2�AZ��+4�ړ�
	*/
	void setPos(float x, float y, float z);

	/* �X�V����
	�L�[�ɂ�莋�_��ύX����
	J�F���O����@K�F�O�ʂ���@L�F�E�O����
	U�F����납��@I�F��납��@O�F�E��납��
	*/
	void update();

	void update(CVector3 eye, CVector3 pos, CVector3 up);
	//38
	static CMatrix44 mCameraInverse;
	static CMatrix44  GetInverse();
};
