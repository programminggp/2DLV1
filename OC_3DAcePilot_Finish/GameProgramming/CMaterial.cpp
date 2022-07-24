#include "CMaterial.h"
//memset�̃C���N���[�h
#include <string.h>
#include "glut.h"

//�f�t�H���g�R���X�g���N�^
CMaterial::CMaterial()
: mpTexture(0), mVertexNum(0)
{
	//���O��0�Ŗ���
	memset(mName, 0, sizeof(mName));
	//0�Ŗ��߂�
	memset(mDiffuse, 0, sizeof(mDiffuse));
}
//�}�e���A����L���ɂ���
void CMaterial::Enabled() {
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//�g�U���̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//�e�N�X�`�����������A�߂�
	if (mpTexture == 0)
		return;
	//�e�N�X�`���L��
	if (mpTexture->mId) {
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, mpTexture->mId);
	}
}
//�}�e���A���𖳌��ɂ���
void CMaterial::Disabled() {
	//�A���t�@�u�����h�𖳌�
	glDisable(GL_BLEND);
	//�e�N�X�`�����������A�߂�
	if (mpTexture == 0)
		return;
	//�e�N�X�`���L��
	if (mpTexture->mId) {
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`���𖳌��ɂ���
		glDisable(GL_TEXTURE_2D);
	}
}
