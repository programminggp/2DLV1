#ifndef CFREEMONSTER_H
#define CFREEMONSTER_H

#include "CModelX.h"
#include "CXCharacter.h"

class CFreeMonster : public CXCharacter
{
public:
	static CModelX *spModel;
	CFreeMonster();
	void Set(const CVector &pos, const CVector &rot, const CVector &scale);
	~CFreeMonster();
};

#endif
