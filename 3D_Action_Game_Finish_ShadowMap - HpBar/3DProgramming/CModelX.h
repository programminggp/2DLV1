#ifndef CMODELX_H
#define CMODELX_H
#include "CMyShader.h" //�V�F�[�_�[�̃C���N���[�h
#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix44.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CTexture.h"
#include "CMaterial.h"

//#define MODEL_FILE "sample.blend.x"
//#define MODEL_FILE "���O�i.x"	//���̓t�@�C����

//�|�C���^�z��̔j��
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*
���_�o�b�t�@�f�[�^�N���X
���_���Ƀf�[�^���܂Ƃ߂܂�
*/
class CMyVertex {
public:
	//�ʒu
	CVector3 mPosition;
	//�@��
	CVector3 mNormal;
	//�e�N�X�`���}�b�s���O
	CVector2 mTextureCoords;
	//�X�L���E�F�C�g
	float mBoneWeight[4];
	//�X�L���C���f�b�N�X
	float mBoneIndex[4];

	CMyVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};


class CModelX;	// CModelX�N���X�̐錾

/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey {
public:
	//����
	float mTime;
	//�s��
	CMatrix44 mMatrix;
};
/*
CAnimation
�A�j���[�V�����N���X
*/
class CAnimation {
public:
	char *mpFrameName;//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mKeyNum;	//�L�[���i���Ԑ��j
	CAnimationKey *mpKey;	//�L�[�̔z��

	CAnimation()
		: mpFrameName(0), mpKey(0)
	{}

	CAnimation(CModelX *model);

	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}

	CAnimation(const CAnimation& c) {
		mpFrameName = new char[strlen(c.mpFrameName) + 1];
		strcpy(mpFrameName, c.mpFrameName);
		mFrameIndex = c.mFrameIndex;
		mKeyNum = c.mKeyNum;
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			mpKey[i] = c.mpKey[i];
		}
	}

	const CAnimation operator=(const CAnimation &c) {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);

		mpFrameName = new char[strlen(c.mpFrameName) + 1];
		strcpy(mpFrameName, c.mpFrameName);
		mFrameIndex = c.mFrameIndex;
		mKeyNum = c.mKeyNum;
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			mpKey[i] = c.mpKey[i];
		}
		return (*this);
	}

};
/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet {
public:
	//�A�j���[�V������
	char *mpName;
	//�A�j���[�V����
	std::vector<CAnimation*> mAnimation;

	float mTime;	//���ݎ���
	float mWeight;	//�d��
	float mMaxTime;	//�ő厞��

	CAnimationSet()
		: mpName(0), mTime(0), mMaxTime(0), mWeight(0)
	{}

	CAnimationSet(CModelX *model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (int i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights {
public:
	char *mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mIndexNum;	//���_�ԍ���
	int *mpIndex;	//���_�ԍ��z��
	float *mpWeight;	//���_�E�F�C�g�z��
	CMatrix44 mOffset;	//�I�t�Z�b�g�}�g���b�N�X

	CSkinWeights(CModelX *model);

	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};


//CMesh�N���X�̒�`
class CMesh {
public:
	int mVertexNum;	//���_��
	CVector3 *mpVertex;	//���_�f�[�^
	int mFaceNum;	//�ʐ�
	int *mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
	int mNormalNum;	//�@����
	CVector3 *mpNormal;//�@���f�[�^
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;//�}�e���A���ԍ����i�ʐ��j
	int *mpMaterialIndex;	  //�}�e���A���ԍ�
	std::vector<CMaterial*> mMaterial;//�}�e���A���f�[�^
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*> mSkinWeights;
	CVector3 *mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector3 *mpAnimateNormal;	//�A�j���[�V�����p�@��
	//�e�N�X�`�����W�f�[�^
	CVector2 *mpTextureCoords;

	//37
	//�}�e���A�����̖ʐ�
	std::vector<int> mMaterialVertexCount;
	//���_�o�b�t�@���ʎq
	GLuint	  mMyVertexBufferId;
	//���_�o�b�t�@�̍쐬
	void CreateVertexBuffer();


	//�R���X�g���N�^
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(0)
		, mNormalNum(0)
		, mpNormal(0)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(0)
		, mpAnimateVertex(0)
		, mpAnimateNormal(0)
		, mpTextureCoords(0)
		, mMyVertexBufferId(0)
	{}
	//�f�X�g���N�^
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//�X�L���E�F�C�g�̍폜
		for (int i = 0; i < mSkinWeights.size(); i++) {
			delete mSkinWeights[i];
		}
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
	}
	//�ǂݍ��ݏ���
	void Init(CModelX *model);
	void Render();
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX *model);
	void AnimateVertex(CMatrix44*);
};

//CModelXFrame�N���X�̒�`
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix44 mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�
	CMesh mMesh;	//Mesh�f�[�^
	CMatrix44 mCombinedMatrix;	//�����s��
	CModelXFrame()
		: mIndex(0)
		, mpName(0)
	{};
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame() {
		//�q�t���[����S�ĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete *itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
	void Render();
	//�����s��̍쐬
	void Animate(CMatrix44* parent);

};

class CModelX {
public:
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��
	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<CMaterial*> mMaterial;	//�}�e���A���̔z��
	std::vector<CTexture*> mTexture;	//�e�N�X�`���̔z��
	//37
	CMatrix44 *mpSkinningMatrix; //�V�F�[�_�[�p�X�L���}�g���b�N�X
	CMyShader mShader; //�V�F�[�_�[�̃C���X�^���X

	CModelX()
		: mpPointer(0)
		, mpSkinningMatrix(0) //37
	{}

	~CModelX() {
		delete mFrame[0];
		for (int i = 0; i < mAnimationSet.size(); i++) {
			delete mAnimationSet[i];
		}
		//�}�e���A���̉��
		for (int i = 0; i < mMaterial.size(); i++) {
			delete mMaterial[i];
		}
		//�e�N�X�`���̉��
		for (int i = 0; i < mTexture.size(); i++) {
			delete mTexture[i];
		}
		//37
		SAFE_DELETE_ARRAY(mpSkinningMatrix);
	}
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
	void Render();
	CModelXFrame* FindFrame(char* name);
	void AnimateFrame();
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();
	void AnimateVertex(CMatrix44*);
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);
	//�e�N�X�`���̌���
	CTexture* FindTexture(char* name);
	//37
	//�V�F�[�_�[���g�����`��
	void RenderShader(CMatrix44 *m);

	void AddMaterial(CModelX*, CMaterial*);
	void SeparateAnimationSet(int start, int end, char* name);
};

#endif
