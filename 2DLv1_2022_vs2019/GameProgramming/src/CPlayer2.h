#pragma once
#include "CCharacter.h"
#include "CInput.h"

class CPlayer2 : public CCharacter
{
public:
	//�C���X�^���X�̎擾
	static CPlayer2* Instance();
	//HP���擾
	static int Hp();
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CPlayer2(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CPlayer2(float x, float y, float w, float h, CTexture* pt);
	//�X�V����
	void Update();
private:
	static CPlayer2* spInstance; //�C���X�^���X�̃|�C���^
	static int sHp;	//HP
	int mInvincible; //���G�J�E���^
	CInput mInput;
};