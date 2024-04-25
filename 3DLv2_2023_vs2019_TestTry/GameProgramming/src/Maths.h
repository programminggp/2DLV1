#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
	/// <summary>
	/// ディグリー（度）をラジアンに変換
	/// </summary>
	/// <param name="degree">角度（度）</param>
	/// <returns>角度（ラジアン）</returns>
	float DegreeToRadian(float degree);
	/// <summary>
	/// ラジアンをディグリー（度）に変換
	/// </summary>
	/// <param name="radian">角度（ラジアン）</param>
	/// <returns>角度（度）</returns>
	float RadianToDegree(float radian);

	/// <summary>
	/// 乱数を取得（整数）
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>乱数</returns>
	int Rand(int min, int max);
	/// <summary>
	/// 乱数を取得（小数）
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>乱数</returns>
	float Rand(float min, float max);

	/// <summary>
	/// 値を最小値から最大値-1の範囲に収める
	/// </summary>
	/// <param name="value">対象となる値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>最小値から最大値-1の範囲に収めた結果</returns>
	int Clamp(int value, int min, int max);
	/// <summary>
	/// 値を最小値から最大値の範囲に収める
	/// </summary>
	/// <param name="value">対象となる値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>最小値から最大値の範囲に収めた結果</returns>
	float Clamp(float value, float min, float max);
	/// <summary>
	/// 値を0.0f～1.0fの範囲に収める
	/// </summary>
	/// <param name="value">対象となる値</param>
	/// <returns>0.0f～1.0fに収めた結果</returns>
	float Clamp01(float value);

	/// <summary>
	/// 2つの値を線形補間する
	/// </summary>
	/// <param name="a">開始値</param>
	/// <param name="b">終了値</param>
	/// <param name="t">補間割合（0.0f～1.0f）</param>
	/// <returns></returns>
	float Lerp(float a, float b, float t);

	/// <summary>
	/// 0から指定値の範囲でループさせる
	/// </summary>
	/// <param name="t">対象となる値</param>
	/// <param name="length">範囲の最大値</param>
	/// <returns>ループさせた結果</returns>
	float Repeat(float t, float length);
	/// <summary>
	/// 0から指定値の範囲でループさせる
	/// </summary>
	/// <param name="t">対象となる値</param>
	/// <param name="length">範囲の最大値</param>
	/// <returns>ループさせた結果</returns>
	int Repeat(int t, int length);
}
