#ifndef CMODEL_H
#define CMODEL_H
/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
//vector�̃C���N���[�h
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"
#include "CMyShader.h"

class CModel {
	friend CMyShader;
public:
	GLuint mMyVertexBufferId;
	const std::vector<CTriangle>& Triangles() const;
	//���f���t�@�C���̓���
	//Load(���f���t�@�C�����A�}�e���A���t�@�C����)
	void Load(char* obj, char* mtl);
	//�`��
	void Render();
	~CModel();
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
private:
	CMyShader mShader;
	//���_�̔z��
	CVertex* mpVertexes;
	void CreateVertexBuiffer();
	//�}�e���A���|�C���^�̉ϒ��z��
	std::vector<CMaterial*>mpMaterials;
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle>mTriangles;
};

#endif
