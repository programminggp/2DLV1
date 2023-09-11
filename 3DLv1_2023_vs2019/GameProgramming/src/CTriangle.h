#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"
#include "CMatrix.h"

/*
�O�p�`�N���X
*/
class CTriangle {
public:
	//UV�ݒ�
	void UV(const CVector& v0, const CVector& v1, const CVector& v2);
	//�}�e���A���ԍ��̎擾
	int MaterialIdx();
	//�}�e���A���ԍ��̐ݒ�
	//Material(�}�e���A���ԍ�)
	void MaterialIdx(int idx);
	//Normal(�@���x�N�g��1, �@���x�N�g��2, �@���x�N�g��3)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2);
	//���_���W�ݒ�
	//Vertex(���_1, ���_2, ���_3)
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2);
	//�@���ݒ�
	//Normal(�@���x�N�g��)
	void Normal(const CVector& n);
	//�`��
	void Render();
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
	//CVector* V();
	//CVector* N();
	//CVector* Uv();

	const CVector& V0() const;
	const CVector& V1() const;
	const CVector& V2() const;
	const CVector& N0() const;
	const CVector& N1() const;
	const CVector& N2() const;
	const CVector& U0() const;
	const CVector& U1() const;
	const CVector& U2() const;

private:
	CVector mUv[3]; //�e�N�X�`���}�b�s���O
	int mMaterialIdx; //�}�e���A���ԍ�
	CVector mV[3]; //���_���W
	CVector mN[3]; //�@��
};
#endif
