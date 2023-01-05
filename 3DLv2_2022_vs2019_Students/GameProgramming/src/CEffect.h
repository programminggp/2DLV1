#ifndef CEFFECT_H
#define CEFFECT_H
//�r���{�[�h�N���X�̃C���N���[�h
#include "CBillBoard.h"
/*
�G�t�F�N�g�N���X
�e�N�X�`���̃A�j���[�V����
*/
class CEffect : public CBillBoard {
public:
	enum EType {
		EANIMATION,
		EFADE,
	};
	void Animation();
	void Fade();
	//�R���X�g���N�^
	//CEffect(�ʒu, ��, ����, �e�N�X�`����, �s��, ��, 1�R�}������̃t���[����)�@�s���A�񐔁A�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	CEffect(const CVector &pos, float w, float h, char *texture, int row = 1, int col = 1, int fps = 1);
	//CEffect(�ʒu, ��, ����, �s��, ��, 1�R�}������̃t���[����)�@�s���A�񐔁A�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	CEffect(const CVector& pos, float w, float h, int row = 1, int col = 1, int fps = 1, EType type = EANIMATION, int frame = 0);
	//�X�V
	void Update();
	//�`��
	void Render();
	void Render(CMaterial* material);
private:
	int mFadeCount;
	EType mType;
	//�s��
	int mRows;
	//��
	int mCols;
	//1�R�}�̃t���[����
	int mFps;
	//�t���[���J�E���^
	int mFrame;
	//�}�e���A��
	static CMaterial sMaterial;
};


class CEffectDarkness17 : public CEffect
{
public:
	//�R���X�g���N�^(�ʒu, ��, ����, �s��, ��, 1�R�}������̃t���[����)�@�s���A�񐔁A�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	CEffectDarkness17(const CVector& pos, float w, float h, int row = 1, int col = 1, int fps = 1);

	void Render();
private:
	static CMaterial sMaterial;
};

class CEffectFire7 : public CEffect
{
public:
	//�R���X�g���N�^(�ʒu, ��, ����, �s��, ��, 1�R�}������̃t���[����)�@�s���A�񐔁A�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	CEffectFire7(const CVector& pos, float w, float h, int row = 1, int col = 1, int fps = 1, EType type = EANIMATION, int frame = 0);

	void Render();
private:
	static CMaterial sMaterial;
};

#endif

