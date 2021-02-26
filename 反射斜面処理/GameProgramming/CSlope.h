#ifndef CSLOPE_H
#define CSLOPE_H

#include "CObj.h"

class CSlope : public CObj
{
public:
	CSlope(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale);
	void Update();
};


#endif
