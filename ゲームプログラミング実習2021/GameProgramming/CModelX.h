#ifndef CMODEL_H
#define CMODEL_H

#define MODEL_FILE "sample.blend.x"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))



#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"

class CModelX;	// CModelX�N���X�̐錾


//CMesh�N���X�̒�`
class CMesh {
public:
	int mVertexNum;	//���_��
	CVector* mpVertex;	//���_�f�[�^
	int mFaceNum;	//�ʐ�
	int* mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�

	//�R���X�g���N�^
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
	{}
	//�f�X�g���N�^
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
	}
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
};

//CModelXFrame�N���X�̒�`
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�
	CMesh mMesh;	//Mesh�f�[�^

	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame() {
		//�q�t���[����S�ĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete* itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
};


class CModelX {
public:
	char* mpPointer;
	char mToken[1024];
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��

	CModelX()
		: mpPointer(nullptr)
	{}

	~CModelX() {
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
	}

	void Load(char* file);

	//�P��̎��o��
	void GetToken();

	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();

	//���������_�f�[�^�̎擾
	float GetFloatToken();

	//�����f�[�^�̎擾
	int GetIntToken();

};

#endif
