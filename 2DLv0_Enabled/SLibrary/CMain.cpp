#include "CMain.h"
#include "CTask.h"



/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape2D(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);	//画面の描画エリアの指定
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2Dの画面を設定
	//	gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);	//3Dの画面を設定

	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化
}


CMain::CMain() 
	: mpScene(0)
{
//	last_time.QuadPart = 0;
	//一秒間のカウンタ数を取得
	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&last_time);
}

CMain::~CMain() {
	CTaskManager::Get()->Destroy();
	glfwTerminate();
}

#include <stdio.h>
int CMain::Init2D(int width, int height) {
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Programming GP", NULL, NULL);
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
		// GLEW の初期化に失敗した
		//		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}
	// 垂直同期のタイミングを待つ  
	//glfwSwapInterval(1); 


	//	glEnable(GL_DEPTH_TEST);	//3D必要 2D不要
	glEnable(GL_CULL_FACE);

	// ウィンドウのサイズ変更時に呼び出す処理の登録
	glfwSetWindowSizeCallback(window, reshape2D);
	reshape2D(window, width, height);

	//ライトの設定（3D必要 2D不要）
	//固定シェーダー用
	//	glEnable(GL_LIGHTING);
	//	glEnable(GL_LIGHT0);
	//メッシュシェーダー用
	//	CLight::getLight(0)->setDir(CVector3(0, -1, 1).GetNormalize());
	//	CLight::getLight(0)->setColor(CVector3(0.9f, 0.9f, 0.9f), CVector3(1.0f, 1.0f, 1.0f));

	printf("Copyright 2019 Programming GP\n");

	return 0;
}

/* display関数
1秒間に60回実行される
*/
void CMain::display() {

	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();

	CTaskManager::Get()->Update();
	mpScene->Update();
	CTaskManager::Get()->Collision();
	CTaskManager::Get()->Remove();
	CTaskManager::Get()->Render();
	mpScene->Render();
}

//１秒間に６０回描画するように調節する
void CMain::idle() {

	//一秒間のカウンタ数を取得
	//QueryPerformanceFrequency(&freq);

	//if (last_time.QuadPart == 0) {
	//	QueryPerformanceCounter(&last_time);
	//}
	do{
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time);

		//今のカウント-前回のカウント < 1秒当たりのカウント数を60で割る(1/60秒当たりのカウント数)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//描画する関数を呼ぶ
	display();
}

int CMain::Main2D(CScene* pscene)
{
	mpScene = pscene;

	mpScene->Init();
	//mScene.Init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		idle();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

//	CTaskManager::Get()->Destroy();

//	delete mpScene;

//	glfwTerminate();

	return 0;
}
