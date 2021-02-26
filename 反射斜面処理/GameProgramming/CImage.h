#ifndef CIMAGE_H
#define CIMAGE_H
#include "CBillBoard.h"
/*
CImage
�|���S���Ƀe�N�X�`����\���ĕ`��
*/
class CImage : public CBillBoard {
public:
	//CImage(�e�N�X�`��,�ʒu,��],�g�k)
	CImage(std::shared_ptr<CTexture> texture, const CVector &pos, const CVector &rot, const CVector &sca);
	//SetUv(�����W,�E���W,����W,�����W)
	//�g�p����e�N�X�`���̍��W���w�肷��
	//���_����
	void SetUv(float left, float right, float bottom, float top);
	//Update
	//�s��̍X�V
	void Update();
};

#endif
