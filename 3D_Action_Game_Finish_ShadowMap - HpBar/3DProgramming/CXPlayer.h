#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollision.h"
#include "CParticle.h"
#include "CHpBar.h"
#include "CSound.h"
#include <vector>
/*
CXPlayer�N���X
�v���C���[�N���X
*/
class CXPlayer : public CXCharacter {
public:
	//�v���C���[�|�C���^
	static CXPlayer *mpPlayer;
	//�R���C�_���X�g
	std::vector<CCollider*> mColliders;

	CHPBar mHpBar;//HP�Q�[�W
	//�p�[�e�B�N���G�~�b�^�̐錾
	CEmitter mEmitter;

	CXPlayer()
		: mEmitter("tex_glow.tga", 10)
		, mHpBar(CVector3(), CVector2(30, 2), 100, 100)
	{
		mTag = EPLAYER;	//�^�O�Ƀv���C���[��ݒ�
	}
	/*
	�R���X�g���N�^
	m:�g�p���郂�f���̃|�C���^
	pos:�z�u������W
	*/
	CXPlayer(CModelX *m, CVector3 pos)
		: CXPlayer() 
	{
		Init(m); //����������
		mPosition = pos; //�ʒu�ݒ�
		//Task�}�l�[�W���ɒǉ�
		CTaskManager::Get()->Add(this);
	}
	~CXPlayer() {
		//�R���C�_�̍폜
		for (int i = 0; i < mColliders.size(); i++) {
			CCollisionManager::Get()->Remove(mColliders[i]);
		}
		mColliders.clear();
	}
	//����������
	void Init(CModelX*);
	//�X�V����
	void Update();
	//�Փˏ���
	bool Collision(CCollider *m, CCollider *y);
	//�`�揈��
	void Render();
};

#endif
