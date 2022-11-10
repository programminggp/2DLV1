#ifndef CMATRIX_H
#define CMATRIX_H
class CVector;
/*
�}�g���N�X�N���X
4�s4��̍s��f�[�^�������܂�
*/
class CMatrix {
	//friend CVector; //�t�����h�N���X�̐ݒ�

public:
	//�t�s��擾
	CMatrix Transpose();
	//Z���̃x�N�g���𓾂�
	CVector VectorZ() const;
	//X���̃x�N�g���𓾂�
	CVector VectorX() const;
	//Y���̃x�N�g���𓾂�
	CVector VectorY() const;
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix * float �̉��Z���ʂ�Ԃ�
	CMatrix operator*(const float& f) const;
	//+���Z�q�̃I�[�o�[���[�h
	//CMatrix1 + CMatrix2 �̉��Z���ʂ�Ԃ�
	CMatrix operator+(const CMatrix& m) const;
	//+=���Z�q�̃I�[�o�[���[�h
	//CMatrix1 += CMatrix2 �̉��Z���s��
	void operator+=(const CMatrix& m);

	//�N�I�[�^�j�I���ŉ�]�s���ݒ肷��
	CMatrix Quaternion(float x, float y, float z, float w);

	//�\���m�F�p
	//4�~4�̍s�����ʏo��
	void Print();
	//�f�t�H���g�R���X�g���N�^
	CMatrix();
	//�P�ʍs��̍쐬
	CMatrix Identity();
	//�s��̎擾
	float* M() const;
	//�s��l�̎擾
	//M(�s��, ��)
	float M(int row, int col) const;
	//�s��l�̐ݒ�
	//M(�s��, ��, �l)
	void M(int row, int col, float value);
	//�g��k���s��̍쐬
	//Scale(�{��X, �{��Y, �{��Z)
	CMatrix Scale(float sx, float sy, float sz);
	//��]�s��iY���j�̍쐬
	//RotateY(�p�x)
	CMatrix RotateY(float degree);
	//��]�s��iZ���j�̍쐬
	//RotateZ(�p�x)
	CMatrix RotateZ(float degree);
	//��]�s��iX���j�̍쐬
	//RotateX(�p�x)
	CMatrix RotateX(float degree);
	//�ړ��s��̍쐬
	//Translate(�ړ���X, �ړ���Y, �ړ���Z)
	CMatrix Translate(float mx, float my, float mz);
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix * CMatrix �̉��Z���ʂ�Ԃ�
	CMatrix operator*(const CMatrix &m);
	int Size();
private:
	//4�~4�̍s��f�[�^��ݒ�
	float mM[4][4];
};
#endif
