#ifndef CMATRIX_H
#define CMATRIX_H
/*
�}�g���N�X�N���X
4�s4��̍s��f�[�^�������܂�
*/
class CMatrix {
public:
	union
	{
		//4�~4�̍s��f�[�^��ݒ�
		float mM[4][4];
		//float mF[16];
		//struct
		//{
		//	float
		//		m00, m10, m20, m30,
		//		m01, m11, m21, m31,
		//		m02, m12, m22, m32,
		//		m03, m13, m23, m33;
		//};
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

	CMatrix operator*(const float& f) const;

	CMatrix CMatrix::GetInverse();
	CMatrix CMatrix::GetTranspose();
};

#endif
