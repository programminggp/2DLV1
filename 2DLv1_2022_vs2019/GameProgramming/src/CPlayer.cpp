#include "CPlayer.h"

void CPlayer::Update()
{
	if (mInput.Key('A'))
	{
		float x = X() - 4.0f;
		X(x);
	}
	//if (mInput.Key('W'))
	//{
	//	float y = Y() + 4.0f;
	//	Y(y);
	//}
	if (mInput.Key('D'))
	{
		float x = X() + 4.0f;
		X(x);
	}
	//if (mInput.Key('S'))
	//{
	//	float y = Y() - 4.0f;
	//	Y(y);
	//}
}
