#include "CUI.h"

CFont CUI::mFont;
int CUI::mEnemyHit = 0;
int CUI::mPlayerHit = 0;

void CUI::Render() {
	char str[50];
	sprintf(str, "ENEMY %5d", mEnemyHit);
	mFont.Render(str, 50, 580, 12, 16);
	sprintf(str, "PLAYER %5d", mPlayerHit);
	mFont.Render(str, 450, 580, 12, 16);
}
