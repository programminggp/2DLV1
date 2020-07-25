#ifndef CC5_H
#define CC5_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
//
#include "CPoint.h"

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CC5 : public CCharacter {
public:
	CPoint *mpPoint;//�ڎw���|�C���g
	int mHp;
	//�R���C�_
	CCollider mCollider;
	CCollider mSearch;
	//�R���X�g���N�^
	//CC5(���f��, �ʒu, ��], �g�k)
	CC5(CModel *model, CVector position, CVector rotation, CVector scale);
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);

};


#endif
