#include "CApplication.h"
#include <stdio.h> //printf関数のインクルード

//四角形クラスの宣言
class CRect;

//四角形クラスの定義
class CRect
{
public:
	void Render(); //Renderメソッドの宣言
};


//Renderメソッドの定義
void CRect::Render()
{
	printf("Render CRect\n"); //文字列の出力
}


void CApplication::Start()
{
	CRect rect; //CRectクラスのインスタンスrectの作成
	rect.Render(); //rectインスタンスのRender()を実行
}

void CApplication::Update()
{

}
