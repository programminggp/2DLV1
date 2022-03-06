#include "glew.h"
#include <stdio.h>
#include <string.h>	//������֐��̃C���N���[�h

#include "CModelX.h"

#include "CMaterial.h"

#include "CVertex.h"

#define VERTEX_SHADER "res\\skinmesh.vert"		//���_�V�F�[�_�[
#define FRAGMENT_SHADER "res\\skinmesh.frag"	//�t���O�����g�V�F�[�_�[

std::vector<CMaterial*>& CModelX::Materials()
{
	return mMaterials;
}

char* CModelX::Token()
{
	return mToken;
}

std::vector<CModelXFrame*>& CModelX::Frames()
{
	return mFrames;
}

CMatrix* CModelX::SkinningMatrix()
{
	return mpSkinningMatrix;
}

std::vector<CAnimationSet*>& CModelX::AnimationSets()
{
	return mAnimationSets;
}

CModelX::CModelX()
	: mpPointer(nullptr)
	, mpSkinningMatrix(nullptr)
{
	//mToken��������
	memset(mToken, 0, sizeof(mToken));
}

CModelX::~CModelX() 
{
	if (mFrames.size() > 0)
	{
		delete mFrames[0];
	}
	for (size_t i = 0; i < mAnimationSets.size(); i++) {
		delete mAnimationSets[i];
	}
	//�}�e���A���̉��
	for (size_t i = 0; i < mMaterials.size(); i++) {
		delete mMaterials[i];
	}
	SAFE_DELETE_ARRAY(mpSkinningMatrix);
}

void CModelX::Load(char* file)
{
	FILE *fp;
	fp = fopen(file, "rb");
	if (fp == NULL)
	{
		printf("fopen error:%s\n", file);
		return;
	}
	fseek(fp, 0L, SEEK_END);
	unsigned int size = ftell(fp);
	char *buf = mpPointer = new char[size + 1];
	fseek(fp, 0L, SEEK_SET);
	fread(buf, size, 1, fp);
	buf[size] = '\0';
	fclose(fp);

	//�_�~�[���[�g�t���[���̍쐬
	CModelXFrame* p = new CModelXFrame();
	//���O�Ȃ�
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	//�t���[���z��ɒǉ�
	mFrames.push_back(p);

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();	//�P��̎擾
		//template �ǂݔ�΂�
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//Material �̎�
		else if (strcmp(mToken, "Material") == 0) {
			new CMaterial(this);
		}
		//�P�ꂪFrame�̏ꍇ
		else if (strcmp(mToken, "Frame") == 0) {
			//�t���[�����擾
			GetToken();
			if (strchr(mToken, '{')) {
				//�t���[�����Ȃ��F�X�L�b�v
				SkipNode();
				GetToken(); //}
			}
			else {
				//�t���[�����������
				if (FindFrame(mToken) == 0) {
					//�t���[�����쐬����
					p->mChild.push_back(
						new CModelXFrame(this));
				}
			}
		}
		//�P�ꂪAnimationSet�̏ꍇ
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}

	SAFE_DELETE_ARRAY(buf);
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	SetSkinWeightFrameIndex();
	//���_�o�b�t�@�̍쐬
	for (size_t i = 0; i < mFrames.size(); i++) {
		if (mFrames[i]->mMesh.mFaceNum > 0) {
			mFrames[i]->mMesh.CreateVertexBuffer();
		}
	}
	//�X�L���}�g���b�N�X�̃G���A�쐬
	mpSkinningMatrix = new CMatrix[mFrames.size()];
	//�V�F�[�_�[�ǂݍ���
	mShader.Load(VERTEX_SHADER, FRAGMENT_SHADER);
}

void CModelX::AddAnimationSet(char* file)
{
	FILE* fp;
	fp = fopen(file, "rb");
	if (fp == NULL)
	{
		printf("fopen error:%s\n", file);
		return;
	}
	fseek(fp, 0L, SEEK_END);
	unsigned int size = ftell(fp);
	char* buf = mpPointer = new char[size + 1];
	fseek(fp, 0L, SEEK_SET);
	fread(buf, size, 1, fp);
	buf[size] = '\0';
	fclose(fp);

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();	//�P��̎擾
		//template �ǂݔ�΂�
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		/*
		//Material �̎�
		else if (strcmp(mToken, "Material") == 0) {
			new CMaterial(this);
		}
		//�P�ꂪFrame�̏ꍇ
		else if (strcmp(mToken, "Frame") == 0) {
			//�t���[�����擾
			GetToken();
			if (strchr(mToken, '{')) {
				//�t���[�����Ȃ��F�X�L�b�v
				SkipNode();
				GetToken(); //}
			}
			else {
				//�t���[�����������
				if (FindFrame(mToken) == 0) {
					//�t���[�����쐬����
					p->mChild.push_back(
						new CModelXFrame(this));
				}
			}
		}
		*/
		//�P�ꂪAnimationSet�̏ꍇ
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}
	SAFE_DELETE_ARRAY(buf);
}
/*
GetToken
������f�[�^����A�P���1�擾����
*/
void CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	//��( )�^�u(\t)���s(\r)(\n)�C�G�h�ȊO�̕����ɂȂ�܂œǂݔ�΂�
	/*
	strchr(������, ����)
	������ɕ������܂܂�Ă���΁A�������������ւ̃|�C���^��Ԃ�
	������Ȃ�������NULL��Ԃ�
	*/
	while (*p != '\0' && strchr(" \t\r\n,;\"", *p)) p++;
	if (*p == '{' || *p == '}') {
		//{�܂���}�Ȃ�mToken�ɑ�������̕�����
		*q++ = *p++;
	}
	else {
		//��( )�^�u(\t)���s(\r)(\n)�C�G�h}�̕����ɂȂ�܂�mToken�ɑ������
		while (*p != '\0' && !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0';	//mToken�̍Ō��\0����
	mpPointer = p;	//���̓ǂݍ��ރ|�C���g���X�V����

	//����mToken��//�̏ꍇ�́A�R�����g�Ȃ̂ŉ��s�܂œǂݔ�΂�
	/*
	strcmp(������1, ������2)
	������1�ƕ�����2���������ꍇ�A0��Ԃ��܂��B
	������1�ƕ�����2���������Ȃ��ꍇ�A0�ȊO��Ԃ��܂��B
	*/
	if (!strcmp("//", mToken)) {
		//���s�܂œǂݔ�΂�
		while (*p != '\0' && !strchr("\r\n", *p)) p++;
		//�ǂݍ��݈ʒu�̍X�V
		mpPointer = p;
		//�P����擾����i�ċA�Ăяo���j
		GetToken();
	}
}
/*
SkipNode
�m�[�h��ǂݔ�΂�
*/
void CModelX::SkipNode() {
	//�������I�������I��
	while (*mpPointer != '\0') {
		GetToken();	//���̒P��擾
		//{�����������烋�[�v�I��
		if (strchr(mToken, '{')) break;
	}
	int count = 1;
	//�������I��邩�A�J�E���g��0�ɂȂ�����I��
	while (*mpPointer != '\0' && count > 0) {
		GetToken();	//���̒P��擾
		//{��������ƃJ�E���g�A�b�v
		if (strchr(mToken, '{')) count++;
		//}��������ƃJ�E���g�_�E��
		else if (strchr(mToken, '}')) count--;
	}
}

CMesh& CModelXFrame::Mesh()
{
	return mMesh;
}

const CMatrix& CModelXFrame::CombinedMatrix()
{
	return mCombinedMatrix;
}

void CModelXFrame::TransformMatrix(const CMatrix& matrix)
{
	mTransformMatrix = matrix;
}

/*
 CModelXFrame
 model�FCModelX�C���X�^���X�ւ̃|�C���^
 �t���[�����쐬����
 �ǂݍ��ݒ���Frame��������΁A�t���[�����쐬���A
 �q�t���[���ɒǉ�����
*/
CModelXFrame::CModelXFrame(CModelX* model) {
	//���݂̃t���[���z��̗v�f�����擾���ݒ肷��
	mIndex = model->mFrames.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrames.push_back(this);
	//�ϊ��s���P�ʍs��ɂ���
	mTransformMatrix.Identity();
	//���̒P��i�t���[�����̗\��j���擾����
	//model->GetToken(); // frame name
	//�t���[�������G���A���m�ۂ���
	mpName = new char[strlen(model->mToken) + 1];
	//�t���[�������R�s�[����
	strcpy(mpName, model->mToken);
	//���̒P��i{�̗\��j���擾����
	model->GetToken();  // {
		//�����������Ȃ�����I���
	while (*model->mpPointer != '\0') {
		//���̒P��擾
		model->GetToken(); // Frame
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}')) break;
		//�V�ȃt���[���̏ꍇ�́A�q�t���[���ɒǉ�
		if (strcmp(model->mToken, "Frame") == 0) {
			//�t���[�����擾
			model->GetToken();
			if (strchr(model->mToken, '{')) {
				//�t���[�����Ȃ��F�X�L�b�v
				model->SkipNode();
				model->GetToken(); //}
			}
			else {
				//�t���[�����������
				if (model->FindFrame(model->mToken) == 0) {
					//�t���[�����쐬���A�q�t���[���̔z��ɒǉ�
					mChild.push_back(new CModelXFrame(model));
				}
			}
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0) {
			model->GetToken(); // {
			for (int i = 0; i < mTransformMatrix.Size(); i++) {
				mTransformMatrix.M()[i] = model->GetFloatToken();
			}
			model->GetToken(); // }
		}
		else if (strcmp(model->mToken, "Mesh") == 0) {
			mMesh.Init(model);
		}
		else {
			//��L�ȊO�̗v�f�͓ǂݔ�΂�
			model->SkipNode();
		}
	}
}
/*
GetFloatToken
�P��𕂓������_�^�̃f�[�^�ŕԂ�
*/
float CModelX::GetFloatToken() {
	GetToken();
	//atof
	//�������float�^�֕ϊ�
	return atof(mToken);
}
/*
GetIntToken
�P��𐮐��^�̃f�[�^�ŕԂ�
*/
int CModelX::GetIntToken() {
	GetToken();
	return atoi(mToken);
}
const unsigned int& CMesh::FaceNum()
{
	return mFaceNum;
}

std::vector<CSkinWeights*>& CMesh::SkinWeights()
{
	return mSkinWeights;
}
const GLuint& CMesh::MyVertexBufferId()
{
	return mMyVertexBufferId;
}
std::vector<CMaterial*>& CMesh::Materials()
{
	return mMaterials;
}
std::vector<int>& CMesh::MaterialVertexCount()
{
	return mMaterialVertexCount;
}
/*
 Init
 Mesh�̃f�[�^����荞��
*/
void CMesh::Init(CModelX* model) {
	model->GetToken();	// { or ���O
	if (!strchr(model->mToken, '{')) {
		//���O�̏ꍇ�A����{
		model->GetToken();	// {
	}
	//���_���̎擾
	mVertexNum = model->GetIntToken(); //printf("VertexNum:%d\n", mVertexNum);
	//���_�����G���A�m��
	mpVertex = new CVector[mVertexNum];
	mpAnimateVertex = new CVector[mVertexNum];
	//���_�����f�[�^����荞��
	for (unsigned int i = 0; i < mVertexNum; i++) {
		mpVertex[i].X(model->GetFloatToken());
		mpVertex[i].Y(model->GetFloatToken());
		mpVertex[i].Z(model->GetFloatToken());
	}
	mFaceNum = model->GetIntToken();	//�ʐ��ǂݍ���
//���_����1�ʂ�3���_
	mpVertexIndex = new unsigned int[mFaceNum * 3];
	for (unsigned int i = 0; i < mFaceNum * 3; i += 3) {
		model->GetToken();	//���_���ǂݔ�΂�
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
	}
	//�����������Ȃ�����I���
	while (model->mpPointer != '\0') {
		model->GetToken();	//MeshNormals
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}'))
			break;
		if (strcmp(model->mToken, "MeshNormals") == 0) {
			model->GetToken();	// {
			//�@���f�[�^�����擾
			mNormalNum = model->GetIntToken();
			//�@���̃f�[�^��z��Ɏ�荞��
			CVector* pNormal = new CVector[mNormalNum];
			for (unsigned int i = 0; i < mNormalNum; i++) {
				pNormal[i].X(model->GetFloatToken());
				pNormal[i].Y(model->GetFloatToken());
				pNormal[i].Z(model->GetFloatToken());
			}
			//�@����=�ʐ��~�R
			mNormalNum = model->GetIntToken() * 3; //FaceNum
			int ni;
			//���_���ɖ@���f�[�^��ݒ肷��
			mpNormal = new CVector[mNormalNum];
			mpAnimateNormal = new CVector[mNormalNum];
			for (unsigned int i = 0; i < mNormalNum; i += 3) {
				model->GetToken(); // 3
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 1] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[] pNormal;
			model->GetToken();	// }
		}
		// MeshMaterialList�̂Ƃ�
		else if (strcmp(model->mToken, "MeshMaterialList") == 0) {
			model->GetToken(); // {
			// Material�̐�
			mMaterialNum = model->GetIntToken();
			// FaceNum
			mMaterialIndexNum = model->GetIntToken();
			//�}�e���A���C���f�b�N�X�̍쐬
			mpMaterialIndex = new unsigned int[mMaterialIndexNum];
			for (unsigned int i = 0; i < mMaterialIndexNum; i++) {
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//�}�e���A���f�[�^�̍쐬
			for (unsigned int i = 0; i < mMaterialNum; i++) {
				model->GetToken();	// Material
				if (strcmp(model->mToken, "Material") == 0) {
					mMaterials.push_back(new CMaterial(model));
				}
				else {
					// {  ���o
					model->GetToken();	//MaterialName
					mMaterials.push_back(
						model->FindMaterial(model->mToken));
					model->GetToken();	// }
				}

			}
			model->GetToken();	// } //End of MeshMaterialList
		}
		//SkinWeights�̂Ƃ�
		else if (strcmp(model->mToken, "SkinWeights") == 0) {
			//CSkinWeights�N���X�̃C���X�^���X���쐬���A�z��ɒǉ�
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		//�e�N�X�`�����W�̎�
		else if (strcmp(model->mToken, "MeshTextureCoords") == 0) {
			model->GetToken();	// {
			//�e�N�X�`�����W�����擾
			int textureCoordsNum = model->GetIntToken() * 2;
			//�e�N�X�`�����W�̃f�[�^��z��Ɏ�荞��
			mpTextureCoords = new float[textureCoordsNum];
			for (int i = 0; i < textureCoordsNum; i++) {
				mpTextureCoords[i] = model->GetFloatToken();
			}
			model->GetToken();	// }
		}
		else {
			//�ȊO�̃m�[�h�͓ǂݔ�΂�
			model->SkipNode();
		}

	}
}
/*
 Render
 ��ʂɕ`�悷��
*/
void CMesh::Render() {
	/* ���_�f�[�^�C�@���f�[�^�̔z���L���ɂ��� */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z���L���ɂ���
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	/* ���_�f�[�^�C�@���f�[�^�̏ꏊ���w�肷�� */
	glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);

	/* ���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷�� */
	for (unsigned int i = 0; i < mFaceNum; i++) {
		//�}�e���A����K�p����
		mMaterials[mpMaterialIndex[i]]->Enabled();
		glDrawElements(GL_TRIANGLES, 3,
			GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		mMaterials[mpMaterialIndex[i]]->Disabled();
	}

	/* ���_�f�[�^�C�@���f�[�^�̔z��𖳌��ɂ��� */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
/*
 Render
 ���b�V���̖ʐ���0�ȊO�Ȃ�`�悷��
*/
void CModelXFrame::Render() {
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}
/*
Render
�S�Ẵt���[���̕`�揈�����Ăяo��
*/
void CModelX::Render() {
	for (size_t i = 0; i < mFrames.size(); i++) {
		mFrames[i]->Render();
	}
}

/*
CSkinWeights
�X�L���E�F�C�g�̓ǂݍ���
*/
CSkinWeights::CSkinWeights(CModelX* model)
	: mpFrameName(0)
	, mFrameIndex(0)
	, mIndexNum(0)
	, mpIndex(nullptr)
	, mpWeight(nullptr)
{
	model->GetToken();	// {
	model->GetToken();	// FrameName
	//�t���[�����G���A�m�ہA�ݒ�
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//���_�ԍ����擾
	mIndexNum = model->GetIntToken();
	//���_�ԍ�����0�𒴂���
	if (mIndexNum > 0) {
		//���_�ԍ��ƒ��_�E�F�C�g�̃G���A�m��
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//���_�ԍ��擾
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		//���_�E�F�C�g�擾
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
	}
	//�I�t�Z�b�g�s��擾
	for (int i = 0; i < 16; i++) {
		mOffset.M()[i] = model->GetFloatToken();
	}
	model->GetToken();	// }
}
const int& CSkinWeights::FrameIndex()
{
	return mFrameIndex;
}
const CMatrix& CSkinWeights::Offset()
{
	return mOffset;
}
CAnimationSet::CAnimationSet()
	:mpName(nullptr)
	, mMaxTime(0.0f)
	, mTime(0.0f)
	, mWeight(0.0f)
{
}
/*
CAnimationSet
*/
CAnimationSet::CAnimationSet(CModelX* model)
	: mpName(nullptr)
	, mTime(0)
	, mWeight(0)
	, mMaxTime(0)
{
	model->mAnimationSets.push_back(this);
	model->GetToken();	// Animation Name
	//�A�j���[�V�����Z�b�g����ޔ�
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken(); // {
	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or Animation
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Animation") == 0) {
			 //Animation�v�f�ǂݍ���
			mAnimation.push_back(new CAnimation(model));
		}
	}
	//�I�����Ԑݒ�
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
}

const float& CAnimationSet::Time()
{
	return mTime;
}

const float& CAnimationSet::MaxTime()
{
	return mMaxTime;
}

void CAnimationSet::Time(float time)
{
	mTime = time;
}

void CAnimationSet::Weight(float wight)
{
	mWeight = wight;
}
/*
 FindFrame
 �t���[�����ɊY������t���[���̃A�h���X��Ԃ�
*/
CModelXFrame* CModelX::FindFrame(char* name) {
	//�C�e���[�^�̍쐬
	std::vector<CModelXFrame*>::iterator itr;
	//�擪����Ō�܂ŌJ��Ԃ�
	for (itr = mFrames.begin(); itr != mFrames.end(); itr++) {
		//���O����v�������H
		if (strcmp(name, (*itr)->mpName) == 0) {
			//��v�����炻�̃A�h���X��Ԃ�
			return *itr;
		}
	}
	//��v����t���[�������ꍇ��NULL��Ԃ�
	return NULL;
}
CAnimation::CAnimation()
	:mpFrameName(nullptr)
	, mFrameIndex(0)
	, mKeyNum(0)
	, mpKey(nullptr)
{
}
CAnimation::CAnimation(CModelX* model)
	: mpFrameName(0)
	, mFrameIndex(0)
	, mKeyNum(0)
	, mpKey(nullptr)
{
	model->GetToken(); // { or Animation Name
	if (strchr(model->mToken, '{')) {
		model->GetToken(); // {
	}
	else {
		model->GetToken(); // {
		model->GetToken(); // {
	}

	model->GetToken(); //FrameName
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex =
		model->FindFrame(model->mToken)->mIndex;
	model->GetToken(); // }
	//�L�[�̔z���ۑ����Ă����z��
	CMatrix* key[4] = { 0, 0, 0, 0 };
	//���Ԃ̔z���ۑ����Ă����z��
	float* time[4] = { 0, 0, 0, 0 };
	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or AnimationKey
		if (strchr(model->mToken, '}')) break;
		if (strcmp(model->mToken, "AnimationKey") == 0) {
			model->GetToken(); // {
			//�f�[�^�̃^�C�v�擾
			int type = model->GetIntToken();
			//���Ԑ��擾
			mKeyNum = model->GetIntToken();
			switch (type) {
			case 0:
				// Rotation Quaternion
				//�s��̔z������Ԑ����m��
				key[type] = new CMatrix[mKeyNum];
				//���Ԃ̔z������Ԑ����m��
				time[type] = new float[mKeyNum];
				//���Ԑ����J��Ԃ�
				for (int i = 0; i < mKeyNum; i++) {
					//���Ԏ擾
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 4��ǂݔ�΂�
					//w,x,y,z���擾
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//�N�H�[�^�j�I������]�s��֕ϊ�
					key[type][i].Quaternion(x, y, z, w);
				}
				break;
			case 1:
				//�g��E�k���̍s��쐬
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].Scale(x,y,z);
				}
				break;
			case 2: //�ړ��̍s��쐬
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].Translate(x, y, z);
				}
				break;
			case 4: //�s��f�[�^���擾
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					mpKey[i].mTime = model->GetFloatToken(); // Time
					model->GetToken(); // 16
					for (int j = 0; j < 16; j++) {
						mpKey[i].mMatrix.M()[j] = model->GetFloatToken();
					}
				}
				break;
			}
			model->GetToken(); // }
		}
		else {
			model->SkipNode();
		}
	}
	//�s��f�[�^�ł͂Ȃ���
	if (mpKey == 0) {
		//���Ԑ����L�[���쐬
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			//���Ԑݒ�
			mpKey[i].mTime = time[2][i]; // Time
			//�s��쐬 Size * Rotation * Position
			mpKey[i].mMatrix = key[1][i] * key[0][i] * key[2][i];
		}
	}
	//�m�ۂ����G���A���
	for (int i = 0; i < ARRAY_SIZE(key); i++) {
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(key[i]);
	}
}
/*
AnimateFrame
�t���[���̕ϊ��s����A�j���[�V�����f�[�^�ōX�V����
*/
void CModelX::AnimateFrame() {
	//�A�j���[�V�����œK�p�����t���[����
	//�ϊ��s����[���N���A����
	for (size_t i = 0; i < mAnimationSets.size(); i++) {
		CAnimationSet* anim = mAnimationSets[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0) continue;
		//�t���[�����iAnimation���j�J��Ԃ�
		for (size_t j = 0; j < anim->mAnimation.size(); j++) {
			CAnimation* animation = anim->mAnimation[j];
			//�Y������t���[���̕ϊ��s����[���N���A����
			memset(&mFrames[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix));
		}
	}
	//�A�j���[�V�����ɊY������t���[���̕ϊ��s���
	//�A�j���[�V�����̃f�[�^�Őݒ肷��
	for (size_t i = 0; i < mAnimationSets.size(); i++) {
		CAnimationSet* anim = mAnimationSets[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0) continue;
		//�t���[�����iAnimation���j�J��Ԃ�
		for (size_t j = 0; j < anim->mAnimation.size(); j++) {
			//�t���[�����擾����
			CAnimation* animation = anim->mAnimation[j];
			CModelXFrame* frame = mFrames[animation->mFrameIndex];
			//�L�[���Ȃ��ꍇ�͔�΂�
			if (animation->mpKey == 0) continue;
			//���Ԃ��擾
			float time = anim->mTime;
			//�ŏ��̎��Ԃ�菬�����ꍇ
			if (time < animation->mpKey[0].mTime) {
				//�ϊ��s���0�R�}�ڂ̍s��ōX�V
				frame->mTransformMatrix += animation->mpKey[0].mMatrix * anim->mWeight;
			}
			//�Ō�̎��Ԃ��傫���ꍇ
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime) {
				//�ϊ��s����Ō�̃R�}�̍s��ōX�V
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix * anim->mWeight;
			}
			else {
				//���Ԃ̓r���̏ꍇ
				for (int k = 1; k < animation->mKeyNum; k++) {
					//�ϊ��s����A���`��ԂɂčX�V
					if (time < animation->mpKey[k].mTime &&
						animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime) {
						float r = (animation->mpKey[k].mTime - time) /
							(animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
						frame->mTransformMatrix +=
							(animation->mpKey[k - 1].mMatrix * r + animation->mpKey[k].mMatrix * (1 - r)) * anim->mWeight;
						break;
					}
				}
			}
		}
	}

}
/*
 AnimateCombined
 �����s��̍쐬
*/
void CModelXFrame::AnimateCombined(CMatrix* parent) {
	//�����̕ϊ��s��ɁA�e����̕ϊ��s����|����
	mCombinedMatrix = mTransformMatrix * (*parent);
	//�q�t���[���̍����s����쐬����
	for (size_t i = 0; i < mChild.size(); i++) {
		mChild[i]->AnimateCombined(&mCombinedMatrix);
	}

}
/*
SetSkinWeightFrameIndex
�X�L���E�F�C�g�Ƀt���[���ԍ���ݒ肷��
*/
void CModelX::SetSkinWeightFrameIndex() {
	//�t���[�������J��Ԃ�
	for (size_t i = 0; i < mFrames.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrames[i]->mMesh.mFaceNum > 0) {
			//�X�L���E�F�C�g���J��Ԃ�
			for (size_t j = 0; j < mFrames[i]->mMesh.mSkinWeights.size(); j++) {
				//�t���[�����̃t���[�����擾����
				CModelXFrame* frame = FindFrame(mFrames[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//�t���[���ԍ���ݒ肷��
				mFrames[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
			}
		}
	}
}
/* AnimateVertex ���_�ɃA�j���[�V������K�p */
void CMesh::AnimateVertex(CModelX* model) {
	//�A�j���[�V�����p�̒��_�G���A�N���A
	memset(mpAnimateVertex, 0, sizeof(CVector) * mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector) * mNormalNum);
	//�X�L���E�F�C�g���J��Ԃ�
	for (size_t i = 0; i < mSkinWeights.size(); i++) {
		//�t���[���ԍ��擾
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//�I�t�Z�b�g�s��ƃt���[�������s�������
		CMatrix mSkinningMatrix = mSkinWeights[i]->mOffset * model->mFrames[frameIndex]->mCombinedMatrix;
		//���_�����J��Ԃ�
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//���_�ԍ��擾
			int index = mSkinWeights[i]->mpIndex[j];
			//�d�ݎ擾
			float weight = mSkinWeights[i]->mpWeight[j];
			//���_�Ɩ@�����X�V����
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//�@���𐳋K������
	for (unsigned int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}
/*
AnimateVertex
���_�ɃA�j���[�V������K�p����
*/
void CModelX::AnimateVertex() {
	//�t���[�������J��Ԃ�
	for (size_t i = 0; i < mFrames.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrames[i]->mMesh.mFaceNum > 0) {
			//���_���A�j���[�V�����ōX�V����
			mFrames[i]->mMesh.AnimateVertex(this);
		}
	}
}
/*
 FindMaterial
 �}�e���A�����ɊY������}�e���A����ԋp����
*/
CMaterial* CModelX::FindMaterial(char* name) {
	//�}�e���A���z��̃C�e���[�^�쐬
	std::vector<CMaterial*>::iterator itr;
	//�}�e���A���z���擪���珇�Ɍ���
	for (itr = mMaterials.begin(); itr != mMaterials.end(); itr++) {
		//���O����v����΃}�e���A���̃|�C���^��ԋp
		if (strcmp(name, (*itr)->Name()) == 0) {
			return *itr;
		}
	}
	//��������NULL��ԋp
	return NULL;
}
void CModelX::SeparateAnimationSet(int idx, int start, int end, char* name)
{
	CAnimationSet* anim = mAnimationSets[idx];//��������A�j���[�V�����Z�b�g���m��
	CAnimationSet* as = new CAnimationSet();//�A�j���[�V�����Z�b�g�̐���
	as->mpName = new char[strlen(name) + 1];
	strcpy(as->mpName, name);
	as->mMaxTime = end - start;
	for (size_t i = 0; i < anim->mAnimation.size(); i++) {//�����̃A�j���[�V�������J��Ԃ�
		CAnimation* animation = new CAnimation();//�A�j���[�V�����̐���
		animation->mpFrameName = new char[strlen(anim->mAnimation[i]->mpFrameName) + 1];
		strcpy(animation->mpFrameName, anim->mAnimation[i]->mpFrameName);
		animation->mFrameIndex = anim->mAnimation[i]->mFrameIndex;
		animation->mKeyNum = end - start + 1;
		animation->mpKey = new CAnimationKey[animation->mKeyNum];//�A�j���[�V�����L�[�̐���
		animation->mKeyNum = 0;
		for (int j = start; j <= end && j < anim->mAnimation[i]->mKeyNum; j++) {
			if (j < anim->mAnimation[i]->mKeyNum)
			{
				animation->mpKey[animation->mKeyNum] = anim->mAnimation[i]->mpKey[j];
			}
			else
			{
				animation->mpKey[animation->mKeyNum] =
					anim->mAnimation[i]->mpKey[anim->mAnimation[i]->mKeyNum - 1];
			}
			animation->mpKey[animation->mKeyNum].mTime = animation->mKeyNum++;
			//animation->mpKey[animation->mKeyNum] = anim->mAnimation[i]->mpKey[j];
			//animation->mpKey[animation->mKeyNum].mTime = animation->mKeyNum;
			//animation->mKeyNum++;
		}//�A�j���[�V�����L�[�̃R�s�[
		as->mAnimation.push_back(animation);//�A�j���[�V�����̒ǉ�
	}
	mAnimationSets.push_back(as);//�A�j���[�V�����Z�b�g�̒ǉ�

}
void CModelX::AnimateVertex(CMatrix* mat) {
	//�t���[�������J��Ԃ�
	for (size_t i = 0; i < mFrames.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrames[i]->mMesh.mFaceNum > 0) {
			//���_���A�j���[�V�����ōX�V����
			mFrames[i]->
				mMesh.AnimateVertex(mat);
		}
	}
}
void CMesh::AnimateVertex(CMatrix* mat) {
	//�A�j���[�V�����p�̒��_�G���A�N���A
	memset(mpAnimateVertex, 0, sizeof(CVector) * mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector) * mNormalNum);
	//�X�L���E�F�C�g���J��Ԃ�
	for (size_t i = 0; i < mSkinWeights.size(); i++) {
		//�t���[���ԍ��擾
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//�t���[�������s��ɃI�t�Z�b�g�s�������
		CMatrix mSkinningMatrix = mSkinWeights[i]->mOffset * mat[frameIndex];
		//���_�����J��Ԃ�
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//���_�ԍ��擾
			int index = mSkinWeights[i]->mpIndex[j];
			//�d�ݎ擾
			float weight = mSkinWeights[i]->mpWeight[j];
			//���_�Ɩ@�����X�V����
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//�@���𐳋K������
	for (unsigned int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}

void CModelX::RenderShader(CMatrix* pCombinedMatrix)
{
	mShader.Render(this, pCombinedMatrix);
}

bool CModelX::IsLoaded()
{
	return mFrames.size() != 0;
}

void CMesh::CreateVertexBuffer() {
	//���b�V�����Ɉ��쐬����΂悢
	if (mMyVertexBufferId > 0)
		return;
	if (mVertexNum > 0) {
		//���_�C���f�b�N�X���g�킸�A�S�Ă̖ʃf�[�^���쐬
		CVertex* pmyVertex, * vec;
		//���_���v�Z
		unsigned int myVertexNum = mFaceNum * 3;
		//���_�������_�z��쐬
		pmyVertex = new CVertex[myVertexNum];
		vec = new CVertex[mVertexNum];
		for (unsigned int j = 0; j < mVertexNum; j++) {
			//���_���W�ݒ�
			vec[j].mPosition = mpVertex[j];
			//�e�N�X�`���}�b�s���O�ݒ�
			if (mpTextureCoords != NULL) {
				vec[j].mTextureCoords.Set(mpTextureCoords[j * 2]
					, mpTextureCoords[j * 2 + 1],0.0f);
			}
			vec[j].mBoneWeight[0] = 1.0f;
		}
		int wi = 0;
		//�X�L���E�F�C�g�ݒ�
		for (size_t k = 0; k < mSkinWeights.size(); k++) {
			for (int l = 0; l < mSkinWeights[k]->mIndexNum; l++) {
				int idx = mSkinWeights[k]->mpIndex[l];
				int m;
				for (m = 0; m < 3; m++) {
					//if (vec[idx].mBoneWeight[m] < mSkinWeights[k]->mpWeight[l])
					//{
					//	if (vec[idx].mBoneIndex[m + 1] != 0)
					//	{
					//		vec[idx].mBoneIndex[m] = vec[idx].mBoneIndex[m + 1];
					//		vec[idx].mBoneWeight[m] = vec[idx].mBoneWeight[m + 1];
					//	}
					//}
					//else {
					//	break;
					//}
					if (vec[idx].mBoneIndex[m] == 0) {
						vec[idx].mBoneIndex[m] =
							mSkinWeights[k]->mFrameIndex;
						vec[idx].mBoneWeight[m] =
							mSkinWeights[k]->mpWeight[l];
						break;
					}
				}
				//if (vec[idx].mBoneIndex[m] == 0 ||
				//	vec[idx].mBoneWeight[m] <= mSkinWeights[k]->mpWeight[l])
				//{
				//	vec[idx].mBoneIndex[m] =
				//		mSkinWeights[k]->mFrameIndex;
				//	vec[idx].mBoneWeight[m] =
				//		mSkinWeights[k]->mpWeight[l];
				//}
				//else
				//{
				//	if (m > 0)
				//	{
				//		vec[idx].mBoneIndex[m-1] =
				//			mSkinWeights[k]->mFrameIndex;
				//		vec[idx].mBoneWeight[m-1] =
				//			mSkinWeights[k]->mpWeight[l];
				//	}
				//}
			}
		}
		unsigned int k = 0;
		//�}�e���A���ԍ��̏����ɖʂ̒��_��ݒ�
		for (size_t i = 0; i < mMaterials.size(); i++) {
			unsigned int w = k;
			for (unsigned int j = 0; j < mMaterialIndexNum; j++) {
				if (mpMaterialIndex[j] == i) {
					//���_�z��ɐݒ肵�A�@����ݒ肷��
					pmyVertex[k] = vec[mpVertexIndex[j * 3]];
					pmyVertex[k++].mNormal = mpNormal[j * 3];
					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 1]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 1];
					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 2]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 2];
				}
			}
			//�}�e���A�����̒��_����ǉ�����
			mMaterialVertexCount.push_back(k - w);
		}
		//���_�o�b�t�@�̍쐬
		glGenBuffers(1, &mMyVertexBufferId);
		//���_�o�b�t�@���o�C���h
		glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBufferId);
		//�o�C���h�����o�b�t�@�Ƀf�[�^��]��
		glBufferData(GL_ARRAY_BUFFER
			, sizeof(CVertex) * myVertexNum
			, pmyVertex, GL_STATIC_DRAW);
		//�o�C���h����
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//�z����
		delete[] pmyVertex;
		delete[] vec;
		pmyVertex = NULL;
	}
}

CAnimationKey::CAnimationKey()
	: mTime(0.0f)
{
}
