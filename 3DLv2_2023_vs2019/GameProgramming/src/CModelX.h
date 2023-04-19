#ifndef CMODELX_H	//�C���N���[�h�K�[�h
#define CMODELX_H
#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"

class CModelX;	// CModelX�N���X�̐錾
class CModelXFrame;	// CModelXFrame�N���X�̐錾
class CMesh;	// CMesh�N���X�̐錾
class CMaterial;	//�}�e���A���̐錾
class CSkinWeights;	//�X�L���E�F�C�g�N���X

#define MODEL_FILE "res\\sample.blend.x"	//���̓t�@�C����

//�̈������}�N����
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = nullptr;}
/*
 CModelX
 X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
	friend CModelXFrame;
//	friend CMesh;
//	friend CMaterial;
public:
	bool EOT();	//�g�[�N���I�������true
	//�P��̎��o��
	char* GetToken();
	char* Token();
	void Render();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	~CModelX();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();

	CModelX();
	//�t�@�C���ǂݍ���
	void Load(char* file);
private:
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��

	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);

	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
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
	CMesh *mpMesh;	//Mesh�f�[�^
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�
};

//CMesh�N���X�̒�`
class CMesh {
//	friend CModelX;
//	friend CModelXFrame;
public:
	void Render();
	//�R���X�g���N�^
	CMesh();
	//�f�X�g���N�^
	~CMesh();
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
private:
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*> mSkinWeights;
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

/*
 CSkinWeights
 �X�L���E�F�C�g�N���X
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights();
	const int& FrameIndex();
	const CMatrix& Offset();
private:
	char* mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mIndexNum;	//���_�ԍ���
	int* mpIndex;	//���_�ԍ��z��
	float* mpWeight;	//���_�E�F�C�g�z��
	CMatrix mOffset;	//�I�t�Z�b�g�}�g���b�N�X
};


#endif