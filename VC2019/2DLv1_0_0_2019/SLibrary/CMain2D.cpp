#include "CMain2D.h"

CMain2D::CMain2D() {
	Init2D();
}

CMain2D::CMain2D(int width, int height) {
	Init2D(width, height);
}

int CMain2D::SetScene(CScene* pscene) {
	return Main2D(pscene);
}
