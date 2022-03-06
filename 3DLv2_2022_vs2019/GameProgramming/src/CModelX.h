#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "���O�i.x"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"
#include "CMyShader.h" //�V�F�[�_�[�̃C���N���[�h

class CModelX;	// CModelX�N���X�̐錾
class CMaterial;	//�N���X�̐錾
class CAnimation;
class CAnimationSet;
class CModelXFrame;
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
public:
	CAnimationKey();
};
/*
 CAnimation
 �A�j���[�V�����N���X
*/
class CAnimation {
	friend CAnimationSet;
	friend CModelX;

	char* mpFrameName;//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mKeyNum;	//�L�[���i���Ԑ��j
	CAnimationKey* mpKey;	//�L�[�̔z��
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

	//�A�j���[�V�����Z�b�g��
	char* mpName;
	//�A�j���[�V����
	std::vector<CAnimation*> mAnimation;
	float mTime;	//���ݎ���
	float mWeight;	//�d��
	float mMaxTime;	//�ő厞��
public:
	CAnimationSet();
	CAnimationSet(CModelX* model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (size_t i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}

	const float& Time();
	const float& MaxTime();
	void Time(float time);
	void Weight(float wight);
};
/*
 CSkinWeights
 �X�L���E�F�C�g�N���X
*/
class CSkinWeights {
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
	friend CModelX;
	friend CModelXFrame;

	//�}�e���A�����̖ʐ�
	std::vector<int> mMaterialVertexCount;
	//���_�o�b�t�@���ʎq
	GLuint	  mMyVertexBufferId;
	unsigned int mVertexNum;	//���_��
	CVector* mpVertex;	//���_�f�[�^
	unsigned int mFaceNum;	//�ʐ�
	unsigned int* mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
	unsigned int mNormalNum;	//�@����
	CVector* mpNormal;//�@���f�[�^

	unsigned int mMaterialNum;	//�}�e���A����
	unsigned int mMaterialIndexNum;//�}�e���A���ԍ����i�ʐ��j
	unsigned int* mpMaterialIndex;	  //�}�e���A���ԍ�
	std::vector<CMaterial*> mMaterials;//�}�e���A���f�[�^
	CVector* mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector* mpAnimateNormal;	//�A�j���[�V�����p�@��
	//�e�N�X�`�����W�f�[�^
	float* mpTextureCoords;

	//�X�L���E�F�C�g
	std::vector<CSkinWeights*> mSkinWeights;

public:

	const unsigned int& FaceNum();
	std::vector<CSkinWeights*>& SkinWeights();
	const GLuint& MyVertexBufferId();
	std::vector<CMaterial*>& Materials();
	std::vector<int>& MaterialVertexCount();

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
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
		//�X�L���E�F�C�g�̍폜
		for (size_t i = 0; i < mSkinWeights.size(); i++) {
			delete mSkinWeights[i];
		}
	}
	//�ǂݍ��ݏ���
	void Init(CModelX* model);

	void Render();
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX* model);

	void AnimateVertex(CMatrix*);
	//���_�o�b�t�@�̍쐬
	void CreateVertexBuffer();
};

//CModelXFrame�N���X�̒�`
class CModelXFrame {
	friend CModelX;
	friend CAnimation;
	friend CMesh;

	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�
	CMesh mMesh;	//Mesh�f�[�^
	CMatrix mCombinedMatrix;	//�����s��
public:

	CMesh& Mesh();	//Mesh�f�[�^
	const CMatrix& CombinedMatrix();	//�����s��
	void TransformMatrix(const CMatrix& matrix);

	CModelXFrame()
		: mpName(nullptr)
		, mIndex(0) {}	//�R���X�g���N�^

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

	void Render();
	//�����s��̍쐬
	void AnimateCombined(CMatrix* parent);

};


class CModelX {
	friend CModelXFrame;
	friend CMesh;
	friend CSkinWeights;
	friend CAnimationSet;
	friend CAnimation;

	CMyShader mShader; //�V�F�[�_�[�̃C���X�^���X
	//�V�F�[�_�[�p�X�L���}�g���b�N�X
	CMatrix* mpSkinningMatrix;
	char* mpPointer;
	char mToken[1024];
	std::vector<CModelXFrame*> mFrames;	//�t���[���̔z��
	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*> mAnimationSets;
	std::vector<CMaterial*> mMaterials;	//�}�e���A���̔z��
public:
	std::vector<CMaterial*>& Materials();
	char* Token();
	std::vector<CModelXFrame*>& Frames();
	CMatrix* SkinningMatrix();
	std::vector<CAnimationSet*>& AnimationSets();

	CModelX();
	~CModelX();

	void Load(char* file);
	//�t�@�C������A�j���[�V�����Z�b�g��ǉ�����
	void AddAnimationSet(char* file);

	//�P��̎��o��
	void GetToken();

	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();

	//���������_�f�[�^�̎擾
	float GetFloatToken();

	//�����f�[�^�̎擾
	int GetIntToken();

	void Render();

	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);

	//�t���[���̕ϊ��s����A�j���[�V�����f�[�^�ōX�V����
	void AnimateFrame();

	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();

	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();
	void AnimateVertex(CMatrix*);

	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);

	/*
	�A�j���[�V�����𔲂��o��
	idx:�����������A�j���[�V�����Z�b�g�̔ԍ�
	start:�����������A�j���[�V�����̊J�n����
	end:�����������A�j���[�V�����̏I������
	name:�ǉ�����A�j���[�V�����Z�b�g�̖��O
	*/
	void CModelX::SeparateAnimationSet(int idx, int start, int end, char* name);
	//�V�F�[�_�[���g�����`��
	void RenderShader(CMatrix* m);
	//���f���̓��͏�
	//�߂�l�Ftrue�F���͍�  false�F������
	bool IsLoaded();
};

#endif
