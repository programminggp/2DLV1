#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"
/*
�O�p�`�N���X
*/
class CTriangle {
public:
	//���_���W�ݒ�
	//Vertex(���_1, ���_2, ���_3)
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2);
	//�@���ݒ�
	//Normal(�@���x�N�g��)
	void Normal(const CVector& n);
	//�`��
	void Render();
private:
	CVector mV[3]; //���_���W
	CVector mN; //�@��
};
#endif
