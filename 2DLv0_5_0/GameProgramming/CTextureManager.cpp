#include "CTextureManager.h"

CTexture CTextureManager::mTexture;


void CTextureManager::Load() {
	mTexture.Load("Bomberman.tga");
}
