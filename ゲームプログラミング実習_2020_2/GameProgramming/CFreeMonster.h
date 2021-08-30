#ifndef CFREEMONSTER_H
#define CFREEMONSTER_H

#include "CModelX.h"
#include "CXCharacter.h"

class CFreeMonster : public CXCharacter
{
	static CModelX sModel;
public:
	CFreeMonster();
	void Set(const CVector &pos, const CVector &rot, const CVector &scale);
	~CFreeMonster();
};

#endif
