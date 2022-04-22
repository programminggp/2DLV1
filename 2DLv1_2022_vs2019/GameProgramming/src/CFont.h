#pragma once
#include "CTexture.h"

class CFont
{
private:
	CTexture mTexture;
public:
	void Load(const char* file, int row, int col);
	void Draw(float x, float y, float w, float h, char c);
};