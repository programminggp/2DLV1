#pragma once
#include "CCharacter.h"
/*
* �|�C���g�N���X
* ���낢��ȃ|�C���g���쐬���܂�
*/
class CPoint : public CCharacter
{
public:
	//CPoint(X���W, Y���W, ��, ����, �^�O)
	CPoint(float x, float y, float w, float h, ETag t);
	void Update() {}	//�������Ȃ�
	void Render() {}	//�`�悵�Ȃ�
};