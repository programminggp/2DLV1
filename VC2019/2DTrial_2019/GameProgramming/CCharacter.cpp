#include "CCharacter.h"
#include "CRectangle.h"
#include "CSceneGame.h"

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

/*
void CCharacter::Set(float x, float y, float w, float h) {
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	//mRect.mX = x;
	//mRect.mY = y;
	//mRect.mW = w;
	//mRect.mH = h;
}
*/

void CCharacter::Render() {
//	CRectangle::Render(mX, mY, mW, mH);
	CRectangle::Render();
}
