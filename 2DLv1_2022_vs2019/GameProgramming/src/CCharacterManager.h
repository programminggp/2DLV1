#pragma once
#include "CCharacter.h"
#include <vector>
/*
* CCharacter�N���X�̃C���X�^���X���Ǘ�����
*/
class CCharacterManager
{
private:
	//CCharacter�̃|�C���^�̉ϒ��z��
	std::vector<CCharacter*> mCharacters;
public:
	//static���\�b�h�͍ŏ�����쐬����A
	//�C���X�^���X�s�v�ŁA�ǂ��ł��ĂԂ��Ƃ��ł���B
	//CCharacterManager�̃C���X�^���X�̃|�C���^��Ԃ�
	static CCharacterManager* Get();
	//Add(CChracter�̃|�C���^)
	//�ϒ��z��̌��ɒǉ�����
	void Add(CCharacter* c);
	//�ϒ��z��ɂ���|�C���^��Update()�����s���Ă���
	void Update();
//	void Collision();
//	void Delete();
	//�ϒ��z��ɂ���|�C���^��Render()�����s���Ă���
	void Render();
};