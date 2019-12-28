#ifndef CUI_H
#define CUI_H

#include "CFont.h"

class CUI {
public:
	static CFont mFont;
	static int mEnemyHit;
	static int mPlayerHit;
	static void Render();
};


#endif
