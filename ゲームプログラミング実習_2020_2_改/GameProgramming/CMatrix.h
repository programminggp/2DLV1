#ifndef CMATRIX_H
#define CMATRIX_H
/*
�}�g���N�X�N���X
4�s4��̍s��f�[�^�������܂�
*/
class CMatrix {
public:
	union {
		//4�~4�̍s��f�[�^��ݒ�
		float mM[4][4];
		//1�����z��Ƃ��Ďg��
		float mF[16];
	};
	//�\���m�F�p
	//4�~4�̍s�����ʏo��
	void Print();
	//�f�t�H���g�R���X�g���N�^
	CMatrix();
	//�P�ʍs��̍쐬
	CMatrix Identity();
	//��]�s��iY���j�̍쐬
	//RotateY(�p�x)
	CMatrix RotateY(float degree);
	//��]�s��iX���j�̍쐬
	//RotateX(�p�x)
	CMatrix RotateX(float degree);
	//��]�s��iZ���j�̍쐬
	//RotateZ(�p�x)
	CMatrix RotateZ(float degree);
	//���s�ړ��s��̍쐬
	//Translate(�ړ���X, �ړ���Y, �ړ���Z)
	CMatrix Translate(float x, float y, float z);
	//�g��k���s��̍쐬
	//Scale(�{��X, �{��Y, �{��Z)
	CMatrix Scale(float x, float y, float z);
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix * CMatrix �̉��Z���ʂ�Ԃ�
	CMatrix operator*(const CMatrix &m);
	//�N�I�[�^�j�I�������]�s���ݒ肷��
	CMatrix SetQuaternion(float x, float y, float z, float w);
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix * float �̉��Z���ʂ�Ԃ�
	CMatrix operator*(const float &f);
	//+=���Z�q�̃I�[�o�[���[�h
	//CMatrix += CMatrix �̉��Z���s��
	void operator+=(const CMatrix &m);
	//+���Z�q�̃I�[�o�[���[�h
	//CMatrix + CMatrix �̉��Z���s��
	CMatrix operator+(const CMatrix &m);
};

#endif
