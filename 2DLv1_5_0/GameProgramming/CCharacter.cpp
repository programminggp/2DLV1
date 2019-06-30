#include "CCharacter.h"
#include "CSceneGame.h"
#include "CRectangle.h"

CCharacter::CCharacter()
	: mState(EENABLED)
{
//	CSceneGame::mCharacters.push_back(this);
}

CCharacter::~CCharacter() {
	//std::vector<CCharacter*>::iterator it = std::find(CSceneGame::mCharacters.begin(), CSceneGame::mCharacters.end(), this);
	//if (it != CSceneGame::mCharacters.end()) {
	//	CSceneGame::mCharacters.erase(it);
	//}
}

void CCharacter::Set(int posx, int posy, int width, int height) {
	mX = posx;
	mY = posy;
	mW = width;
	mH = height;
}
