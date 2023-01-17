#include "CInput.h"
GLFWwindow* CInput::spWindow = nullptr;//ウィンドウのポインタ
int CInput::sWheel = 0;	//ホイールの値

void CInput::Window(GLFWwindow* pwindow)
{
	//ウィンドウポインタの保存
	spWindow = pwindow;
	//コースバック関数の登録
	glfwSetScrollCallback(spWindow, CInput::MouseScrollCB);
}

void CInput::GetMousePosWin(float* px, float* py)
{
	double xpos, ypos;
	//マウスカーソル座標の取得
	glfwGetCursorPos(spWindow, &xpos, &ypos);
	*px = (float)xpos;
	*py = (float)ypos;
	return;
}

void CInput::SetMousePosWin(float px, float py)
{
	//マウスカーソル座標の設定
	glfwSetCursorPos(spWindow, px, py);
	return;
}
void CInput::GetMousePosDisp(int* px, int* py)
{
	POINT point;
	//WindowsAPI　マウスカーソル座標の取得
	GetCursorPos(&point);
	*px = point.x;
	*py = point.y;
}

void CInput::SetMousePosDisp(int x, int y)
{
	//WindowsAPI　マウスカーソル座標の設定
	SetCursorPos(x, y);
}

//マウスホイールに変化があると呼ばれるコールバック関数
void CInput::MouseScrollCB(GLFWwindow* window, double x, double y)
{
	sWheel = (int)y;
}

int CInput::Wheel()
{
	int r = sWheel;
	sWheel = 0;
	return r;
}
