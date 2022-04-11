#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64 //���O�̒���

#include"CMaterial.h"
#include "CTexture.h"


/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial{
public:
	
	//�e�N�X�`��
	CTexture mTexture;
	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�}�e���A���̖��O���擾
	char* Name();
	//�}�e���A���̖��O��ݒ肷��
	//Name(�}�e���A���̖��O)
	void Name(char* name);
	//mDiffuse�z��̎擾
	float* Diffuse();
	//�}�e���A���𖳌��ɂ���
	void Disabled();
	//�e�N�X�`���̎擾
	CTexture* Texture();
	//���_���̐ݒ�
	//VertexNum(���_��)
	void VertexNum(int num);
	//���_���̎擾
	int VertexNum();

private:
	//�}�e���A����
	char mName[MATERIAL_NAME_LEN];
	//�g�U���̐FRGBA
	float mDiffuse[4];
	//�}�e���A�����̒��_��
	int mVertexNum;
	
};

#endif 

