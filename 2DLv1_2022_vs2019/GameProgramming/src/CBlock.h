#pragma once
#include "CCharacter.h"
/*
* CBlock
* �u���b�N�N���X
* �}�b�v�̃u���b�N�Ɏg�p����
*/
class CBlock : public CCharacter
{
public:
	//CBlock(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CBlock(float x, float y, float w, float h, CTexture* pt);
	//Update�ł͉������Ȃ�
	void Update() {}
};