#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"
#define MATERIAL_NAME_LEN 64 //���O�̒���
#include "CModelX.h"

/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial {
	friend CMyShader;
public:
	CMaterial(CModelX* model);
	~CMaterial();
	//�e�N�X�`���̎擾
	CTexture* Texture();
	//�}�e���A���𖳌��ɂ���
	void Disabled();
	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�}�e���A���̖��O�̎擾
	char* Name();
	//�}�e���A���̖��O��ݒ肷��
	//Name(�}�e���A���̖��O)
	void Name(char* name);
	//mDiffuse�z��̎擾
	float* Diffuse();
	//���_���̐ݒ�
	//VertexNum(���_��)
	void VertexNum(int num);
	//���_���̎擾
	int VertexNum();
	void Specular(float r, float g, float b)
	{
		mSpecular[0] = r;
		mSpecular[1] = g;
		mSpecular[2] = b;
	}

	void Emissive(float r, float g, float b)
	{
		mEmissive[0] = r;
		mEmissive[1] = g;
		mEmissive[2] = b;
	}

	void Power(float p)
	{
		mPower = p;
	}

private:
	//�}�e���A�����̒��_��
	int mVertexNum;
	//�e�N�X�`��
	CTexture mTexture;
	//�}�e���A����
	char mName[MATERIAL_NAME_LEN + 1];
	//�g�U���̐FRGBA
	float mDiffuse[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	char* mpTextureFilename;
};

#endif
