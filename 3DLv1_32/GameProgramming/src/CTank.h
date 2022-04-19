#ifndef CTANK_H
#define CTANK_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"


/*
�C���N���X
*/
class CTank2 : public CCharacter
{
public:
	CTank2(CCharacter* parent);
	void Update();
private:
	static CModel mModel;
	CCharacter* mpParent;
};

/*
��ԃN���X
�L�����N�^�N���X���p��
*/
class CTank : public CCharacter {
public:
	//�R���X�g���N�^
	CTank();
	//Tank(�ʒu, ��], �g�k)
	CTank(const CVector& position, const CVector& rotation,
		const CVector& scale);
	//�X�V����
	void Update();
private:
	//���f���f�[�^
	static CModel mModel;
};

#endif
