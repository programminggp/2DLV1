#ifndef CUI_H
#define CUI_H

#include "CFont.h"
#include "CCamera.h"

class CUI {
public:
	static CCamera mCamera;
	static CFont mFont;
	static int mEnemyHit;
	static int mPlayerHit;
	static void Render();
};


#endif
