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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	GL gl;

	gl.Update();

	return 0;
}

