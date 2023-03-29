#include "CFont2.h"

//�R���X�g���N�^
CFont2::CFont2()
{
}

//�f�X�g���N�^
CFont2::~CFont2()
{
}

void CFont2::Load(const char* file, int row, int col)
{
	mTexture.Load(file);
	mTexture.SetRowCol(row, col);
}

void CFont2::Draw(float x, float y, float w, float h, char c)
{
	int i = c - 0x20;
	mTexture.DrawImage(x - w, x + w, y - h, y + h, i);
}

void CFont2::Draw(float x, float y, float w, float h, char c[])
{
	for (int i = 0; c[i] != '\0'; i++)
	{
		Draw(x, y, w, h, c[i]);
		x += w * 2;
	}
	return;
}

//�X�V����
void CFont2::Update()
{
}