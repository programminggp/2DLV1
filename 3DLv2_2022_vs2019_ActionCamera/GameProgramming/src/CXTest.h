#pragma once
#include "CXCharacter.h"
#include "CCollider.h"

class CXTest : public CXCharacter
{
public:
	CXTest();
	void Update();
private:
	static CModelX sModel;
};