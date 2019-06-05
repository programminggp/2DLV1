#include "CCharacter.h"
#include "CSceneGame.h"

CCharacter::CCharacter()
	: mEnabled(true)
{
//	CSceneGame::mCharacters.push_back(this);
}

CCharacter::~CCharacter() {
	//std::vector<CCharacter*>::iterator it = std::find(CSceneGame::mCharacters.begin(), CSceneGame::mCharacters.end(), this);
	//if (it != CSceneGame::mCharacters.end()) {
	//	CSceneGame::mCharacters.erase(it);
	//}
}
