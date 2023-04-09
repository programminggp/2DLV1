#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"
#include"CModelX.h"
#include"CMyShader.h"
#define MATERIAL_NAME_LEN 64
class CMyShader;
/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial {
	friend CMyShader;
public:
//	void Diffuse(float r, float g, float b, float a);
	//���_���̐ݒ�
	//VertexNum(���_��)
	void VertexNum(int num);
	//���_���̎擾
	int VertexNum();
	//mDiffuse�z��̎擾
	float* Diffuse();
	//�}�e���A���̖��O�̎擾
	char* Name();
	//�}�e���A���̖��O��ݒ肷��
	//Name(�}�e���A���̖��O)
	void Name(char* name);
	//�e�N�X�`���̎擾
	CTexture* Texture();
	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�e�N�X�`����ǂݍ���
//	void LoadTexture(char *file);
	//�}�e���A���𖳌��ɂ���
	void Disabled();
	CMaterial(CModelX* model);
	~CMaterial();
private:
	//�}�e���A�����̒��_��
	int mVertexNum;
	//�e�N�X�`��
	CTexture mTexture;
	//�}�e���A����
	char mName[MATERIAL_NAME_LEN];
	//�g�U���̐FRGBA
	float mDiffuse[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	char* mpTextureFilename;
};

#endif