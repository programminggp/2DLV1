#include "Easing.h"

namespace Easing
{
	float QuadIn(float t, float total, float min, float max)
	{
		max -= min;
		t /= total;
		return max * t * t + min;
	}

	float QuadOut(float t, float total, float min, float max)
	{
		max -= min;
		t /= total;
		return -max * t * (t - 2.0f) + min;
	}

	float QuadInOut(float t, float total, float min, float max)
	{
		max -= min;
		t /= total / 2.0f;
		if (t < 1.0f)return max / 2.0f * t * t + min;

		t = t - 1;
		return -max / 2.0f * (t * (t - 2) - 1) + min;
	}

	float CubicIn(float t, float total, float min, float max)
	{
		max -= min;
		t /= total;
		return max * t * t * t + min;
	}

	float CubicOut(float t, float total, float min, float max)
	{
		max -= min;
		t = t / total - 1.0f;
		return max * (t * t * t + 1) + min;
	}

	float CubicInOut(float t, float total, float min, float max)
	{
		max -= min;
		t /= total / 2.0f;
		if (t < 1.0f) return max / 2.0f * t * t * t + min;

		t = t - 2.0f;
		return max / 2.0f * (t * t * t + 2.0f) + min;
	}

	float QuartIn(float t, float total, float min, float max)
	{
		max -= min;
		t /= total;
		return max * t * t * t * t + min;
	}

	float QuartOut(float t, float total, float min, float max)
	{
		max -= min;
		t = t / total - 1.0f;
		return -max * (t * t * t * t - 1.0f) + min;
	}

	float QuartInOut(float t, float total, float min, float max)
	{
		max -= min;
		t /= total / 2.0f;
		if (t < 1.0f) return max / 2.0f * t * t * t * t + min;

		t = t - 2.0f;
		return -max / 2.0f * (t * t * t * t - 2.0f) + min;
	}

	float QuintIn(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float QuintOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float QuintInOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float SineIn(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float SineOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float SineInOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float ExpIn(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float ExpOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float ExpInOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float CircIn(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float CircOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float CircInOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float ElasticIn(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float ElasticOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float ElasticInOut(float t, float total, float min, float max)
	{
		return 0.0f;
	}

	float BackIn(float t, float total, float min, float max, float s)
	{
		return 0.0f;
	}

	float BackOut(float t, float total, float min, float max, float s)
	{
		return 0.0f;
	}

	float BackInOut(float t, float total, float min, float max, float s)
	{
		return 0.0f;
	}

	float BounceIn(float t, float total, float min, float max, float s)
	{
		return 0.0f;
	}

	float BounceOut(float t, float total, float min, float max, float s)
	{
		return 0.0f;
	}

	float BounceInOut(float t, float total, float min, float max, float s)
	{
		return 0.0f;
	}
}
