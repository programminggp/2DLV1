#include "glut.h"
#include <stdio.h>
#include <string.h>	//������֐��̃C���N���[�h

#include "CModelX.h"

#include "CMaterial.h"

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
	int size = ftell(fp);
	char *buf = mpPointer = new char[size + 1];
	fseek(fp, 0L, SEEK_SET);
	fread(buf, size, 1, fp);
	buf[size] = '\0';
	fclose(fp);

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();	//�P��̎擾
		//�P�ꂪFrame�̏ꍇ
		if (strcmp(mToken, "Frame") == 0) {
			//�t���[�����쐬����
			new CModelXFrame(this);
		}
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
	model->GetToken(); // frame name
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
			//�t���[�����쐬���A�q�t���[���̔z��ɒǉ�
			mChild.push_back(
				new CModelXFrame(model));
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0) {
			model->GetToken(); // {
			for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.mF); i++) {
				mTransformMatrix.mF[i] = model->GetFloatToken();
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
	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	printf("%s\n", mpName);
	for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.mF); i++) {
		printf("%10f", mTransformMatrix.mF[i]);
		if (i % 4 == 3)
			printf("\n");
	}
#endif
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
	//���_�����f�[�^����荞��
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].mX = model->GetFloatToken();
		mpVertex[i].mY = model->GetFloatToken();
		mpVertex[i].mZ = model->GetFloatToken();
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
				pNormal[i].mX = model->GetFloatToken();
				pNormal[i].mY = model->GetFloatToken();
				pNormal[i].mZ = model->GetFloatToken();
			}
			//�@����=�ʐ��~�R
			mNormalNum = model->GetIntToken() * 3; //FaceNum
			int ni;
			//���_���ɖ@���f�[�^��ݒ肷��
			mpNormal = new CVector[mNormalNum];
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
			}
			model->GetToken();	// } //End of MeshMaterialList
		}
		//SkinWeights�̂Ƃ�
		else if (strcmp(model->mToken, "SkinWeights") == 0) {
			//CSkinWeights�N���X�̃C���X�^���X���쐬���A�z��ɒǉ�
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		else {
			//�ȊO�̃m�[�h�͓ǂݔ�΂�
			model->SkipNode();
		}

	}

	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	printf("NormalNum:%d\n", mNormalNum);
	for (int i = 0; i < mNormalNum; i++) {
		printf("%10f", mpNormal[i].mX);
		printf("%10f", mpNormal[i].mY);
		printf("%10f\n", mpNormal[i].mZ);
	}
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

	/* ���_�f�[�^�C�@���f�[�^�̏ꏊ���w�肷�� */
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);

	/* ���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷�� */
	for (int i = 0; i < mFaceNum; i++) {
		//�}�e���A����K�p����
		mMaterial[mpMaterialIndex[i]]->Enabled();
		glDrawElements(GL_TRIANGLES, 3,
			GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
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
	for (int i = 0; i < mFrame.size(); i++) {
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
		mOffset.mF[i] = model->GetFloatToken();
	}
	model->GetToken();	// }

	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	printf("SkinWeights:%s\n", mpFrameName);
	for (int i = 0; i < mIndexNum; i++) {
		printf("%d", mpIndex[i]);
		printf("%10f\n", mpWeight[i]);
	}
	mOffset.Print();
#endif
}
/*
CAnimationSet
*/
CAnimationSet::CAnimationSet(CModelX* model)
	: mpName(0)
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
	//��v����t���[�������ꍇ��NULL��Ԃ�
	return NULL;
}
CAnimation::CAnimation(CModelX* model)
	: mpFrameName(0)
	, mFrameIndex(0)
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
	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or AnimationKey
		if (strchr(model->mToken, '}')) break;
		if (strcmp(model->mToken, "AnimationKey") == 0) {
			model->SkipNode();
		}
	}
#ifdef _DEBUG
	printf("AnimationSet:%s\n", mpFrameName);
#endif
}
