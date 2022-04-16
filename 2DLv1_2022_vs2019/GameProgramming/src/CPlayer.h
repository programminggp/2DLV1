#pragma once
#include "CCharacter.h"
#include "CInput.h"

class CPlayer : public CCharacter
{
private:
	CInput mInput;
public:
	void Update();
};