#ifndef CENEMY_H
#define CENEMY_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CCollider.h"

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy : public CCharacter3 {
public:
	//�Փˏ���
	void Collision();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	////�m�F�p���\�b�h�@�폜�\��
	//void CEnemy::Render() {
	//	CCharacter3::Render();
	//	mCollider1.Render();
	//	mCollider2.Render();
	//	mCollider3.Render();
	//}

	//�R���X�g���N�^
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	//�X�V����
	void Update();
private:
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;

};

#endif
