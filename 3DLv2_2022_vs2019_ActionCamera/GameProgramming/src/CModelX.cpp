#include "glew.h"
#include <stdio.h>
#include <string.h>
#include "CModelX.h"
#include "glut.h"
#include "CVector.h"
#include "CMaterial.h"
#include "CVertex.h"

CModelX::CModelX()
	: mpPointer(nullptr)
	, mpSkinningMatrix(nullptr)
{
	//mToken��������
	memset(mToken, 0, sizeof(mToken));
}

void CModelX::Load(char* file) {
	//
	//�t�@�C���T�C�Y���擾����
	//
	FILE* fp;	//�t�@�C���|�C���^�ϐ��̍쐬
	fp = fopen(file, "rb");	//�t�@�C�����I�[�v������
	if (fp == NULL) {	//�G���[�`�F�b�N
		printf("fopen error:%s��n", file);
		return;
	}

	//�t�@�C���̍Ō�ֈړ�
	fseek(fp, 0L, SEEK_END);
	//�t�@�C���T�C�Y�̎擾
	int size = ftell(fp);
	//�t�@�C���T�C�Y+1�o�C�g���̗̈���m��
	char* buf = mpPointer = new char[size + 1];
	//
	//�t�@�C������3D���f���̃f�[�^��ǂݍ���
	//
	//�t�@�C���̐擪�ֈړ�
	fseek(fp, 0L, SEEK_SET);
	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
	fread(buf, size, 1, fp);
	//�Ō��\0��ݒ肷��i������̏I�[�j
	buf[size] = '\0';
	fclose(fp);	//�t�@�C�����N���[�Y����

	//�_�~�[���[�g�t���[���̍쐬
	CModelXFrame* p = new CModelXFrame();
	//���O�Ȃ�
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	//�t���[���z��ɒǉ�
	mFrame.push_back(p);

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
	SAFE_DELETE_ARRAY(buf);	//�m�ۂ����̈���J������
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	SetSkinWeightFrameIndex();

	//���_�o�b�t�@�̍쐬
	for (size_t i = 0; i < mFrame.size(); i++) {
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			mFrame[i]->mMesh.CreateVertexBuffer();
		}
	}
	//�X�L���}�g���b�N�X�̃G���A�쐬
	mpSkinningMatrix = new CMatrix[mFrame.size()];
	//�V�F�[�_�[�ǂݍ���
	mShader.Load("res\\skinmesh.vert", "res\\skinmesh.flag");
}

void CModelX::GetToken()
{
	char* p = mpPointer;
	char* q = mToken;
	/*
	strchr(������, ����)
	������ɕ������܂܂�Ă���΁A�������������ւ̃|�C���^��Ԃ�
	������Ȃ�������NULL��Ԃ�
	*/
	//��( )�^�u(\t)���s(\r)(\n)�C�G�h�ȊO�̕����ɂȂ�܂œǂݔ�΂�
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

CModelX::~CModelX()
{
	if (mFrame.size() > 0)
	{
		delete mFrame[0];
	}
	for (size_t i = 0; i < mAnimationSet.size(); i++)
	{
		delete mAnimationSet[i];
	}
	//�}�e���A���̉��
	for (size_t i = 0; i < mMaterial.size(); i++) {
		delete mMaterial[i];
	}
	SAFE_DELETE_ARRAY(mpSkinningMatrix);
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

std::vector<CMaterial*>& CModelX::Material()
{
	return mMaterial;
}

float CModelX::GetFloatToken()
{
	GetToken();
	//atof
	//�������float�^�֕ϊ�
	return atof(mToken);
}

int CModelX::GetIntToken()
{
	GetToken();
	return atoi(mToken);
}

char* CModelX::Token()
{
	return mToken;
}

std::vector<CModelXFrame*>& CModelX::Frames()
{
	return mFrame;
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
	mIndex = model->mFrame.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrame.push_back(this);
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
			model->GetToken(); // Frame
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
	mVertexNum = model->GetIntToken();
	//���_�����G���A�m��
	mpVertex = new CVector[mVertexNum];
	mpAnimateVertex = new CVector[mVertexNum];
	//���_�����f�[�^����荞��
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].X(model->GetFloatToken());
		mpVertex[i].Y(model->GetFloatToken());
		mpVertex[i].Z(model->GetFloatToken());
	}
	mFaceNum = model->GetIntToken();	//�ʐ��ǂݍ���
//���_����1�ʂ�3���_
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3) {
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
			for (int i = 0; i < mNormalNum; i++) {
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
			for (int i = 0; i < mNormalNum; i += 3) {
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
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++) {
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//�}�e���A���f�[�^�̍쐬
			for (int i = 0; i < mMaterialNum; i++) {
				model->GetToken();	// Material
				if (strcmp(model->mToken, "Material") == 0) {
					mMaterial.push_back(new CMaterial(model));
				}
				else {
					// {  ���o
					model->GetToken();	//MaterialName
					mMaterial.push_back(
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

#ifdef _DEBUG
	/*printf("NormalNum:%d\n", mNormalNum);
	for (int i = 0; i < mNormalNum; i++) {
		printf("%10f%10f%10f\n",
			mpNormal[i].X(),
			mpNormal[i].Y(),
			mpNormal[i].Z());
	}*/
#endif
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
	for (int i = 0; i < mFaceNum; i++) {
		//�}�e���A����K�p����
		mMaterial[mpMaterialIndex[i]]->Enabled();
		/* ���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷�� */
		glDrawElements(GL_TRIANGLES, 3,
			GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		mMaterial[mpMaterialIndex[i]]->Disabled();
	}

	/* ���_�f�[�^�C�@���f�[�^�̔z��𖳌��ɂ��� */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
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
	for (size_t i = 0; i < mFrame.size(); i++) {
		mFrame[i]->Render();
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
	mpFrameName = new char[strlen(model->Token()) + 1];
	strcpy(mpFrameName, model->Token());
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

#ifdef _DEBUG
	/*printf("SkinWeights:%s\n", mpFrameName);
	for (int i = 0; i < mIndexNum; i++)
	{
		printf("%3d %10f\n", mpIndex[i], mpWeight[i]);
	}
	mOffset.Print();*/
#endif
}

CAnimationSet::CAnimationSet()
	: mTime(0.0f)
	, mWeight(0.0f)
	, mMaxTime(0.0f)
	, mpName(nullptr)
{
}

float CAnimationSet::Time()
{
	return mTime;
}

float CAnimationSet::MaxTime()
{
	return mMaxTime;
}

void CAnimationSet::Time(float time)
{
	mTime = time;
}

void CAnimationSet::Weight(float weight)
{
	mWeight = weight;
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
	model->mAnimationSet.push_back(this);
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

#ifdef _DEBUG
//	printf("AnimationSet:%s\n", mpName);
#endif
}

std::vector<CAnimationSet*>& CModelX::AnimationSet()
{
	return mAnimationSet;
}
/*
 FindFrame
 �t���[�����ɊY������t���[���̃A�h���X��Ԃ�
*/
CModelXFrame* CModelX::FindFrame(char* name) {
	//�C�e���[�^�̍쐬
	std::vector<CModelXFrame*>::iterator itr;
	//�擪����Ō�܂ŌJ��Ԃ�
	for (itr = mFrame.begin(); itr != mFrame.end(); itr++) {
		//���O����v�������H
		if (strcmp(name, (*itr)->mpName) == 0) {
			//��v�����炻�̃A�h���X��Ԃ�
			return *itr;
		}
	}
	//��v����t���[���������ꍇ��nullptr��Ԃ�
	return nullptr;
}

//std::vector<CModelXFrame*>& CModelX::Frames()
//{
//	return mFrame;
//}

CAnimation::CAnimation()
	: mKeyNum(0)
	, mpKey(nullptr)
	, mpFrameName(nullptr)
	, mFrameIndex(0)
{
}

CAnimation::CAnimation(CModelX* model)
	: mpFrameName(nullptr)
	, mFrameIndex(0)
	, mKeyNum(0)
	, mpKey(nullptr)
{
	model->GetToken(); // { or Animation Name
	if (strchr(model->Token(), '{')) {
		model->GetToken(); // {
	}
	else {
		model->GetToken(); // {
		model->GetToken(); // {
	}

	model->GetToken(); //FrameName
	mpFrameName = new char[strlen(model->Token()) + 1];
	strcpy(mpFrameName, model->Token());
	mFrameIndex =
		model->FindFrame(model->Token())->mIndex;
	model->GetToken(); // }

	//�L�[�̔z���ۑ����Ă����z��
	CMatrix* key[4] = { 0, 0, 0, 0 };
	//���Ԃ̔z���ۑ����Ă����z��
	float* time[4] = { 0, 0, 0, 0 };

	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or AnimationKey
		if (strchr(model->Token(), '}')) break;
		if (strcmp(model->Token(), "AnimationKey") == 0) {
			model->GetToken(); // {
			//�f�[�^�̃^�C�v�擾
			int type = model->GetIntToken();
			//���Ԑ��擾
			mKeyNum = model->GetIntToken();
			switch (type) {
			case 0: // Rotation Quaternion
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
					//�N�H�[�^�j�I�������]�s��ɕϊ�
					key[type][i].Quaternion(x, y, z, w);
				}
				break;
			case 1: //�g��E�k���̍s��쐬
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].Scale(x, y, z);
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

#ifdef _DEBUG
//	printf("Animation:%s\n", mpFrameName);
//	mpKey[0].mMatrix.Print();
#endif
}
/*
AnimateFrame
�t���[���̕ϊ��s����A�j���[�V�����f�[�^�ōX�V����
*/
void CModelX::AnimateFrame() {
	//�A�j���[�V�����œK�p�����t���[����
	//�ϊ��s����[���N���A����
	for (size_t i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0) continue;
		//�t���[�����iAnimation���j�J��Ԃ�
		for (size_t j = 0; j < anim->mAnimation.size(); j++) {
			CAnimation* animation = anim->mAnimation[j];
			//�Y������t���[���̕ϊ��s����[���N���A����
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix));
		}
	}
	//�A�j���[�V�����ɊY������t���[���̕ϊ��s���
	//�A�j���[�V�����̃f�[�^�Őݒ肷��
	for (size_t i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0) continue;
		//�t���[�����iAnimation���j�J��Ԃ�
		for (size_t j = 0; j < anim->mAnimation.size(); j++) {
			//�t���[�����擾����
			CAnimation* animation = anim->mAnimation[j];
			CModelXFrame* frame = mFrame[animation->mFrameIndex];
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
#ifdef _DEBUG
//			printf("%s\n",frame->mpName);
//			frame->mTransformMatrix.Print();
#endif
		}
	}
	//for (int i = 0; i < mFrame.size(); i++)
	//{
	//	printf("Frame:%s\n", mFrame[i]->mpName);
	//	mFrame[i]->mTransformMatrix.Print();
	//}
}
const CMatrix& CModelXFrame::CombinedMatrix()
{
	return mCombinedMatrix;
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
#ifdef _DEBUG
//	printf("Frame:%s\n", mpName);
//	mCombinedMatrix.Print();
#endif
}

/*
SetSkinWeightFrameIndex
�X�L���E�F�C�g�Ƀt���[���ԍ���ݒ肷��
*/
void CModelX::SetSkinWeightFrameIndex() {
	//�t���[�������J��Ԃ�
	for (size_t i = 0; i < mFrame.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//�X�L���E�F�C�g���J��Ԃ�
			for (size_t j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++) {
				//�t���[�����̃t���[�����擾����
				CModelXFrame* frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//�t���[���ԍ���ݒ肷��
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
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
		CMatrix mSkinningMatrix = mSkinWeights[i]->mOffset * model->mFrame[frameIndex]->CombinedMatrix();
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
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}
/*
AnimateVertex
���_�ɃA�j���[�V������K�p����
*/
void CModelX::AnimateVertex() {
	//�t���[�������J��Ԃ�
	for (size_t i = 0; i < mFrame.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//���_���A�j���[�V�����ōX�V����
			mFrame[i]->mMesh.AnimateVertex(this);
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
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
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
	CAnimationSet* anim = mAnimationSet[idx];//��������A�j���[�V�����Z�b�g���m��
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
		}//�A�j���[�V�����L�[�̃R�s�[
		as->mAnimation.push_back(animation);//�A�j���[�V�����̒ǉ�
	}
	mAnimationSet.push_back(as);//�A�j���[�V�����Z�b�g�̒ǉ�
}

void CModelX::AnimateVertex(CMatrix* mat) {
	//�t���[�������J��Ԃ�
	for (size_t i = 0; i < mFrame.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//���_���A�j���[�V�����ōX�V����
			mFrame[i]->
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
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}

void CModelX::RenderShader(
	CMatrix* pCombinedMatrix) {
	mShader.Render(this, pCombinedMatrix);
}

void CMesh::CreateVertexBuffer() {
	//���b�V�����Ɉ��쐬����΂悢
	if (mMyVertexBufferId > 0)
		return;
	if (mVertexNum > 0) {
		//���_�C���f�b�N�X���g�킸�A�S�Ă̖ʃf�[�^���쐬
		CVertex* pmyVertex, * vec;
		//���_���v�Z
		int myVertexNum = mFaceNum * 3;
		//���_�������_�z��쐬
		pmyVertex = new CVertex[myVertexNum];
		vec = new CVertex[mVertexNum];
		for (int j = 0; j < mVertexNum; j++) {
			//���_���W�ݒ�
			vec[j].mPosition = mpVertex[j];
			//�e�N�X�`���}�b�s���O�ݒ�
			if (mpTextureCoords != NULL) {
				vec[j].mTextureCoords.X(mpTextureCoords[j * 2]);
				vec[j].mTextureCoords.Y(mpTextureCoords[j * 2 + 1]);
			}
			vec[j].mBoneWeight[0] = 1.0f;
		}
		int wi = 0;
		//�X�L���E�F�C�g�ݒ�
		for (size_t k = 0; k < mSkinWeights.size(); k++) {
			for (int l = 0; l < mSkinWeights[k]->mIndexNum; l++) {
				int idx = mSkinWeights[k]->mpIndex[l];
				for (int m = 0; m < 4; m++) {
					if (vec[idx].mBoneIndex[m] == 0) {
						vec[idx].mBoneIndex[m] =
							mSkinWeights[k]->mFrameIndex;
						vec[idx].mBoneWeight[m] =
							mSkinWeights[k]->mpWeight[l];
						break;
					}
				}
			}
		}
		int k = 0;
		//�}�e���A���ԍ��̏����ɖʂ̒��_��ݒ�
		for (size_t i = 0; i < mMaterial.size(); i++) {
			int w = k;
			for (int j = 0; j < mMaterialIndexNum; j++) {
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
		pmyVertex = nullptr;
	}
}


