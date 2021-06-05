#pragma once

#include "CVector3.h"
#include "CVector4.h"

/* 4x4�s��N���X�̒�`
| f[ 0] f[ 1] f[ 2] f[ 3] |
| f[ 4] f[ 5] f[ 6] f[ 7] |
| f[ 8] f[ 9] f[10] f[11] |
| f[12] f[13] f[14] f[15] |

| m[0][0] m[0][1] m[0][2] m[0][3] |
| m[1][0] m[1][1] m[1][2] m[1][3] |
| m[2][0] m[2][1] m[2][2] m[2][3] |
| m[3][0] m[3][1] m[3][2] m[3][3] |

| m00 m10 m20 m30 |
| m01 m11 m21 m31 |
| m02 m12 m22 m32 |
| m03 m13 m23 m33 |

*/
class CMatrix44 {
public:
	/* ���p�́F�̈�͋���
	f[0]�Am[0][0]�Am00�͓����G���A���Q�Ƃ���
	f[1]�Am[0][1]�Am10�͓����G���A���Q�Ƃ���
	f[15]�Am[3][3]�Am33�͓����G���A���Q�Ƃ���
	*/
	union //���p�́@���ʂ̗̈���Q�Ƃ���
	{
		float	f[16];
		float	m[4][4];
		struct
		{
			float	m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33;
		};
	};

	CMatrix44();

	/* �P�ʍs��̐ݒ�
	| 1 0 0 0 |
	| 0 1 0 0 |
	| 0 0 1 0 |
	| 0 0 0 1 |
	*/
	void identity();
	/* Y����]�s��̐ݒ�
	| cos 0 -sin 0 |
	|  0  1   0  0 |
	| sin 0  cos 0 |
	|  0  0   0  1 |
	*/
	void rotationY(float deg);
	/* X����]�s��̐ݒ�
	| 1   0    0   0 |
	| 0  cos  sin  0 |
	| 0 -sin  cos  0 |
	| 0   0    0   1 |
	*/
	void rotationX(float deg);
	/* Z����]�s��̐ݒ�
	| cos sin   0   0 |
	|-sin cos   0   0 |
	| 0    0    1   0 |
	| 0    0    0   1 |
	*/
	void rotationZ(float deg);
	/* �ړ��s��̐ݒ�
	| 1 0 0 0 |
	| 0 1 0 0 |
	| 0 0 1 0 |
	| x y z 1 |
	*/
	void translate(float pos[3]);
	/* ���_�Ƃ̊|���Z
	| x y z 1 | * | a b c d |
	| e f g h |
	| i j k l |
	| m n o p |
	x = x*a + y*e + z*i + 1*m
	y = x*b + y*f + z*j + 1*n
	z = x*c + y*g + z*k + 1*o
	*/
	void multi(float *x, float *y, float *z);
	//�s�񓯎m�̊|���Z
	const CMatrix44 operator * (const CMatrix44 &r) const;
	// �x�N�g������ړ��s����쐬���郁�\�b�h�̐錾
	void translate(CVector4 v);
	void translate(CVector3 v);
	void SetQuaternion(float x, float y, float z, float w);
	const CMatrix44 operator * (float f) const;
	void operator += (const CMatrix44 &r);
	const CMatrix44 operator + (const CMatrix44 &r) const;
	//38
	//�t�s��̎擾
	CMatrix44 getInverse(void);
	CMatrix44 getTranspose();
	void scale(const CVector3&);
	const CVector3 operator * (const CVector3& v) const;
	const CVector4 operator * (const CVector4& v) const;
};
