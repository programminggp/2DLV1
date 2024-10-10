#pragma once
#include "CCharacter3.h"

class CMap : public CCharacter3
{
public:
	CMap();
	void Update(){}
private:
	static CModel mModel;
	static bool mLoad;
};
