#include "Maths.h"
#include <random>
#include <time.h>

// 乱数シード値用
std::random_device rnd;
// 擬似乱数列生成器
std::mt19937 mt(rnd());

// ディグリー（度）をラジアンに変換
float Math::DegreeToRadian(float degree)
{
	return (float)(degree * (M_PI / 180.0f));
}

// ラジアンをディグリー（度）に変換
float Math::RadianToDegree(float radian)
{
	return (float)(radian * (180.0f / M_PI));
}

// 乱数を取得（整数）
int Math::Rand(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

// 乱数を取得（小数）
float Math::Rand(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}

// 値を最小値から最大値-1の範囲に収める
int Math::Clamp(int value, int min, int max)
{
	return std::min(std::max(value, min), max - 1);
}

// 値を最小値から最大値の範囲に収める
float Math::Clamp(float value, float min, float max)
{
	return std::min(std::max(value, min), max);
}

// 値を0.0f～1.0fの範囲に収める
float Math::Clamp01(float value)
{
	return Clamp(value, 0.0f, 1.0f);
}

// 2つの値を線形補間する
float Math::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

// 0から指定値の範囲でループさせる
float Math::Repeat(float t, float length)
{
	float v = fmodf(t, length);
	return v < 0.0f ? v + length : v;
}

// 0から指定値の範囲でループさせる
int Math::Repeat(int t, int length)
{
	int v = t % length;
	return v < 0 ? v + length : v;
}
