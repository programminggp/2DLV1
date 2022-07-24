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
	//�s��
	int mRows;
	//��
	int mCols;
	//1�R�}�̃t���[����
	int mFps;
	//�t���[���J�E���^
	int mFrame;

	//�R���X�g���N�^
	//CEffect(�ʒu, ��, ����, �e�N�X�`��, �s��, ��, �t���[����)
	CEffect(const CVector &pos, float w, float h, std::shared_ptr<CTexture> texture, int row=1, int col=1, int fps=1);
	//�X�V
	void Update();
};

#endif
