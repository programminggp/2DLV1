#include "CMain.h"
//#include "CTask.h"
#include "CCamera.h"

//////////////////////////////WinInet http connection
#include <windows.h>
#include <Wininet.h>

#include <assert.h>
#include <string>
#include <sstream>
#include <locale.h>
#include <conio.h>
//#include "NhConversion.h"

#pragma comment( lib, "Wininet.lib" )

typedef std::basic_string<TCHAR>		tstring;
typedef std::basic_stringstream<TCHAR>	tstringstream;

#define URLBUFFER_SIZE		(4096)
#define	READBUFFER_SIZE		(4096)

bool HttpRequest(tstring strUserAgent,
	tstring strUrl,
	bool bIsHttpVerbGet,
	tstring strParameter,
	tstring& rstrResult)
{
	// アウトプットの初期化
	rstrResult = tstring();

	// インプットのチェック
	if (0 == strUrl.length())
	{
		assert(!"URLが不正");
		return false;
	}

	// 変数
	HINTERNET			hInternetOpen = NULL;
	HINTERNET			hInternetConnect = NULL;
	HINTERNET			hInternetRequest = NULL;
	char*				pszOptional = NULL;
	URL_COMPONENTS		urlcomponents;
	tstring				strServer;
	tstring				strObject;
	INTERNET_PORT		nPort;
	tstring				strVerb;
	tstring				strHeaders;
	tstringstream		ssRead;

	// URL解析
	ZeroMemory(&urlcomponents, sizeof(URL_COMPONENTS));
	urlcomponents.dwStructSize = sizeof(URL_COMPONENTS);
	TCHAR szHostName[URLBUFFER_SIZE];
	TCHAR szUrlPath[URLBUFFER_SIZE];
	urlcomponents.lpszHostName = szHostName;
	urlcomponents.lpszUrlPath = szUrlPath;
	urlcomponents.dwHostNameLength = URLBUFFER_SIZE;
	urlcomponents.dwUrlPathLength = URLBUFFER_SIZE;
	if (!InternetCrackUrl(strUrl.c_str(),
		(DWORD)strUrl.length(),
		0,
		&urlcomponents))
	{	// URLの解析に失敗
		assert(!"URL解析に失敗");
		return false;
	}
	strServer = urlcomponents.lpszHostName;
	strObject = urlcomponents.lpszUrlPath;
	nPort = urlcomponents.nPort;

	// HTTPかHTTPSかそれ以外か
	DWORD dwFlags = 0;
	if (INTERNET_SCHEME_HTTP == urlcomponents.nScheme)
	{	// HTTP
		dwFlags = INTERNET_FLAG_RELOAD				// 要求されたファイル、オブジェクト、またはフォルダ一覧を、キャッシュからではなく、元のサーバーから強制的にダウンロードします。
			| INTERNET_FLAG_DONT_CACHE			// 返されたエンティティをキャシュへ追加しません。
			| INTERNET_FLAG_NO_AUTO_REDIRECT;	// HTTP だけで使用され、リダイレクトが HttpSendRequest で処理されないことを指定します。
	}
	else if (INTERNET_SCHEME_HTTPS == urlcomponents.nScheme)
	{	// HTTPS
		dwFlags = INTERNET_FLAG_RELOAD				// 要求されたファイル、オブジェクト、またはフォルダ一覧を、キャッシュからではなく、元のサーバーから強制的にダウンロードします。
			| INTERNET_FLAG_DONT_CACHE			// 返されたエンティティをキャシュへ追加しません。
			| INTERNET_FLAG_NO_AUTO_REDIRECT	// HTTP だけで使用され、リダイレクトが HttpSendRequest で処理されないことを指定します。
			| INTERNET_FLAG_SECURE						// 安全なトランザクションを使用します。これにより、SSL/PCT を使うように変換され、HTTP 要求だけで有効です。 
			| INTERNET_FLAG_IGNORE_CERT_DATE_INVALID	// INTERNET_FLAG_IGNORE_CERT_DATE_INVALID、INTERNET_FLAG_IGNORE_CERT_CN_INVALID
			| INTERNET_FLAG_IGNORE_CERT_CN_INVALID;		// は、証明書に関する警告を無視するフラグ
	}
	else
	{
		assert(!"HTTPでもHTTPSでもない");
		return false;
	}

	// GETかPOSTか
	if (bIsHttpVerbGet)
	{	// GET
//		strVerb = _T("GET");
		strVerb = ("GET");
//		strHeaders = _T("");
		strHeaders = ("");
		if (0 != strParameter.length())
		{	// オブジェクトとパラメータを「?」で連結
//			strObject += _T("?") + strParameter;
			strObject += ("?") + strParameter;
		}
	}
	else
	{	// POST
//		strVerb = _T("POST");
		strVerb = ("POST");
//		strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
		strHeaders = ("Content-Type: application/x-www-form-urlencoded");
		if (0 != strParameter.length())
		{	// パラメータを、送信するオプションデータに変換する
//			pszOptional = NhT2M(strParameter.c_str());	// char文字列に変換
			pszOptional = (char *)(strParameter.c_str());	// char文字列に変換
		}
	}

	// WinInetの初期化
	hInternetOpen = InternetOpen(strUserAgent.c_str(),
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, 0);
	if (NULL == hInternetOpen)
	{
		assert(!"WinInetの初期化に失敗");
		goto LABEL_ERROR;
	}

	// HTTP接続
	hInternetConnect = InternetConnect(hInternetOpen,
		strServer.c_str(),
		nPort,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		0,
		0);
	if (NULL == hInternetConnect)
	{
		assert(!"HTTP接続に失敗");
		goto LABEL_ERROR;
	}

	// HTTP接続を開く
	hInternetRequest = HttpOpenRequest(hInternetConnect,
		strVerb.c_str(),
		strObject.c_str(),
		NULL,
		NULL,
		NULL,
		dwFlags,
		NULL);
	if (NULL == hInternetRequest)
	{
		assert(!"HTTP接続を開くに失敗");
		goto LABEL_ERROR;
	}

	// HTTP要求送信
	if (!HttpSendRequest(hInternetRequest,
		strHeaders.c_str(),
		(DWORD)strHeaders.length(),
		(LPVOID)((char*)pszOptional),
		pszOptional ? (DWORD)(strlen(pszOptional) * sizeof(char)) : 0))
	{
		assert(!"HTTP要求送信に失敗");
		goto LABEL_ERROR;
	}

	// HTTP要求に対応するステータスコードの取得
	DWORD dwStatusCode;
	DWORD dwLength = sizeof(DWORD);
	if (!HttpQueryInfo(hInternetRequest,
		HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
		&dwStatusCode,
		&dwLength,
		0))
	{
		assert(!"HTTP要求に対応するステータスコードの取得に失敗");
		goto LABEL_ERROR;
	}
	if (HTTP_STATUS_OK != dwStatusCode)
	{
		assert(!"ステータスコードがOKでない");
		goto LABEL_ERROR;
	}

	// HTTPファイル読み込み
	char szReadBuffer[READBUFFER_SIZE + 1];
	while (1)
	{
		DWORD dwRead = 0;
		if (!InternetReadFile(hInternetRequest, szReadBuffer, READBUFFER_SIZE, &dwRead))
		{
			assert(!"HTTPファイル読み込みに失敗");
			goto LABEL_ERROR;
		}
		if (0 == dwRead)
		{
			break;
		}
		szReadBuffer[dwRead] = '\0';	// 終端文字「\0」の付加
		size_t length = dwRead + 1;
//		LPWSTR	pszWideChar = (LPWSTR)malloc(length * sizeof(WCHAR));
		//MultiByteToWideChar(CP_UTF8,	// CODE PAGE: UTF-8
		//	0,
		//	szReadBuffer,
		//	-1,
		//	pszWideChar,
		//	(int)length);	// UTF-8文字列をANSI文字列に変換
//		TCHAR* pszTchar = NhW2T(pszWideChar);	// WideChar文字列をTCHAR文字列に変換
//		TCHAR* pszTchar = (TCHAR*)(pszWideChar);	// WideChar文字列をTCHAR文字列に変換
//		ssRead << pszTchar;	// ストリーム文字列に流し込む
		ssRead << szReadBuffer;	// ストリーム文字列に流し込む
//		free(pszTchar);
//		free(pszWideChar);
	}

	// ストリーム文字列を、出力文字列に変換
	rstrResult = ssRead.str().c_str();

	if (pszOptional){ free(pszOptional); }
	InternetCloseHandle(hInternetRequest);
	InternetCloseHandle(hInternetConnect);
	InternetCloseHandle(hInternetOpen);
	return true;

LABEL_ERROR:
	if (pszOptional){ free(pszOptional); }
	InternetCloseHandle(hInternetRequest);
	InternetCloseHandle(hInternetConnect);
	InternetCloseHandle(hInternetOpen);
	return false;
}




/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape2D(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);	//画面の描画エリアの指定
	CCamera camera;
	camera.Camera2D(0.0f, 0.0f, width / 2.0f, height / 2.0f);
	//glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	//glLoadIdentity();				//行列を初期化
	//gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2Dの画面を設定
	////	gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);	//3Dの画面を設定

	//glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	//glLoadIdentity();				//行列を初期化
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
//	CTaskManager::Get()->Destroy();
	glfwTerminate();
	if (mpScene) {
		delete mpScene;
		mpScene = 0;
	}
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

//	CTaskManager::Get()->Update();
	mpScene->Update();
//	CTaskManager::Get()->Collision();
//	CTaskManager::Get()->Remove();
//	CTaskManager::Get()->Render();
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
/////////////////////////////////////////////////////////////////
//	tstring strUserAgent = _T("HttpRequestTest");
	tstring strUserAgent = ("HttpRequestTest");
//	tstring strUrl = _T("http://weather.livedoor.com/forecast/webservice/json/v1");
	tstring strUrl = ("http://gama-programming-jp.jupk2ppz9p.us-west-2.elasticbeanstalk.com/");
	bool bIsHttpVerbGet = true;
//	tstring strParameter = _T("city=400040");
	tstring strParameter = ("city=400040");

	tstring strResult;

	goto Skip;

	if (!HttpRequest(strUserAgent,
		strUrl,
		bIsHttpVerbGet,
		strParameter,
		strResult))
	{
		return false;
	}

	setlocale(LC_ALL, "Japanese");
//	_tprintf(_T("%s"), strResult.c_str());
	printf("%s", strResult.c_str());
////////////////////////////////////////////////////
Skip:
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
