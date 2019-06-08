#ifndef CTEXTUREMANAGER_H
#define CTEXTUREMANAGER_H

#include "CTexture.h"

class CTextureManager {
public:
	static CTexture mBackGround;
	static CTexture mShoot;
	static CTexture mEnemy;
	static CTexture mPlayer;
	static CTexture mBossExplosion;

	static void Load();
};


#endif
