#include <Windows.h>
#include "CMain.h"
#include "CLight.h"
#include "main.h"
#include "GLFW/glfw3.h"

CMatrix44 GMatrixViewport;
CMatrix44 GMatrixProjection;
CMatrix44 GMatrixModelView;

/*
Return Screen Position
(0,600) Left-Top (800,600) Right-Top
(0,0) Left-Bottom (800,0) Right-Bottom
*/
CVector3 WorldToViewportPoint(const CVector3 &v) {
	CVector4 vector;
	vector.x = v.x;
	vector.y = v.y;
	vector.z = v.z;
	vector = vector * GMatrixModelView  * GMatrixProjection;
	CVector3 vector3 = vector / vector.z;
	vector3.z = vector.z;
	return vector3 * GMatrixViewport;
}

CMain Main;

/* display関数
1秒間に60回実行される
*/
void display() {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Main.loop();
}

//関数のプロトタイプ宣言
void reshape(GLFWwindow* window, int, int);
void idle();

int main(int argc, char* argv[]) {

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(WINDOW_W, WINDOW_H, "Hello 3DProgramming", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// GLEW を初期化する
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// ウィンドウのサイズ変更時に呼び出す処理の登録
	reshape(window, WINDOW_W, WINDOW_H);

	glfwSetFramebufferSizeCallback(window, reshape);

	//メッシュシェーダー用
//	CLight::getLight(0)->setDir(CVector3(LIGHT_SET_DIR).normalize());
	CLight::getLight(0)->setPosition(CVector3(LIGHT_POS));
	CLight::getLight(0)->setColor(CVector3(LIGHT_SET_AMB), CVector3(LIGHT_SET_COL));

	//ライトの設定
	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static const GLfloat lightPosition[3] = { LIGHT_POS }; //光源の位置
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	static const GLfloat lightamb[] = { LIGHT_SET_AMB, 1.0 }; /* 環境光強度　　　　 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
	static const GLfloat lightdiff[] = { LIGHT_SET_COL, 1.0 }; /* 環境光強度　　　　 */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiff);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		idle();

		/*window座標取得*/
//		glfwGetWindowPos(window, &WinPosX, &WinPosY);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
bool ProjectionFlg = true;
/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);	//画面の描画エリアの指定

	glMatrixMode(GL_PROJECTION);		//行列をプロジェクションモードへ変更
	glLoadIdentity();
	gluPerspective(75.0, (double)width / (double)height, ZNEAR, ZFAR);
	if (ProjectionFlg) {
		GMatrixViewport.m[0][0] = width / 2;
		GMatrixViewport.m[1][1] = height / 2;
		//
		GMatrixViewport.m[2][2] = (ZFAR - ZNEAR) / 2.0f;
		GMatrixViewport.m[3][0] = width / 2;
		GMatrixViewport.m[3][1] = height / 2;
		//
		GMatrixViewport.m[3][2] = (ZNEAR + ZNEAR) / 2.0f;
		//
		GMatrixViewport.m[3][3] = 1;
		glGetFloatv(GL_PROJECTION_MATRIX, GMatrixProjection.f);
		ProjectionFlg = false;
	}

	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();

	//GMatrixProjection.m[0][0] = 2 * ZNEAR / width;
	//GMatrixProjection.m[1][1] = 2 * ZNEAR / height;
	//GMatrixProjection.m[2][2] = -(ZFAR + ZNEAR) / (ZFAR - ZNEAR);
	//GMatrixProjection.m[2][3] = -1;
	//GMatrixProjection.m[3][2] = -2 * ZNEAR * ZFAR / (ZFAR - ZNEAR);
	//GMatrixProjection.m[3][3] = 0;

}

LARGE_INTEGER last_time;	//前回のカウンタ値
//１秒間に６０回描画するように調節する
void idle() {
	LARGE_INTEGER freq;		//一秒当たりのカウンタ数
	LARGE_INTEGER time;		//今回のカウンタ値

	//一秒間のカウンタ数を取得
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time);

		//今のカウント-前回のカウント < 1秒当たりのカウント数を60で割る(1/60秒当たりのカウント数)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//描画する関数を呼ぶ
	display();
}
