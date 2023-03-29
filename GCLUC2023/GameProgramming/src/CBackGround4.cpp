#include "CBackGround4.h"
#include "CApplication.h"
void CBackGround4::Update()
{
}
CBackGround4::CBackGround4(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt)
	: CCharacter((int)ETaskPriority::EBackGround4)
{
	Set(x, y, w, h);
	Texture(pt, l, r, b, t);
}