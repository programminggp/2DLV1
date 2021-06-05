#ifndef CVERTEX_H
#define CVERTEX_H

#include "CVector3.h"

/*
���_�o�b�t�@�f�[�^�N���X
���_���Ƀf�[�^���܂Ƃ߂܂�
*/
class CVertex {
public:
	//�ʒu
	CVector3 mPosition;
	//�@��
	CVector3 mNormal;
	//�e�N�X�`���}�b�s���O
	CVector2 mTextureCoords;
	//�X�L���E�F�C�g
	float mBoneWeight[4];
	//�X�L���C���f�b�N�X
	float mBoneIndex[4];

	CVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};

#endif
