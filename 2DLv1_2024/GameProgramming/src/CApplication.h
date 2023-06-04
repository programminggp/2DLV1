#pragma once
#include "glut.h"
//
//クラスの宣言
//
class CApplication;
class CRect;

//
//クラスの定義
//
class CRect
{
public:
	void Render();
};

void CRect::Render()
{
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(400.0f, 0.0f);
	glVertex2f(400.0f, 300.0f);
	glVertex2f(0.0f, 300.0f);
	glEnd();
}


class CApplication
{
public:
	//最初に一度だけ実行するメソッド
	void Start();
	//繰り返し実行するメソッド
	void Update();
	//デストラクタ
	~CApplication();
private:
	CRect* mpRect;
};

void CApplication::Start()
{
	mpRect = new CRect();
}

void CApplication::Update()
{
	mpRect->Render();
}

CApplication::~CApplication()
{
	delete mpRect;
}
