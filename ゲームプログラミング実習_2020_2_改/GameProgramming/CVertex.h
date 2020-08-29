#ifndef CVERTEX_H
#define CVERTEX_H
#include "CVector.h"

class CVertex
{
public:
	//���W
	CVector mPosition;
	//�@��
	CVector mNormal;
	//�e�N�X�`���}�b�v
	float mTexCoord[2];
	//�X�L���E�F�C�g
	float mBoneWeight[4];
	//�X�L���C���f�b�N�X
	float mBoneIndex[4];

	//�f�t�H���g�R���X�g���N�^
	CVertex();

};

#endif
