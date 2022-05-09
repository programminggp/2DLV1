#pragma once
#include "CCharacter.h"

class CMiss : public CCharacter
{
public:
	CMiss()
	{
		mTag = ETag::EMISS;
	}
	void Update() {}
	void Render() {}
};
