#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
	mRectangle.Set(400.0f, 300.0f, 200.0f, 100.0f);
}

void CApplication::Update()
{
	mRectangle.Render();
}

