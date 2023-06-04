#pragma once
//
//インクルード
//
#include <stdio.h>
#include "glut.h"

//
//クラスの宣言
//

//CApplicationクラスの宣言
class CApplication;
//CRectクラスの宣言
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
private:
	//変数の宣言
	float mX;
	float mY;
	float mW;
	float mH;
};

//四角形クラスの描画処理の定義
void CRect::Render()
{
	//変数の代入
	mX = 400.0f;
	mY = 300.0f;
	mW = 200.0f;
	mH = 150.0f;
	//画面に四角形を描画する
	glBegin(GL_QUADS);
	glVertex2f(mX - mW, mY - mH);
	glVertex2f(mX + mW, mY - mH);
	glVertex2f(mX + mW, mY + mH);
	glVertex2f(mX - mW, mY + mH);
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
	//printf("Start\n");
	//インスタンスの生成
	mpRect = new CRect();
}

void CApplication::Update()
{
	//printf("Update\n");
	//メソッドの呼び出し
	mpRect->Render();
}

//CApplicationの終了時に実行
CApplication::~CApplication()
{
	//インスタンスの削除
	delete mpRect;
}
