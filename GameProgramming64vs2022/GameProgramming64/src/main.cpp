#include <Windows.h>
#include <stdio.h>
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "GLFW/glfw3.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Hello World"
//#define FULL_SCREEN

class GL;
class Application;


#include "CSceneManager.h"

//シーンマネージャのインスタンス
CSceneManager SceneManager;

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
	//シーンマネージャの初期化
	SceneManager.Init();
}
//Update関数
//プログラムの実行中、繰り返し呼ばれる関数
void Update() {
	//シーンマネージャの更新
	SceneManager.Update();
}

class Application
{
	//シーンマネージャのインスタンス
	CSceneManager SceneManager;
public:
	void Start()
	{
		SceneManager.Init();
	}

	void Update()
	{
		SceneManager.Update();
	}
};



class GL
{
public:
	GL()
		: pWindow(nullptr)
		, fpsCounter(0.0)
	{
		//glutInit(&argc, argv);

		/* Initialize the library */
		if (!glfwInit())
			return;

		/* Create a windowed mode window and its OpenGL context */
#ifndef FULL_SCREEN
		pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
#else
	//Full Screen
		pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, glfwGetPrimaryMonitor(), NULL);
#endif
		if (!pWindow)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(pWindow);


		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

		// GLEW を初期化する
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			// GLEW の初期化に失敗した
			printf("Can't initialize GLEW\n");
	//		std::cerr << "Can't initialize GLEW" << std::endl;
			return;
		}
		// 垂直同期のタイミングを待つ  
		//glfwSwapInterval(1); 


		glEnable(GL_DEPTH_TEST);	//3D必要 2D不要
		glEnable(GL_CULL_FACE);

		// ウィンドウのサイズ変更時に呼び出す処理の登録
		glfwSetWindowSizeCallback(pWindow, reshape);
		reshape(pWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

		//ライトの設定（3D必要 2D不要）
		//固定シェーダー用
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		float lightPosition[] = { 0.0f, 100.0f, 100.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		glEnable(GL_NORMALIZE);

		//メッシュシェーダー用
	//	CLight::getLight(0)->setDir(CVector3(0, -1, 1).GetNormalize());
	//	CLight::getLight(0)->setColor(CVector3(0.9f, 0.9f, 0.9f), CVector3(1.0f, 1.0f, 1.0f));

	}

	void Update()
	{
		application.Start();
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(pWindow))
		{

			idle();

			/* Swap front and back buffers */
			glfwSwapBuffers(pWindow);

			/* Poll for and process events */
			glfwPollEvents();

			int state = glfwGetKey(pWindow, GLFW_KEY_ESCAPE);
			if (state == GLFW_PRESS) {
				//ESCキーでループ終了
				break;
			}
		}

		glfwTerminate();
	}

private:
	GLFWwindow* pWindow;
	double fpsCounter;
	Application application;

	void idle()
	{
		double time;
		do
		{
			time = glfwGetTime();
		} while (fpsCounter > time);
		fpsCounter = time + 1.0 / 60.0;
		display();
	}

	void display()
	{
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//行列のモードをモデルビューにする
		glMatrixMode(GL_MODELVIEW);
		//モデルビューの行列を単位行列にする
		glLoadIdentity();

		application.Update();
	}

	static void reshape(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);	//画面の描画エリアの指定
		glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
		glLoadIdentity();				//行列を初期化
		//	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2Dの画面を設定
		gluPerspective(75.0, (double)width / (double)height, 1.0, 10000.0);	//3Dの画面を設定

		//glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
		//glLoadIdentity();				//行列を初期化
	}

};


bool InitFlg = true;

/* display関数
1秒間に60回実行される
*/
void display() {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();

	if (InitFlg) {
		Init();
		InitFlg = false;
	}
	else {
		Update();
	}

}


/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);	//画面の描画エリアの指定
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
//	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2Dの画面を設定
	gluPerspective(75.0, (double)width / (double)height, 1.0, 10000.0);	//3Dの画面を設定

	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化
}
//
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

double sNextTime = 1.0/60.0;
void Idle()
{
	double time;
	do
	{
		time = glfwGetTime();
	} while (sNextTime > time);
	sNextTime = time + 1.0 / 60.0;
	display();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	GL gl;

	gl.Update();


	return 0;



	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
#ifndef FULL_SCREEN
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
#else
	//Full Screen
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", glfwGetPrimaryMonitor(), NULL);
#endif
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	// GLEW を初期化する
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		// GLEW の初期化に失敗した
//		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}
	// 垂直同期のタイミングを待つ  
	//glfwSwapInterval(1); 


	glEnable(GL_DEPTH_TEST);	//3D必要 2D不要
	glEnable(GL_CULL_FACE);

	// ウィンドウのサイズ変更時に呼び出す処理の登録
	glfwSetWindowSizeCallback(window, reshape);
	reshape(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	//ライトの設定（3D必要 2D不要）
	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float lightPosition[] = {0.0f, 100.0f, 100.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_NORMALIZE);

	//メッシュシェーダー用
//	CLight::getLight(0)->setDir(CVector3(0, -1, 1).GetNormalize());
//	CLight::getLight(0)->setColor(CVector3(0.9f, 0.9f, 0.9f), CVector3(1.0f, 1.0f, 1.0f));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		Idle();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (state == GLFW_PRESS) {
			//ESCキーでループ終了
			break;
		}
	}

	glfwTerminate();
	return 0;
}
