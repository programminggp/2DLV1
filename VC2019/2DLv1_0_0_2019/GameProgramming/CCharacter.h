#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "CRectangle.h"

class CCharacter : public CRectangle {
public:
//	float mX, mY, mW, mH;
//	CRectangle mRect;

	//�^�O
	enum ETag {
		ENONE,
		EPLAYER,
		EBACKGROUND,
		EBOSS,
		EPLAYERSHOT,
		ESHOOTBOSS,
		EENEMYSHOT,
		EENEMY
	};
	ETag mTag;

	//�X�e�[�^�X
	enum EState {
		EDELETE,	//��
		EDISABLED,	//����
		EENABLED,	//�L��
	};
	EState mState;
	//�R���X�g���N�^
	CCharacter();
	virtual ~CCharacter();
	void Set(float x, float y, float w, float h);
	//�X�V����
	virtual void Update() {};
	//�`�揈��
	virtual void Render();
	//�Փˏ���
	virtual void Collision(CCharacter* mc, CCharacter* yc) {};

};

#endif