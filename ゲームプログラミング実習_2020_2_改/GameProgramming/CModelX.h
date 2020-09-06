#ifndef CMODELX_H	//�C���N���[�h�K�[�h
#define CMODELX_H

#define MODEL_FILE "���O�i.x"	//���̓t�@�C����
//#define MODEL_FILE "sample.blend.x"	//���̓t�@�C����

//�̈������}�N����
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"

//09
class CMaterial;

class CModelX;	// CModelX�N���X�̐錾

class CModel;
/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey {
public:
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
public:
	char *mpFrameName;//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mKeyNum;	//�L�[���i���Ԑ��j
	CAnimationKey *mpKey;	//�L�[�̔z��

	CAnimation(CModelX *model);

	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
	}
};

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet {
public:
	//�A�j���[�V�����Z�b�g��
	char *mpName;
	//�A�j���[�V����
	std::vector<CAnimation*> mAnimation;

	float mTime;	//���ݎ���
	float mWeight;	//�d��
	float mMaxTime;	//�ő厞��

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
	CMatrix mOffset;	//�I�t�Z�b�g�}�g���b�N�X

	CSkinWeights(CModelX *model);

	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};
//class CModel;
#include "CModel.h"
//CMesh�N���X�̒�`
class CMesh : CModel {
	CModelX* mpModel;
public:
	int mVertexNum;	//���_��
	CVertex *mpVertex;	//���_�f�[�^
	int mFaceNum;	//�ʐ�
	int *mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
	int mNormalNum;	//�@����
	CVector *mpNormal;//�@���f�[�^

	//09
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;//�}�e���A���ԍ����i�ʐ��j
	int *mpMaterialIndex;	  //�}�e���A���ԍ�
//	std::vector<CMaterial*> mMaterial;//�}�e���A���f�[�^
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*> mSkinWeights;

	CVector *mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector *mpAnimateNormal;	//�A�j���[�V�����p�@��
	//�e�N�X�`�����W�f�[�^
	float *mpTextureCoords;

	//�R���X�g���N�^
	CMesh()
		: mpModel(0)
		, mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(0)
		, mNormalNum(0)
		, mpNormal(0)
		//
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(0)
		//
		, mpAnimateVertex(0)
		, mpAnimateNormal(0)
		, mpTextureCoords(0)
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
	void AnimateVertex(CMatrix*);
};


//CModelXFrame�N���X�̒�`
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�

	//CMesh mMesh;	//Mesh�f�[�^

	CMatrix mCombinedMatrix;	//�����s��

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
	void AnimateCombined(CMatrix* parent);
};
/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
public:
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��
	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<CMaterial*> mMaterial;	//�}�e���A���̔z��
	std::vector<CMesh*> mMesh;

	CModelX() 
		: mpPointer(0)
	{}

	~CModelX() {
		for (int i = 0; i < mMesh.size(); i++) {
			delete mMesh[i];
		}
		//�}�e���A���̉��
		for (int i = 0; i < mMaterial.size(); i++) {
			delete mMaterial[i];
		}
		for (int i = 0; i < mAnimationSet.size(); i++) {
			delete mAnimationSet[i];
		}		
		delete mFrame[0];

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
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);
	void AnimateVertex(CMatrix*);

};

#endif
