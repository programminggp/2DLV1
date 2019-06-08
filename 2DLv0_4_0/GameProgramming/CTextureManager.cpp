#include "CTextureManager.h"

CTexture CTextureManager::mBackGround;
CTexture CTextureManager::mShoot;
CTexture CTextureManager::mEnemy;
CTexture CTextureManager::mPlayer;
CTexture CTextureManager::mBossExplosion;


void CTextureManager::Load() {
	mBackGround.Load("BackGround.tga");
	mShoot.Load("Shoot.tga");
	mEnemy.Load("Enemy.tga");
	mPlayer.Load("Player.tga");
	mBossExplosion.Load("BossExplosion.tga");
}
