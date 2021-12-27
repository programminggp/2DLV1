#include "CMaterial.h"
//memset�̃C���N���[�h
#include <string.h>
#include "glut.h"

void CMaterial::VertexNum(int num)
{
	mVertexNum = num;
}

int CMaterial::VertexNum()
{
	return mVertexNum;
}

float* CMaterial::Diffuse()
{
	return mDiffuse;
}

//�}�e���A���̖��O�̎擾
char* CMaterial::Name()
{
	return mName;
}

//�}�e���A���̖��O��ݒ肷��
//Name(�}�e���A���̖��O)
void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN - 1);
}

CTexture* CMaterial::Texture()
{
	return &mTexture;
}

//�f�t�H���g�R���X�g���N�^
CMaterial::CMaterial()
:mVertexNum(0)
,mpTextureFilename(nullptr)
, mPower(0.0f)
{
	//���O��0�Ŗ���
	memset(mName, 0, sizeof(mName));
	//0�Ŗ��߂�
	memset(mDiffuse, 0, sizeof(mDiffuse));
	memset(mSpecular, 0, sizeof(mSpecular));
	memset(mEmissive, 0, sizeof(mEmissive));
}

//�}�e���A����L���ɂ���
void CMaterial::Enabled() {
	//�g�U���̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//�e�N�X�`���L��
	if (mTexture.Id())
	{
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, mTexture.Id());
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

//�}�e���A���𖳌��ɂ���
void CMaterial::Disabled()
{
	//�e�N�X�`���L��
	if (mTexture.Id())
	{
		//�A���t�@�u�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`���𖳌��ɂ���
		glDisable(GL_TEXTURE_2D);
	}
}
float CMaterial::Power()
{
	return mPower;
}
float* CMaterial::Specular()
{
	return mSpecular;
}
float* CMaterial::Emissive()
{
	return mEmissive;
}
/*
Material�f�[�^�̓ǂݍ��݂Ɛݒ�
*/
CMaterial::CMaterial(CModelX* model)
	: CMaterial()
{
	//CModelX�Ƀ}�e���A����ǉ�����
	model->Materials().push_back(this);

	model->GetToken(); // { ? Name
	if (strcmp(model->Token(), "{") != 0) {
		//{�łȂ��Ƃ��̓}�e���A����
		strcpy(mName, model->Token());
		model->GetToken(); // {
	}

	mDiffuse[0] = model->GetFloatToken();
	mDiffuse[1] = model->GetFloatToken();
	mDiffuse[2] = model->GetFloatToken();
	mDiffuse[3] = model->GetFloatToken();

	mPower = model->GetFloatToken();
	mSpecular[0] = model->GetFloatToken();
	mSpecular[1] = model->GetFloatToken();
	mSpecular[2] = model->GetFloatToken();

	mEmissive[0] = model->GetFloatToken();
	mEmissive[1] = model->GetFloatToken();
	mEmissive[2] = model->GetFloatToken();

	model->GetToken(); // TextureFilename or }

	if (strcmp(model->Token(), "TextureFilename") == 0) {
		//�e�N�X�`������̏ꍇ�A�e�N�X�`���t�@�C�����擾
		model->GetToken(); // {
		model->GetToken(); // filename
		mpTextureFilename = new char[strlen(model->Token()) + 1];
		strcpy(mpTextureFilename, model->Token());
		//�e�N�X�`���t�@�C���̓ǂݍ���
		mTexture.Load(mpTextureFilename);
		model->GetToken(); // }
		model->GetToken(); // }
	}

	//#ifdef _DEBUG
	//	printf("%s\n", mName);
	//	printf("Diffuse:%f %f %f %f\n", mDiffuse[0], mDiffuse[1], mDiffuse[2], mDiffuse[3]);
	//	printf("Power:%f\n", mPower);
	//	printf("Specular:%f %f %f\n", mSpecular[0], mSpecular[1], mSpecular[2]);
	//	printf("Emissive:%f %f %f\n", mEmissive[0], mEmissive[1], mEmissive[2]);
	//#endif
}

CMaterial::~CMaterial() {
	if (mpTextureFilename) {
		delete[] mpTextureFilename;
	}
	mpTextureFilename = nullptr;
}