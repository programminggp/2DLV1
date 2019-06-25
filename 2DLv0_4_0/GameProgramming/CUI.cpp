#include "CUI.h"

CCamera CUI::mCamera;
CFont CUI::mFont;
int CUI::mEnemyHit = 0;
int CUI::mPlayerHit = 0;

void CUI::Render() {
	mCamera.Camera2D(400, 300, 400, 300);
	char str[50];
	sprintf(str, "ENEMY %5d", mEnemyHit);
	mFont.Render(str, -350 + 400, 280 + 300, 12, 16);
	sprintf(str, "PLAYER %5d", mPlayerHit);
	mFont.Render(str, 50 + 400, 280 + 300, 12, 16);
}
