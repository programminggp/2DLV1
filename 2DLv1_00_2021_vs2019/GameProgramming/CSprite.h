#ifndef CSPRITE_H
#define CSPRITE_H

#include "CRect.h"
#include "CTexture.h"

class CSprite : public CRect {
public:
	CTexture *mpTexture;

	CSprite();
	CSprite(float x, float y, float w, float h, float r, CTexture *ptexture);

	//x:X���W y:Y���W w:�� h:���� r:��] ptexture:�e�N�X�`���ւ̃|�C���^
	void Set(float x, float y, float w, float h, float r, CTexture *ptexture);
	void Set(CTexture *ptexture);

	void Render();
	void Render(int uleft, int uright, int ubottom, int utop);

};


#endif
