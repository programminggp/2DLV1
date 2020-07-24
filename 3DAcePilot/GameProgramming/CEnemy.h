#ifndef CENEMY_H
#define CENEMY_H
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
class CEnemy : public CCharacter {
//	float mRx;
public:
	int mHp;
	//�R���C�_
	CCollider mCollider;
	CCollider mSearch;
	//?
	//�U���|�C���g
	static CPoint *mPoint;
	static int mPointSize;//�|�C���g�̐�
	CPoint *mpPoint;//�ڎw���|�C���g
	int mPointCnt;//�|�C���g�̃J�E���^
	//�R���X�g���N�^
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CEnemy(CModel *model, CVector position, CVector rotation, CVector scale);
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);

	//void Render() {
	//	CCharacter::Render();
	//	mCollider.Render();
	//}
};

#endif
