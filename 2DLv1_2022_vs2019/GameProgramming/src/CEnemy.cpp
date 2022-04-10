#include "CEnemy.h"

void CEnemy::Update()
{
	float x = X() + 8;
	if (x > 800.0f)
	{
		x = 0.0f;
	}
	X(x);
}
