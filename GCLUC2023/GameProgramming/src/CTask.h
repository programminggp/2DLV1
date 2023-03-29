#pragma once
#include<string>
 
class CTaskManager;
class CCharacter;

enum class ETaskPriority
{
	EUI,                //UI
	ETITLE,             //�^�C�g�����
	ECharacter,         //�L�����N�^�[
	ECharacterManager,  //�L�����N�^�[�}�l�[�W���[
	EBackGround = 1003, //�w�i
	EBackGround2 = 1003,
	EBackGround3 = 1003,
	EBackGround4 = 1003,
	EBLOCK = 0,
};

class CTask
{
	friend CTaskManager;
public:
	enum class ETag
	{
		EZERO,
		EPLAYER,    //�v���C���[
		EENEMY,     //�G
		EBULLET,    //�v���C���[�̍U��
		EATTACK,    //�G�̍U��(����\)
		EATTACK2,   //�G�̍U��(������Ɗm��_���[�W)
		EITEM,
		EBLOCK,
	};
private:
	CTask* mpprev;   //�O�̃^�X�N�ւ̃|�C���^
	CTask* mpnext;   //���̃^�X�N�ւ̃|�C���^
	int mpriority;   //�D��x

protected:
	ETag mTag;

public:
	ETag Tag();
	//�R���X�g���N�^
	CTask(int priority);
	//~�f�X�g���N�^
	~CTask();

	//�D��x��ݒ�
	void Setpriority(int priority);
	//�D��x���擾
	int GetPriority() const;
	//�^�X�N���폜
	void Delete();

	//�`�揈��
	virtual void Render() {};
	//�X�V����
	virtual void Update() {};
	//�Փˏ���
	virtual void Collision(CCharacter* m, CCharacter* o) {}
};