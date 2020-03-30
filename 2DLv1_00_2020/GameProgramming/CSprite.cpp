#include "CSprite.h"


CSprite::CSprite()
: mpTexture(0)
{

}

CSprite::CSprite(float x, float y, float w, float h, float r, CTexture *ptexture)
: CRect(x, y, w, h, r)
, mpTexture(ptexture)
{

}

void CSprite::Set(float x, float y, float w, float h, float r, CTexture *ptexture) {
	CRect::Set(x, y, w, h, r);
	mpTexture = ptexture;
}

void CSprite::Set(CTexture *ptexture) {
	mpTexture = ptexture;
}

void CSprite::Render() {
	if (mpTexture) {
		glPushMatrix();
		glTranslatef(mX, mY, 0.0f);
		glRotatef(mR, 0.0f, 0.0f, 1.0f);
		glScalef(mW, mH, 0.0f);
		mpTexture->Draw(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		glPopMatrix();
	}
	else {
		CRect::Render();
	}
}

void CSprite::Render(int uleft, int uright, int ubottom, int utop) {
	if (mpTexture) {
		glPushMatrix();
		glTranslatef(mX, mY, 0.0f);
		glRotatef(mR, 0.0f, 0.0f, 1.0f);
		glScalef(mW, mH, 0.0f);
		mpTexture->Draw(-1.0f, 1.0f, -1.0f, 1.0f, uleft, uright, ubottom, utop);
		glPopMatrix();
	}
	else {
		CRect::Render();
	}
}
