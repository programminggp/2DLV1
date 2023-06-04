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
//四角形クラスの定義
class CRect
{
public:
	//メソッドの宣言
	//描画処理
	void Render();
};

//四角形クラスの描画処理の定義
void CRect::Render()
{
	//画面に四角形を描画する
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
	//インスタンス変数の宣言
	CRect* mpRect;
};

void CApplication::Start()
{
	//インスタンスの生成
	mpRect = new CRect();
}

void CApplication::Update()
{
	//メソッドの呼び出し
	mpRect->Render();
}

CApplication::~CApplication()
{
	//インスタンスの削除
	delete mpRect;
}
