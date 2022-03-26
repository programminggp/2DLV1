#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
}

void CApplication::Update()
{
	mRectangle.Render(200.0f, 450.0f, 200.0f, 150.0f);
}

