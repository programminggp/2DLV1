#pragma once
#include "CCharacter.h"
#include "CInput.h"

class CPlayer2 : public CCharacter
{
public:
	int Hp();
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CPlayer2(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CPlayer2(float x, float y, float w, float h, CTexture* pt);
	//�X�V����
	void Update();
private:
	int mInvincble;
	int mHp;
	CInput mInput;
};