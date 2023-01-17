#ifndef CMODELX_H //�C���N���[�h�K�[�h
#define CMODELX_H

#include<vector>//vecotr�N���X�̃C���N���[�h(���I�z�u)
#include"CMatrix.h"//�}�g���N�X�N���X�̃C���N���[�h
#include"CMyShader.h" //�V�F�[�_�[�̃C���N���[�h
#include"CVector.h"



#define MODEL_FILE "res\\sample.blend.x"//���̓t�@�C����
//�̈������}�N����
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))
//#define MODEL_FILE "res\\���O�i.x"    //���̓t�@�C����


class CModelX;//cNodelX�N���X�̐錾
class CModelXFrame;
class CMaterial;
class CMesh;//�t�����h��`�p
class CAnimationSet; //�t�����h�p
class CAnimation;


/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
	friend CModelX;
	//friend CMyShader;
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
	//friend CMyShader;
	char* mpFrameName; //�t���[����
	int mFrameIndex; //�t���[���ԍ�
public:
	CAnimation(CModelX* model);
	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
	CAnimation();
private:
	int mKeyNum; //�L�[��(����)
	CAnimationKey* mpKey; //�L�[�̔z��
};

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet {
	friend CModelX;
	//friend CMyShader;
	//�A�j���[�V�����Z�b�g��
	char* mpName;
public:
	CAnimationSet(CModelX* model);
	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (size_t i = 0; i < mAnimation.size(); i++)
		{
			delete mAnimation[i];
		}
	}
	void Time(float time);
	void Weight(float weight);
	int Time();
	int MaxTime();
	CAnimationSet();
private:
	//�A�j���[�V����
	std::vector<CAnimation*>mAnimation;
	float mTime; //���ݎ���
	float mWeight; //�d��
	float mMaxTime;//�ő厞��
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
	friend CMyShader;
	char* mpFrameName; //�t���[����
	int mFrameIndex; //�t���[���ԍ�
	int mIndexNum; //���_�ԍ���
	int* mpIndex; //���_�ԍ��z��
	float* mpWeight; //���_�E�F�C�g�z��
	CMatrix mOffset; //�I�t�Z�b�g�}�g���N�X
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
		const int& FrameIndex();
		const CMatrix& Offset();
	}
};


//CMesh�N���X�̒�`
class CMesh {
	friend CModelX;
	friend CModelXFrame;
	friend CMyShader;
	int mVertexNum; //���_��
	CVector* mpVertex; //���_�f�[�^
	int mFaceNum; //�摜
	int* mpVertexIndex; //����\�����钸�_�ԍ�
	int mNormalNum; //�@����
	CVector* mpNormal; //�@���x�N�g��
	int mMaterialNum; //�}�e���A����
	int mMaterialIndexNum; //m�}�e���A���ԍ���(�搔)
	int* mpMaterialIndex; //�}�e���A���ԍ�
	std::vector<CMaterial*>mMaterial; //�}�e���A���f�[�^
	std::vector<CSkinWeights*>mSkinWeights;
	//�e�N�X�`�����W�f�[�^
	float* mpTextureCoords;
public:
	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
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
	~CMesh();
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
	void Render();
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX* model);
	void AnimateVertex(CMatrix*);
	//�}�e���A�����ʐ�
	std::vector<int> mMaterialVertexCount;
	//���_�o�b�t�@���ʎq
	GLuint mMyVertexBufferId;
	//���_�o�b�t�@�쐬
	void CreateVertexBuffer();
private:
	CVector* mpAnimateVertex; //�A�j���[�V�����p���_
	CVector* mpAnimateNormal;//�A�j���[�V�����p�@��

};


//CNodelXFrame�N���X�̒�`
class CModelXFrame {
	friend CModelX;
	friend CAnimation;
	friend CMyShader;
	std::vector<CModelXFrame*>mChild;//�q�t���[���̔z�u
	CMatrix mTransformMatrix;//�ϊ��s��
	char* mpName;//�t���[�����O
	int mIndex;//�t���[���ԍ�
public:
	CModelXFrame(CModelX* model);//�R���X�g���N�^
	~CModelXFrame() {
		//�q�t���[����S�ĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr  = mChild.begin(); itr != mChild.end(); itr++)
		{
			delete* itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
		
	}
	void Render();
	void AnimateCombined(CMatrix* parent);
	const CMatrix& CombinedMatrix();
	CModelXFrame()
		:mpName(nullptr)
		, mIndex(0){}
private:
	CMesh mMesh; //Mesh�f�[�^
	CMatrix mCombinedMatrix; //�����s��
};

/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
	friend CModelXFrame;
	friend CMesh;
	friend CAnimationSet;
	friend CAnimation;
	friend CMyShader;
	char* mpPointer;//�ǂݎ��ʒu
	char mToken[1024];//���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame;//�t���[���̔z�u
	std::vector<CMaterial*>mMaterial;
public:
	CModelX();
	~CModelX();
	//�t�@�C���̓ǂݍ���
	void Load(char* file);
	void GetToken();//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	//�����f�[�^�̎擾
	int GetIntToken();
	void Render();
	char* Token();
	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);
	std::vector<CAnimationSet*>& AnimationSet();
	void AnimateFrame();
	std::vector<CModelXFrame*>& Frames();
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);
	std::vector<CMaterial*>&Material();
	void AnimateVertex(CMatrix*);
	/*
    �A�j���[�V�����𔲂��o��
    idx:�����������A�j���[�V�����Z�b�g�̔ԍ�
    start:�����������A�j���[�V�����Z�b�g�̊J�n����
    end:�����������A�j���[�V�����Z�b�g�̏I������
    name:�ǉ�����A�j���[�V�����Z�b�g�̖��O
    */
	void CModelX::SeparateAnimationSet(int idx, int start, int end, char* name);
	//�V�F�[�_�[���g�����`��
	void RenderShader(CMatrix* m);
	//�A�j���[�V�����Z�b�g�̒ǉ�
	void AddAnimationSet(const char* file);


private:
	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*>mAnimationSet;
	//�V�F�[�_�[�p�X�L���}�g���b�N�X
	CMatrix* mpSkinningMatrix;
	CMyShader mShader;//�V�F�[�_�[�̃C���X�^���X

};

#endif 

