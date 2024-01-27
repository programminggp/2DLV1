#ifndef CMODELX_H	//�C���N���[�h�K�[�h
#define CMODELX_H
#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j

class CModelX;	// CModelX�N���X�̐錾
class CModelXFrame;	// CModelXFrame�N���X�̐錾
class CMesh;	// CMesh�N���X�̐錾
class CMaterial;	//�}�e���A���̐錾
class CSkinWeights;	//�X�L���E�F�C�g�N���X
class CAnimationSet; //�A�j���[�V�����Z�b�g�N���X
class CAnimation; //�A�j���[�V�����N���X
class CAnimationKey;  //�A�j���[�V�����L�[�N���X

#define MODEL_FILE "res\\tsample.fbx"	//���̓t�@�C����

//�̈������}�N����
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = nullptr;}

//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*
 CModelX
 X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
public:

	std::vector<CModelXFrame*>& Frames();

	bool EOT();	//�g�[�N���I�������true
	//�P��̎��o��
	char* GetToken();
	char* Token();
	//void Render();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	~CModelX();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();

	CModelX();
	//�t�@�C���ǂݍ���
	void Load(const char* file);
	bool IsLoaded();
private:


	bool mLoaded;
	std::vector<CMaterial*> mMaterial;  //�}�e���A���z��
	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��

	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);

	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
};


#endif