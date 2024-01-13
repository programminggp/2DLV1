#include "CMaterial.h"
//memset,strncpy�̃C���N���[�h
#include <string.h>
//#define FREEGLUT_STATIC
#include "gl/freeglut.h"
/*
* strncpy(char* str1, const char* str2, int len)
* �R�s�[��str1�ɃR�s�[��str2�̕�����len�������܂ŃR�s�[����
*/
char* strncpy(char* str1, const char* str2, int len)
{
	int i = 0;
	//i��len��菬�����A���A�R�s�[�����I���łȂ��ԌJ��Ԃ�
	while (i < len && *str2 != '\0')
	{
		*(str1 + i) = *str2; //�R�s�[��ɃR�s�[������
		str2++; //�R�s�[��������
		i++;
	}
	str1[i] = '\0'; //�R�s�[��̕�����ɏI���
	return str1; //�R�s�[��̐擪�A�h���X��ԋp
}

CMaterial::CMaterial(CModelX* model)
	: mpTextureFilename(nullptr)
{
	//CModelX�Ƀ}�e���A����ǉ�����
	model->Material().push_back(this);

	model->GetToken(); // { ? Name
	if (strcmp(model->Token(), "{") != 0) {
		//{�łȂ��Ƃ��̓}�e���A����
		strcpy(mName, model->Token());
		model->GetToken(); // {
	}

	mDiffuse[0] = atof(model->GetToken());
	mDiffuse[1] = atof(model->GetToken());
	mDiffuse[2] = atof(model->GetToken());
	mDiffuse[3] = atof(model->GetToken());

	mPower = atof(model->GetToken());
	mSpecular[0] = atof(model->GetToken());
	mSpecular[1] = atof(model->GetToken());
	mSpecular[2] = atof(model->GetToken());

	mEmissive[0] = atof(model->GetToken());
	mEmissive[1] = atof(model->GetToken());
	mEmissive[2] = atof(model->GetToken());

	model->GetToken(); // TextureFilename or }

	if (strcmp(model->Token(), "TextureFilename") == 0) {
		//�e�N�X�`������̏ꍇ�A�e�N�X�`���t�@�C�����擾
		model->GetToken(); // {
		model->GetToken(); // filename
		mpTextureFilename =
			new char[strlen(model->Token()) + 1];
		strcpy(mpTextureFilename, model->Token());

		//�e�N�X�`���t�@�C���̓ǂݍ���
		mTexture.Load(mpTextureFilename);

		model->GetToken(); // }
		model->GetToken(); // }
	}
}


CTexture* CMaterial::Texture()
{
	return &mTexture;
}

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

CMaterial::~CMaterial() {
	if (mpTextureFilename) {
		delete[] mpTextureFilename;
	}
	mpTextureFilename = nullptr;
}

//�f�t�H���g�R���X�g���N�^
CMaterial::CMaterial()
	:mVertexNum(0)
	,mpTextureFilename(nullptr)
{
	//���O��0�Ŗ���
	memset(mName, 0, sizeof(mName));

	//�g�U���̏����l��(1, 1, 1, 1)
	int count = sizeof(mDiffuse) / sizeof(mDiffuse[0]);
	for (int i = 0; i < count; i++)
	{
		mDiffuse[i] = 1.0f;
	}
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
//�}�e���A���̖��O�̎擾
char* CMaterial::Name()
{
	return mName;
}
// �}�e���A���̖��O��ݒ肷��
// Name(�}�e���A���̖��O)
void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN);
}
//mDiffuse�z��̎擾
float* CMaterial::Diffuse()
{
	return mDiffuse;
}

void CMaterial::VertexNum(int num)
{
	mVertexNum = num;
}

int CMaterial::VertexNum()
{
	return mVertexNum;
}
