#include "CMaterial.h"

#include "string.h"

/*
Material�f�[�^�̓ǂݍ��݂Ɛݒ�
*/
CMaterial::CMaterial()
: mpName(0)
, mpTextureFilename(0)
, mTextureId(0)
{
	memset(this, 0, sizeof(CMaterial));
}

/*
SetMaterial
�}�e���A����K�p����
*/
void CMaterial::SetMaterial() {
	glMaterialfv(GL_FRONT, GL_EMISSION, mEmissive);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mPower);
	//�e�N�X�`�����L��ꍇ
	if (mTextureId > 0) {
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		/* �e�N�X�`�����j�b�g0�ɐ؂�ւ��� */
//		glActiveTexture(GL_TEXTURE0);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, mTextureId);
		//�e�N�X�`���}�b�s���O�̃f�[�^��L���ɂ���
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
/*
UnSetMaterial
�e�N�X�`���}�b�s���O�𖳌��ɂ���
*/
void CMaterial::UnSetMaterial() {
	//�e�N�X�`�����L�鎞
	if (mTextureId > 0) {
		/* �e�N�X�`�����j�b�g0�ɐ؂�ւ��� */
//		glActiveTexture(GL_TEXTURE0);
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`���𖳌��ɂ���
//		glDisable(GL_TEXTURE_2D);
		//�e�N�X�`���}�b�s���O�̃f�[�^�𖳌��ɂ���
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
