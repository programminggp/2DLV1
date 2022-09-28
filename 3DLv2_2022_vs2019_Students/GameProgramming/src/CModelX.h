#pragma once
#ifndef CMODELX_H	//�C���N���[�h�K�[�h
#define CMODELX_H
#include "CMyShader.h" //�V�F�[�_�[�̃C���N���[�h

class CMaterial;	//�N���X�̐錾

#define MODEL_FILE "res\\���O�i.x"	//���̓t�@�C����
//#define MODEL_FILE "res\\sample.blend.x"	//���̓t�@�C����

//�̈������}�N����
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
class CModelX;	// CModelX�N���X�̐錾
class CModelXFrame;
class CMesh;
class CAnimationSet;
class CAnimation;
/*
 CAnimationKey
 �A�j���[�V�����L�[�N���X
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
	friend CModelX;

	//����
	float mTime;
	//�s��
	CMatrix mMatrix;
};

/*
 CAnimation
 �A�j���[�V�����N���X
*/
class CAnimation {
	friend CAnimationKey;
	friend CAnimationSet;
	friend CModelX;

	int mKeyNum;	//�L�[���i���Ԑ��j
	CAnimationKey* mpKey;	//�L�[�̔z��

	char* mpFrameName;//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
public:
	CAnimation();
	CAnimation(CModelX* model);

	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

/*
 CAnimationSet
 �A�j���[�V�����Z�b�g
*/
class CAnimationSet {
	friend CModelX;
	float mTime;		//���ݎ���
	float mWeight;	//�d��
	float mMaxTime;	//�ő厞��
	//�A�j���[�V����
	std::vector<CAnimation*> mAnimation;

	//�A�j���[�V�����Z�b�g��
	char* mpName;
public:
	CAnimationSet();
	float Time();
	float MaxTime();
	void Time(float time); //���Ԃ̐ݒ�
	void Weight(float weight); //�d�݂̐ݒ�
	CAnimationSet(CModelX* model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (size_t i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}
};

/*
 CSkinWeights
 �X�L���E�F�C�g�N���X
*/
class CSkinWeights {
	friend CMyShader;
	friend CModelX;
	friend CMesh;

	char* mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mIndexNum;	//���_�ԍ���
	int* mpIndex;	//���_�ԍ��z��
	float* mpWeight;	//���_�E�F�C�g�z��
	CMatrix mOffset;	//�I�t�Z�b�g�}�g���b�N�X
public:
	CSkinWeights(CModelX* model);

	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
	const int& FrameIndex();
	const CMatrix& Offset();
};


//CMesh�N���X�̒�`
class CMesh {
	friend CMyShader;
	friend CModelX;
	friend CModelXFrame;
private:
	//�}�e���A�����̖ʐ�
	std::vector<int> mMaterialVertexCount;
	//���_�o�b�t�@���ʎq
	GLuint	  mMyVertexBufferId;
	//���_�o�b�t�@�̍쐬
	void CreateVertexBuffer();

	//�e�N�X�`�����W�f�[�^
	float* mpTextureCoords;
	CVector* mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector* mpAnimateNormal;	//�A�j���[�V�����p�@��
	int mVertexNum;	//���_��
	CVector* mpVertex;	//���_�f�[�^
	int mFaceNum;	//�ʐ�
	int* mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
	int mNormalNum;	//�@����
	CVector* mpNormal;//�@���x�N�g��
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;//�}�e���A���ԍ����i�ʐ��j
	int* mpMaterialIndex;	  //�}�e���A���ԍ�
	std::vector<CMaterial*> mMaterial;//�}�e���A���f�[�^
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*> mSkinWeights;

public:
	void AnimateVertex(CMatrix*);
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX* model);
	void Render();
	//�R���X�g���N�^
	CMesh()
		: mVertexNum(0)
		, mpVertex(nullptr)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
		, mpAnimateVertex(nullptr)
		, mpAnimateNormal(nullptr)
		, mpTextureCoords(nullptr)
		, mMyVertexBufferId(0)
	{}
	//�f�X�g���N�^
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//�X�L���E�F�C�g�̍폜
		for (size_t i = 0; i < mSkinWeights.size(); i++)
		{
			delete mSkinWeights[i];
		}
		SAFE_DELETE_ARRAY(mpTextureCoords);
	}
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
};

//CModelXFrame�N���X�̒�`
class CModelXFrame {
	friend CMyShader;
//	friend CMesh;
	friend CAnimation;
	friend CModelX;

	CMatrix mCombinedMatrix;	//�����s��
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�
	CMesh mMesh;	//Mesh�f�[�^
public:
	CModelXFrame()
		: mpName(nullptr)
		, mIndex(0) {}	//�R���X�g���N�^
	const CMatrix& CombinedMatrix();	//�����s��
	//�����s��̍쐬
	void AnimateCombined(CMatrix* parent);
	void Render();
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

/*
 CModelX
 X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
	friend CMyShader;
	friend CAnimation;
	friend CAnimationSet;
	friend CModelXFrame;
	friend CMesh;
private:
	//�V�F�[�_�[�p�X�L���}�g���b�N�X
	CMatrix* mpSkinningMatrix;
	CMyShader mShader; //�V�F�[�_�[�̃C���X�^���X

	std::vector<CMaterial*> mMaterial;	//�}�e���A���̔z��
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��
	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*> mAnimationSet;
public:
	//�V�F�[�_�[���g�����`��
	void RenderShader(CMatrix* m);

	/*
	�A�j���[�V�����𔲂��o��
	idx:�����������A�j���[�V�����Z�b�g�̔ԍ�
	start:�����������A�j���[�V�����̊J�n����
	end:�����������A�j���[�V�����̏I������
	name:�ǉ�����A�j���[�V�����Z�b�g�̖��O
	*/
	void CModelX::SeparateAnimationSet(
		int idx, int start, int end, char* name);

	void AnimateVertex(CMatrix*);
	std::vector<CModelXFrame*>& Frames();	//�t���[���̔z��
	std::vector<CMaterial*>& Material();
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);
	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	void AnimateFrame();
	std::vector<CAnimationSet*>& AnimationSet();
	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);

	void Render();
	CModelX();
	~CModelX();

	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	//�����f�[�^�̎擾
	int GetIntToken();
	char* Token();
};


#endif

