#include "CBullet.h"
void CBullet::Update()
{
	float y = Y() + H();
	if (y > 600.0f)
	{
		y = 0.0f;
	}
	/*if (y > 600)
	{
		y = 700.0f;
	}*/
	Y(y);
}

void CBullet::Render()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	CRectangle::Render();
	glColor3f(1.0f, 1.0f, 1.0f);
}
