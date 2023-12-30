#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include "CCharacter3.h"
/*
�r���{�[�h�N���X
��ɃJ�����̂ق��������l�p�`
*/
class CBillBoard : public CCharacter3 {
public:
	//CBillBoard(�ʒu�A���A�����A�D��x)
	CBillBoard(CVector pos, float w, float h, int priority);
	//�R���X�g���N�^
	CBillBoard();
	//CBillBoard(�ʒu�A���A����)
	CBillBoard(CVector pos, float w, float h);
	//�ʒu�Ƒ傫���̐ݒ�
	//Set(�ʒu�A���A����)
	void Set(CVector pos, float w, float h);
	//�X�V
	void Update();
	//�`��
	void Render();
	void Render(CMaterial* mpMaterial);
protected:
	//�O�p�`�Q��
	CTriangle mT[2];
	//�}�e���A��
	CMaterial mMaterial;
};

#endif
