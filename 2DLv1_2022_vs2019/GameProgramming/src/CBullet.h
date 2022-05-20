#pragma once
#include "CCharacter.h"

class CBullet : public CCharacter
{
public:
	//�Փˏ����Q
	void Collision();
	//�Փˏ����S
	//Collision(�����̃|�C���^, �Փˑ���̃|�C���^)
	void Collision(CCharacter* m, CCharacter* o);
	//CBullet(X���W,Y���W,��,����,�摜�E,�摜��,�摜��,�摜��,�e�N�X�`���̃|�C���^)
	CBullet(float x, float y, float w, float h,float l, float r, float b, float t, CTexture* pt);
	CBullet();
	void Update();
	//void Render();
	bool Collision(CRectangle* rect);
};