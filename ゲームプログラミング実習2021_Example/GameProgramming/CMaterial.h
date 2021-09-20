#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"

#include "CModelX.h"

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
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	char* mpTextureFilename;

	CMaterial(CModelX* model);
	~CMaterial() {
		if (mpTextureFilename) {
			delete[] mpTextureFilename;
		}
		mpTextureFilename = nullptr;
	}

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
