#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"

/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CCharacter3 {
public:
	//CBullet bullet;
	CPlayer() {}
	//CPlayer(�ʒu, ��], �X�P�[��)
	CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);
	//�X�V����
	void Update();
private:
	CInput mInput;
};

#endif
