#ifndef CFELGUARD_H
#define CFELGUARD_H

#include "CModelX.h"
#include "CXCharacter.h"

class CFelguard : public CXCharacter
{
	static CModelX *spModel;
	static int sCount;
public:
	CFelguard();
	void Set(const CVector &pos, const CVector &rot, const CVector &scale);
	~CFelguard();
};

#endif
