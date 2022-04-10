#include "CBullet.h"
#include <Windows.h>
void CBullet::Update()
{
	float y = Y() + H();
	short key = GetAsyncKeyState(VK_SPACE);
	if ( y > 600)
	{                                  
		y = 0.0f;
	}
	Y(y);
}

void CBullet::Render()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	CRectangle::Render();
	glColor3f(1.0f, 1.0f, 1.0f);
}
