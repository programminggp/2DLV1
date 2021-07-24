#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"

#define MATERIAL_NAME_LEN 64

/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial {
private:
	//�}�e���A�����̒��_��
	int mVertexNum;
	//�e�N�X�`��
	CTexture mTexture;
	//�}�e���A����
	char mName[MATERIAL_NAME_LEN];
	//�g�U���̐FRGBA
	float mDiffuse[4];
public:
	void Diffuse(float r, float g, float b, float a);
	void VertexNum(int num);
	int VertexNum();
	//mDiffuse�z��̎擾
	float* Diffuse();
	//�}�e���A���̖��O�̎擾
	char* Name();
	//�}�e���A���̖��O��ݒ肷��
	//Name(�}�e���A���̖��O)
	void Name(char* name);
	CTexture& Texture();
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