#ifndef CMAIN_H
#define CMAIN_H
#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include "GLFW/glfw3.h"
#include "CScene.h"

//#define WINDOW_WIDTH 800	//ウィンドウの幅
//#define WINDOW_HEIGHT 600	//ウィンドウの高さ

class CMain {
	//
	LARGE_INTEGER last_time;	//前回のカウンタ値
	LARGE_INTEGER freq;		//一秒当たりのカウンタ数
	LARGE_INTEGER time;		//今回のカウンタ値

	/* display関数
	1秒間に60回実行される
	*/
	void display();
	//１秒間に６０回描画するように調節する
	void idle();
	GLFWwindow* window;
	CScene* mpScene;
public:
	static int mWindowWidth;
	static int mWindowHeight;
	CMain();
	virtual ~CMain();
	int Init2D(int width = 800, int height = 600);
	int Main(CScene* pscene);
};

#endif
