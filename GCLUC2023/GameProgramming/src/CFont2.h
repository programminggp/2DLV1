#pragma once
#include "CTexture.h"

class CFont2
{
private:
	CTexture mTexture;
public:
	//�R���X�g���N�^
	CFont2();
	//�f�X�g���N�^
	~CFont2();

	//Load(�t�@�C����, �s��, ��)
	void Load(const char* file, int row, int col);
	//Draw(X���W, Y���W, ��, ����, ����)
	void Draw(float x, float y, float w, float h, char c);
	//Draw(X���W, Y���W, ��, ����, ������)
	void Draw(float x, float y, float w, float h, char c[]);

	//�X�V����
	void Update();
};
