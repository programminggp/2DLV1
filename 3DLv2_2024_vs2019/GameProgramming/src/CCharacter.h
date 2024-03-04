#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include <stdio.h>

#define VELOCITY 2.0f	//�ړ����x

class CCharacter : public CRectangle
{
public:
	enum class ETag
	{
		EZERO,		//�����l
		EBULLET,	//�e
		EENEMY,		//�G
		EPLAYER,	//�v���C���[
		ETURN,		//�܂�Ԃ�
		EBLOCK,		//�u���b�N
	};
	enum class EState	//���
	{
		EMOVE,	//�ړ�
		ESTOP,	//��~
		EJUMP,	//�W�����v
		ECRY,	//����
	};
protected:
	float mVx;	//X�����x
	float mVy;	//Y�����x
	bool mEnabled;
	ETag mTag;
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	EState State();	//��Ԃ��擾����
	bool Enabled();
	ETag Tag();
	//�Փˏ����Q
	virtual void Collision() {};
	//�Փˏ����S
	//Collision(�����̃|�C���^, �Փˑ���̃|�C���^)
	virtual void Collision(CCharacter* m, CCharacter* o) {};
	virtual void Update() = 0;
	CCharacter();
	CTexture* Texture();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	virtual void Render();
	void Move();
};