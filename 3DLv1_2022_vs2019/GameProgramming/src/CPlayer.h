#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�[�N���X�̃C���N���[�h
#include"CCharacter.h"
//�e�N���X�̃C���N���[�h
#include"CBullet.h"

#include "CColliderLine.h"

#include "CText.h"

/*
�v���C���[�N���X
�L�����N�^�[�N���X���p��
*/

class CPlayer : public CCharacter {
public:
	CPlayer();
	//CBullet�N���X�̃C���X�^���X�ϐ�
	/*CBullet bullet;*/
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
	//�`�揈��
	void Render();
	//�v���C���[�̃C���X�^���X���擾
	static CPlayer* Get();

private:
	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_
	CColliderLine mLine3; //�����R���C�_
	CText mText;
	//�v���C���[�̃C���X�^���X
	static CPlayer* spInstance;
	CCollider mCollider;	//�{�̗p�R���C�_

};
#endif 

