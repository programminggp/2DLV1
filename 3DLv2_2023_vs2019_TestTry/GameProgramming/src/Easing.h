#pragma once

namespace Easing
{
	float QuadIn(float t, float total, float min, float max);
	float QuadOut(float t, float total, float min, float max);
	float QuadInOut(float t, float total, float min, float max);
	float CubicIn(float t, float total, float min, float max);
	float CubicOut(float t, float total, float min, float max);
	float CubicInOut(float t, float total, float min, float max);
	float QuartIn(float t, float total, float min, float max);
	float QuartOut(float t, float total, float min, float max);
	float QuartInOut(float t, float total, float min, float max);
	float QuintIn(float t, float total, float min, float max);
	float QuintOut(float t, float total, float min, float max);
	float QuintInOut(float t, float total, float min, float max);
	float SineIn(float t, float total, float min, float max);
	float SineOut(float t, float total, float min, float max);
	float SineInOut(float t, float total, float min, float max);
	float ExpIn(float t, float total, float min, float max);
	float ExpOut(float t, float total, float min, float max);
	float ExpInOut(float t, float total, float min, float max);
	float CircIn(float t, float total, float min, float max);
	float CircOut(float t, float total, float min, float max);
	float CircInOut(float t, float total, float min, float max);
	float ElasticIn(float t, float total, float min, float max);
	float ElasticOut(float t, float total, float min, float max);
	float ElasticInOut(float t, float total, float min, float max);
	float BackIn(float t, float total, float min, float max, float s);
	float BackOut(float t, float total, float min, float max, float s);
	float BackInOut(float t, float total, float min, float max, float s);
	float BounceIn(float t, float total, float min, float max, float s);
	float BounceOut(float t, float total, float min, float max, float s);
	float BounceInOut(float t, float total, float min, float max, float s);
}
