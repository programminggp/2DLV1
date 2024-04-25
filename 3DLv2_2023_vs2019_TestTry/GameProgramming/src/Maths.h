#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
	/// <summary>
	/// �f�B�O���[�i�x�j�����W�A���ɕϊ�
	/// </summary>
	/// <param name="degree">�p�x�i�x�j</param>
	/// <returns>�p�x�i���W�A���j</returns>
	float DegreeToRadian(float degree);
	/// <summary>
	/// ���W�A�����f�B�O���[�i�x�j�ɕϊ�
	/// </summary>
	/// <param name="radian">�p�x�i���W�A���j</param>
	/// <returns>�p�x�i�x�j</returns>
	float RadianToDegree(float radian);

	/// <summary>
	/// �������擾�i�����j
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>����</returns>
	int Rand(int min, int max);
	/// <summary>
	/// �������擾�i�����j
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>����</returns>
	float Rand(float min, float max);

	/// <summary>
	/// �l���ŏ��l����ő�l-1�͈̔͂Ɏ��߂�
	/// </summary>
	/// <param name="value">�ΏۂƂȂ�l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�ŏ��l����ő�l-1�͈̔͂Ɏ��߂�����</returns>
	int Clamp(int value, int min, int max);
	/// <summary>
	/// �l���ŏ��l����ő�l�͈̔͂Ɏ��߂�
	/// </summary>
	/// <param name="value">�ΏۂƂȂ�l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�ŏ��l����ő�l�͈̔͂Ɏ��߂�����</returns>
	float Clamp(float value, float min, float max);
	/// <summary>
	/// �l��0.0f�`1.0f�͈̔͂Ɏ��߂�
	/// </summary>
	/// <param name="value">�ΏۂƂȂ�l</param>
	/// <returns>0.0f�`1.0f�Ɏ��߂�����</returns>
	float Clamp01(float value);

	/// <summary>
	/// 2�̒l����`��Ԃ���
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԋ����i0.0f�`1.0f�j</param>
	/// <returns></returns>
	float Lerp(float a, float b, float t);

	/// <summary>
	/// 0����w��l�͈̔͂Ń��[�v������
	/// </summary>
	/// <param name="t">�ΏۂƂȂ�l</param>
	/// <param name="length">�͈͂̍ő�l</param>
	/// <returns>���[�v����������</returns>
	float Repeat(float t, float length);
	/// <summary>
	/// 0����w��l�͈̔͂Ń��[�v������
	/// </summary>
	/// <param name="t">�ΏۂƂȂ�l</param>
	/// <param name="length">�͈͂̍ő�l</param>
	/// <returns>���[�v����������</returns>
	int Repeat(int t, int length);
}
