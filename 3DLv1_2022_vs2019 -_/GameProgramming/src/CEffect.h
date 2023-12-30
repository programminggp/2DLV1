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
	//�R���X�g���N�^
	//CEffect(�ʒu�A���A�����A�e�N�X�`�����A�s���A�񐔁A�P�R�}������̃t���[����)�@�s���A�񐔁A�t���[�����̓f�t�H���g�����ŌĂяo�����ȗ��\
	CEffect(const CVector& pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
	//�X�V
	void Update();
	//�`��
	void Render();
private:
	//�s��
	int mRows;
	//��
	int mCols;
	//�P�R�}�̃t���[����
	int mFps;
	//�t���[���J�E���^
	int mFrame;
	//�}�e���A��
	static CMaterial sMaterial;
};
#endif
