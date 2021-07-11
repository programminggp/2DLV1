#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"
/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial {
public:
	//�}�e���A�����̒��_��
	int mVertexNum;
	//�e�N�X�`��
	CTexture mTexture;
	//�}�e���A����
	char mName[64];
	//�g�U���̐FRGBA
	float mDiffuse[4];
	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�e�N�X�`����ǂݍ���
	void LoadTexture(char *file);
	//�}�e���A���𖳌��ɂ���
	void Disabled();
};

#endif
