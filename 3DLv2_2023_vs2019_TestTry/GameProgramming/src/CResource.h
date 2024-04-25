#pragma once
class CResourceManager;

// ���\�[�X�Ǘ�����N���X�̃x�[�X�N���X
class CResource
{
	friend CResourceManager;

public:
	// �Q�ƃJ�E���g���Z
	void Referenced();
	// ���\�[�X���
	virtual void Release();

protected:
	// �R���X�g���N�^
	CResource();
	// �f�X�g���N�^
	virtual ~CResource();

	// �V�[���؂�ւ��ō폜���邩�ǂ�����ݒ�
	void SetDontDelete(bool del);
	// ���\�[�X�ǂݍ���
	virtual bool Load(std::string path, bool dontDelete) = 0;

	EScene mSceneType;		// ��������V�[���̎��
	int mReferenceCount;	// �Q�ƃJ�E���g
};