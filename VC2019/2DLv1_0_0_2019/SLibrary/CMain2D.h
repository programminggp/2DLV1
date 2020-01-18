#ifndef CMAIN2D_H
#define CMAIN2D_H

#include "CMain.h"

class CMain2D : public CMain {
public:
	CMain2D();
	CMain2D(int width, int height);
	int SetScene(CScene* pscene);
};

#endif
