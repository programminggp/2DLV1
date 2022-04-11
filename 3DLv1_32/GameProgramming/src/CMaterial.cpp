#include "CMaterial.h"
//memset,strncpy�̃C���N���[�h
#include <string.h>
#include "glut.h"

//�f�t�H���g�R���X�g���N�^
CMaterial::CMaterial()
:mVertexNum(0)
{
	//���O��0�Ŗ���
	memset(mName, 0, sizeof(mName));
	//0�Ŗ��߂�
	memset(mDiffuse, 0, sizeof(mDiffuse));
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
//�}�e���A���̖��O���擾
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
//mDiffuse�z��̎擾
float* CMaterial::Diffuse()
{
	return mDiffuse;
}
//�}�e���A���𖳌��ɂ���
void CMaterial::Disabled() {
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
CTexture* CMaterial::Texture()
{
	return&mTexture;
}
void CMaterial::VertexNum(int num) 
{
	CMaterial::mVertexNum = num;
}

int CMaterial::VertexNum()
{
	return CMaterial::mVertexNum;
}
