#ifndef CMODEL_H
#define CMODEL_H
//vector�̃C���N���[�h
#include <vector>
#include "CTriangle.h"
#include "CMatrix.h"
//CMaterial�̃C���N���[�h
#include "CMaterial.h"
/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
class CModel {
private:
	//���_�z��
	float *mpVertex; //���_���W
	float *mpNormal; //�@��
	float *mpTextureCoord; //�e�N�X�`���}�b�s���O
public:
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle> mTriangles;
	//�O�p�`�̉ϒ��z��
	std::vector<CMaterial> mMaterials;
	
	//�f�t�H���g�R���X�g���N�^
	CModel();
	//�f�X�g���N�^
	~CModel();
	//���f���t�@�C���̓���
	//Load(���f���t�@�C����, �}�e���A���t�@�C����)
	void Load(char *obj, char *mtl);
	//�`��
	void Render();
	//Render(�����s��)
	void Render(const CMatrix &m);
};

#endif
