#ifndef CBILLBOARD_H
#define CBILLBOARD_H

#include "CVector3.h"
#include "CVector4.h"
#include "CTexture.h"
#include "CMatrix44.h"
#include "CTask.h"

//�r���{�[�h�N���X
class CBillBoard : public CTask {
protected:
	//�s��
	CMatrix44 mMatrix;
	//�ʒu���W
	CVector3 mPosition;
	//�g��k���l
	CVector3 mScale;
	//�\���F
	CVector4 mColor;
	//�e�N�X�`��
	CTexture *mpTexture;
	//�e�N�X�`���}�b�s���O
	CVector2 mUv[4];
public:
	//�R���X�g���N�^
	CBillBoard(){}
	CBillBoard(const CVector3 &position, const CVector3 &scale);
	//�e�N�X�`���̐ݒ�
	void SetTexture(CTexture *t);
	//�`�揈��
	void Render();
};
/*
�q�b�g�G�t�F�N�g�N���X
*/
class CEffectHit : public CBillBoard {
public:
	//�e�N�X�`���̐錾
	static CTexture mTexEffectHit;
	//�G�t�F�N�g�̎���
	int mLife;
	CEffectHit(){}
	CEffectHit(const CVector3 &position, const CVector3 &scale);

	void Update();
	void Render();
};

class CEffectHit2 : public CBillBoard {
public:
	//�e�N�X�`���̐錾
	static CTexture mTexEffectHit;
	//�G�t�F�N�g�̎���
	int mLife;
	int mRows, mCols;
	CEffectHit2(){}
	CEffectHit2(const CVector3 &position, const CVector3 &scale);
	CEffectHit2(const CVector3 &position, const CVector3 &scale, int rows, int cols);

	void Update();
	void Render();
};

class CEffectHit3 : public CBillBoard {
public:
	//�e�N�X�`���̐錾
	static CTexture mTexEffectHit;
	//�G�t�F�N�g�̎���
	int mLife;
	int mRows, mCols;
	CEffectHit3(){}
	CEffectHit3(const CVector3 &position, const CVector3 &scale);
	CEffectHit3(const CVector3 &position, const CVector3 &scale, int rows, int cols);

	void Update();
	void Render();
};


#endif
