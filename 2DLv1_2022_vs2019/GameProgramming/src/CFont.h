#pragma once
#include "CTexture.h"

class CFont
{
private:
	CTexture mTexture;
public:
	//Load(�t�@�C����, �s��, ��)
	void Load(const char* file, int row, int col);
	//Draw(X���W, Y���W, ��, ����, ����)
	void Draw(float x, float y, float w, float h, char c);
	//Draw(X���W, Y���W, ��, ����, ������)
	void Draw(float x, float y, float w, float h, char c[]);
};