#pragma once
#include "CCharacter.h"

class CEnemy : public CCharacter
{
public:
	//CEnemy(X��W,Y��W,��,����,�摜�E,�摜��,�摜��,�摜��,�e�N�X�`���̃|�C���^)
	CEnemy(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt);
	void Update();
	bool Collision(CRectangle* rect);
	void Collision();
	void Collision(CCharacter* m, CCharacter* o);
};