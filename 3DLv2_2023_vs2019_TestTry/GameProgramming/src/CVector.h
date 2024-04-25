#pragma once
#include "CMatrix.h"
class CVector2;
class CVector4;

/// <summary>
/// 3�����x�N�g��
/// </summary>
class CVector
{
public:
	// �R���X�g���N�^�i�����Ȃ��j
	CVector();
	// �R���X�g���N�^�ixyz�j
	CVector(float x, float y, float z);
	// �R���X�g���N�^�iCVector2�j
	CVector(const CVector2& v);
	// �R���X�g���N�^�iCVector2 + z�j
	CVector(const CVector2& v, float z);
	// �R���X�g���N�^�iCVector4�j
	CVector(const CVector4& v);
	// �f�X�g���N�^
	~CVector();

	// CVector == CVector �̌��ʂ�Ԃ�
	bool operator == (const CVector& v) const;
	// CVector != CVector �̌��ʂ�Ԃ�
	bool operator != (const CVector& v) const;

	// -CVector �̉��Z���ʂ�Ԃ�
	CVector operator - () const;

	// CVector + CVector �̉��Z���ʂ�Ԃ�
	CVector operator + (const CVector& v) const;
	// CVector += CVector �ŉ��Z���ʂ����g�ɑ��
	void operator += (const CVector& v);

	// CVector - CVector �̉��Z���ʂ�Ԃ�
	CVector operator - (const CVector& v) const;
	// CVector -= CVector �ŉ��Z���ʂ����g�ɑ��
	void operator -= (const CVector& v);

	// CVector * float �̉��Z���ʂ�Ԃ�
	CVector operator * (const float& f) const;
	// CVector *= float �ŉ��Z���ʂ����g�ɑ��
	void operator *= (const float& f);
	// CVector * CMatrix�̌��ʂ�CVector�ŕԂ�
	CVector operator * (const CMatrix& m) const;

	// �e���̒l��ݒ�
	void Set(float x, float y, float z);

	// X���̒l���擾
	float X() const;
	// X���̒l��ݒ�
	void X(float x);
	// Y���̒l���擾
	float Y() const;
	// Y���̒l��ݒ�
	void Y(float y);
	// Z���̒l���擾
	float Z() const;
	// Z���̒l��ݒ�
	void Z(float z);

	// �x�N�g���𐳋K��
	void Normalize();
	/// <summary>
	/// ���K�������x�N�g�����擾
	/// </summary>
	/// <returns>���K�������x�N�g��</returns>
	CVector Normalized() const;

	/// <summary>
	/// �w�肵���x�N�g���Ƃ̓��ς����߂�
	/// </summary>
	/// <param name="v">����̃x�N�g��</param>
	/// <returns>���ς̌���</returns>
	float Dot(const CVector& v) const;
	/// <summary>
	/// 2�̃x�N�g���̓��ς����߂�
	/// </summary>
	/// <param name="v0">1�ڂ̃x�N�g��</param>
	/// <param name="v1">2�ڂ̃x�N�g��</param>
	/// <returns>���ς̌���</returns>
	static float Dot(const CVector& v0, const CVector& v1);

	/// <summary>
	/// �w�肵���x�N�g���Ƃ̊O�ς����߂�
	/// </summary>
	/// <param name="v">����̃x�N�g��</param>
	/// <returns>�O�ς̌��ʁi3�����̓x�N�g���j</returns>
	CVector Cross(const CVector& v) const;
	/// <summary>
	/// 2�̃x�N�g���̊O�ς����߂�
	/// </summary>
	/// <param name="v0">1�ڂ̃x�N�g��</param>
	/// <param name="v1">2�ڂ̃x�N�g��</param>
	/// <returns>�O�ς̌��ʁi3�����̓x�N�g���j</returns>
	static CVector Cross(const CVector& v0, const CVector& v1);

	/// <summary>
	/// �x�N�g���̒������擾
	/// </summary>
	/// <returns>�x�N�g���̒���</returns>
	float Length() const;
	/// <summary>
	/// �x�N�g����2��̒������擾
	/// </summary>
	/// <returns>�x�N�g����2��̒���</returns>
	float LengthSqr() const;

	/// <summary>
	/// 2�_�Ԃ̋��������߂�
	/// </summary>
	/// <param name="p0">1�ڂ̍��W</param>
	/// <param name="p1">2�ڂ̍��W</param>
	/// <returns>2�_�Ԃ̋���</returns>
	static float Distance(const CVector& p0, const CVector& p1);
	/// <summary>
	/// 2�̃x�N�g���̊p�x�����߂�
	/// �i�ŒZ�p�x�����߂�̂�0�`180�̒l��Ԃ��j
	/// </summary>
	/// <param name="v0">1�ڂ̃x�N�g��</param>
	/// <param name="v1">2�ڂ̃x�N�g��</param>
	/// <returns>2�̃x�N�g���̊p�x�i�f�B�O���[�j</returns>
	static float Angle(const CVector& v0, const CVector& v1);

	/// <summary>
	/// 2�_�Ԃ���`��Ԃ���
	/// </summary>
	/// <param name="a">�J�n�ʒu</param>
	/// <param name="b">�I���ʒu</param>
	/// <param name="t">��Ԋ����i0.0f�`1.0f�j</param>
	/// <returns>���`��Ԃ̌���</returns>
	static CVector Lerp(const CVector& a, const CVector& b, float t);
	/// <summary>
	/// 2�̃x�N�g���Ԃ����ʐ��`��Ԃ���
	/// </summary>
	/// <param name="a">�J�n�x�N�g��</param>
	/// <param name="b">�I���x�N�g��</param>
	/// <param name="t">��Ԋ����i0.0f�`1.0f�j</param>
	/// <returns></returns>
	static CVector Slerp(const CVector& a, const CVector& b, float t);

	// 0�x�N�g�� [0, 0, 0]
	const static CVector zero;
	// 1�x�N�g�� [1, 1, 1]
	const static CVector one;
	// ���x�N�g�� [-1, 0, 0]
	const static CVector left;
	// �E�x�N�g�� [1, 0, 0]
	const static CVector right;
	// ��x�N�g�� [0, 1, 0]
	const static CVector up;
	// ���x�N�g�� [0, -1, 0]
	const static CVector down;
	// �O���x�N�g�� [0, 0, 1]
	const static CVector forward;
	// ����x�N�g�� [0, 0, -1]
	const static CVector back;

private:
	// 3D�e���ł̒l��ݒ�
	float mX, mY, mZ;
};

/// <summary>
/// 2�����x�N�g��
/// </summary>
class CVector2
{
public:
	// �R���X�g���N�^�i�����Ȃ��j
	CVector2();
	// �R���X�g���N�^�ixy�j
	CVector2(float x, float y);
	// �R���X�g���N�^�iCVector�j
	CVector2(const CVector& v);
	// �f�X�g���N�^
	~CVector2();

	// CVector2 == CVector2 �̌��ʂ�Ԃ�
	bool operator == (const CVector2& v) const;
	// CVector2 != CVector2 �̌��ʂ�Ԃ�
	bool operator != (const CVector2& v) const;

	// -CVector2 �̉��Z���ʂ�Ԃ�
	CVector2 operator - () const;

	// CVector2 + CVector2 �̉��Z���ʂ�Ԃ�
	CVector2 operator + (const CVector2& v) const;
	// CVector2 += CVector2 �ŉ��Z���ʂ����g�ɑ��
	void operator += (const CVector2& v);

	// CVector2 - CVector2 �̉��Z���ʂ�Ԃ�
	CVector2 operator - (const CVector2& v) const;
	// CVector2 -= CVector2 �ŉ��Z���ʂ����g�ɑ��
	void operator -= (const CVector2& v);

	// CVector2 * float �̉��Z���ʂ�Ԃ�
	CVector2 operator * (const float& f) const;
	// CVector2 *= float �ŉ��Z���ʂ����g�ɑ��
	void operator *= (const float& f);
	// CVector2 * CMatrix�̌��ʂ�CVector2�ŕԂ�
	CVector2 operator * (const CMatrix& m);

	// �e���̒l��ݒ�
	void Set(float x, float y);

	// X���̒l���擾
	float X() const;
	// X���̒l��ݒ�
	void X(float x);
	// Y���̒l���擾
	float Y() const;
	// Y���̒l��ݒ�
	void Y(float y);

	// �x�N�g���𐳋K��
	void Normalize();
	/// <summary>
	/// ���K�������x�N�g�����擾
	/// </summary>
	/// <returns>���K�������x�N�g��</returns>
	CVector2 Normalized() const;

	/// <summary>
	/// �w�肵���x�N�g���Ƃ̓��ς����߂�
	/// </summary>
	/// <param name="v">����̃x�N�g��</param>
	/// <returns>���ς̌���</returns>
	float Dot(const CVector2& v) const;
	/// <summary>
	/// 2�̃x�N�g���̓��ς����߂�
	/// </summary>
	/// <param name="v0">1�ڂ̃x�N�g��</param>
	/// <param name="v1">2�ڂ̃x�N�g��</param>
	/// <returns>���ς̌���</returns>
	static float Dot(const CVector2& v0, const CVector2& v1);

	/// <summary>
	/// �w�肵���x�N�g���Ƃ̊O�ς����߂�
	/// </summary>
	/// <param name="v">����̃x�N�g��</param>
	/// <returns>�O�ς̌���</returns>
	float Cross(const CVector2& v) const;
	/// <summary>
	/// 2�̃x�N�g���̊O�ς����߂�
	/// </summary>
	/// <param name="v0">1�ڂ̃x�N�g��</param>
	/// <param name="v1">2�ڂ̃x�N�g��</param>
	/// <returns>�O�ς̌���</returns>
	static float Cross(const CVector2& v0, const CVector2& v1);

	/// <summary>
	/// �x�N�g���̒������擾
	/// </summary>
	/// <returns>�x�N�g���̒���</returns>
	float Length() const;
	/// <summary>
	/// �x�N�g����2��̒������擾
	/// </summary>
	/// <returns>�x�N�g����2��̒���</returns>
	float LengthSqr() const;

	/// <summary>
	/// 2�_�Ԃ̋��������߂�
	/// </summary>
	/// <param name="p0">1�ڂ̍��W</param>
	/// <param name="p1">2�ڂ̍��W</param>
	/// <returns>2�_�Ԃ̋���</returns>
	static float Distance(const CVector2& p0, const CVector2& p1);
	/// <summary>
	/// 2�̃x�N�g���̊p�x�����߂�
	/// �i�ŒZ�p�x�����߂�̂�0�`180�̒l��Ԃ��j
	/// </summary>
	/// <param name="v0">1�ڂ̃x�N�g��</param>
	/// <param name="v1">2�ڂ̃x�N�g��</param>
	/// <returns>2�̃x�N�g���̊p�x�i�f�B�O���[�j</returns>
	static float Angle(const CVector2& v0, const CVector2& v1);

	// 0�x�N�g�� [0, 0]
	const static CVector2 zero;
	// 1�x�N�g�� [1, 1]
	const static CVector2 one;
	// ���x�N�g�� [-1, 0]
	const static CVector2 left;
	// �E�x�N�g�� [1, 0]
	const static CVector2 right;
	// ��x�N�g�� [0, 1]
	const static CVector2 up;
	// ���x�N�g�� [0, -1]
	const static CVector2 down;

private:
	// 2D�e���ł̒l��ݒ�
	float mX, mY;
};

//�x�N�g���N���X�i4�����j
class CVector4
{
public:
	// �R���X�g���N�^�i�����Ȃ��j
	CVector4();
	// �R���X�g���N�^�ixyzw�j
	CVector4(float x, float y, float z, float w);
	// �R���X�g���N�^�ixyz�j
	CVector4(float x, float y, float z);
	// �R���X�g���N�^�iCVector�j
	CVector4(const CVector& v);
	// �R���X�g���N�^�iCVector + w�j
	CVector4(const CVector& v, float w);

	//�e���ł̒l�̐ݒ�
	//Set(X���W, Y���W, Z���W, W)
	void Set(float x, float y, float z, float w);
	//Set(X���W, Y���W, Z���W)
	void Set(float x, float y, float z);
	//X�̒l�𓾂�
	float X() const;
	//X�̒l��ݒ�
	void X(float x);
	//Y�̒l�𓾂�
	float Y() const;
	//Y�̒l��ݒ�
	void Y(float y);
	//Z�̒l�𓾂�
	float Z() const;
	//Z�̒l��ݒ�
	void Z(float z);
	//W�̒l�𓾂�
	float W() const;
	//W�̒l��ݒ�
	void W(float w);
	//�C���f�b�N�X�l���w�肵�Ēl���擾
	float V(int n) const;
	//�C���f�b�N�X�l���w�肵�Ēl��ݒ�
	void V(int n, float v);

	//������Z�q
	//CVector4 = CVector ��CVector�̓��e�����g�ɑ��
	void operator=(const CVector& v);

	//��r���Z�q
	//CVector4 == CVector4 �̌��ʂ�Ԃ�
	bool operator==(const CVector4& v) const;
	//CVector4 != CVector4 �̌��ʂ�Ԃ�
	bool operator!=(const CVector4& v) const;

	//+���Z�q�̃I�[�o�[���[�h
	//CVector4 + CVector4 �̉��Z���ʂ�Ԃ�
	CVector4 operator+(const CVector4& v) const;
	//CVector4 += CVector4 �ŉ��Z���ʂ����g�ɑ��
	void operator+=(const CVector4& v);


	//-���Z�q�̃I�[�o�[���[�h
	//CVector4 - CVector4 �̉��Z���ʂ�Ԃ�
	CVector4 operator-(const CVector4& v) const;
	//CVector4 -= CVector4 �ŉ��Z���ʂ����g�ɑ��
	void operator-=(const CVector4& v);

	//*���Z�q�̃I�[�o�[���[�h
	//CVector4 * float �̉��Z���ʂ�Ԃ�
	CVector4 operator*(const float& f) const;
	//CVector4 *= float �ŉ��Z���ʂ����g�ɑ��
	void operator*=(const float& f);

	//CVector4 * CMatrix �̉��Z���ʂ�Ԃ�
	CVector4 operator*(const CMatrix& m) const;

private:
	//4D�ł̒l��ݒ�
	float mX, mY, mZ, mW;
};

//CMatrix * CVector �̉��Z���ʂ�Ԃ�
CVector operator * (const CMatrix& m, const CVector& v);
//CMatrix * CVector4 �̉��Z���ʂ�Ԃ�
CVector4 operator * (const CMatrix& m, const CVector4& v);
