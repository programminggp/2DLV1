#ifndef CMODELX_H	//�C���N���[�h�K�[�h
#define CMODELX_H
#include <vector>		//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"

class CModelX;			// CModelX�N���X�̐錾
class CModelXFrame;		// CModelXFrame�N���X�̐錾
class CMesh;			// CMesh�N���X�̐錾
class CMaterial;		//�}�e���A���̐錾

#define MODEL_FILE "res\\sample.blend.x"	//���̓t�@�C���� \�́�

//CMesh�N���X�̒�`
class CMesh {
public:
	void Render();
	//�R���X�g���N�^
	CMesh();
	//�f�X�g���N�^
	~CMesh();
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
private:
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;//�}�e���A���ԍ����i�ʐ��j
	int* mpMaterialIndex;	  //�}�e���A���ԍ�
	std::vector<CMaterial*> mMaterial;//�}�e���A���f�[�^

	int mNormalNum;	//�@����
	CVector* mpNormal;//�@���x�N�g��

	int mFaceNum;	//�ʐ�
	int* mpVertexIndex;	//�ʂ��\�����钸�_�C���f�b�N�X
	int mVertexNum;	//���_��
	CVector* mpVertex;	//���_�f�[�^
};

//CModelXFrame�N���X�̒�`
class CModelXFrame {
	friend CModelX;
public:
	void Render();
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame();
private:
	CMesh* mpMesh;	//Mesh�f�[�^
	std::vector<CModelXFrame*> mChild;  //�q�t���[���̔z��
	CMatrix mTransformMatrix;  //�ϊ��s��
	char* mpName;   //�t���[�����O
	int mIndex;  //�t���[���ԍ�
};


//�̈������}�N����
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = nullptr;}
/*
 CModelX
 X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
	friend CModelXFrame;
public:
	bool EOT(); // �g�[�N���������Ȃ�����true
	void Render();
	char* Token();

	~CModelX();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();

	//�P��̎��o��
	char* GetToken();

	CModelX();
	//�t�@�C���ǂݍ���
	void Load(char* file);
private:
	std::vector<CModelXFrame*> mFrame;  //�t���[���̔z��
	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);

	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
};

#endif
