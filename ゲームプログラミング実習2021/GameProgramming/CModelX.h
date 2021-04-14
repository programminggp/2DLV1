#ifndef CMODEL_H
#define CMODEL_H

#define MODEL_FILE "sample.blend.x"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}



#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
class CModelX;	// CModelX�N���X�̐錾

//CModelXFrame�N���X�̒�`
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�
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

};

#endif
