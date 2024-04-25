#include "Maths.h"
#include <random>
#include <time.h>

// �����V�[�h�l�p
std::random_device rnd;
// �[�������񐶐���
std::mt19937 mt(rnd());

// �f�B�O���[�i�x�j�����W�A���ɕϊ�
float Math::DegreeToRadian(float degree)
{
	return (float)(degree * (M_PI / 180.0f));
}

// ���W�A�����f�B�O���[�i�x�j�ɕϊ�
float Math::RadianToDegree(float radian)
{
	return (float)(radian * (180.0f / M_PI));
}

// �������擾�i�����j
int Math::Rand(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

// �������擾�i�����j
float Math::Rand(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}

// �l���ŏ��l����ő�l-1�͈̔͂Ɏ��߂�
int Math::Clamp(int value, int min, int max)
{
	return std::min(std::max(value, min), max - 1);
}

// �l���ŏ��l����ő�l�͈̔͂Ɏ��߂�
float Math::Clamp(float value, float min, float max)
{
	return std::min(std::max(value, min), max);
}

// �l��0.0f�`1.0f�͈̔͂Ɏ��߂�
float Math::Clamp01(float value)
{
	return Clamp(value, 0.0f, 1.0f);
}

// 2�̒l����`��Ԃ���
float Math::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

// 0����w��l�͈̔͂Ń��[�v������
float Math::Repeat(float t, float length)
{
	float v = fmodf(t, length);
	return v < 0.0f ? v + length : v;
}

// 0����w��l�͈̔͂Ń��[�v������
int Math::Repeat(int t, int length)
{
	int v = t % length;
	return v < 0 ? v + length : v;
}
