#include "CSceneGame.h"
//OpenGL
#include "glut.h"
//
#include "CCamera.h"
//
#include "CText.h"
//
#include "CRes.h"


//スマートポインタの生成
std::shared_ptr<CTexture> TextureExp(new CTexture());

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {
	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//モデルファイルの入力
	CRes::sBackGround.Load("sky.obj", "sky.mtl");
}


void CSceneGame::Update() {
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(-2.0f, 10.0f, -30.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);
	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	CRes::sBackGround.Render(CMatrix());

	//2D描画開始
	Start2D(0, 800, 0, 600);

	CText::DrawString("PLAYER DAMAGE ", 20, 50, 10, 12);
	CText::DrawString("AIRBASE DAMAGE", 20, 20, 10, 12);

	//2D描画終了
	End2D();

	return;
}

//2D描画スタート
//Start2D(左座標, 右座標, 下座標, 上座標)
void CSceneGame::Start2D(float left, float right, float bottom, float top) {
	//モデルビュー行列の退避
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();

	//モデルビュー行列から
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//2D描画の設定
	gluOrtho2D(left, right, bottom, top);
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
}

//2D描画終了
void CSceneGame::End2D() {
	//プロジェクション行列を戻す
	glPopMatrix();
	//モデルビューモードへ切り替え
	glMatrixMode(GL_MODELVIEW);
	//モデルビュー行列を戻す
	glPopMatrix();
	//Depthテストオン
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

}
