#include "CSceneGame.h"
//OpenGL
#include "glut.h"
//CVectorクラスのインクルード
#include "CVector.h"
//CMatrixクラスのインクルード
#include "CMatrix.h"
//CTriangleクラスのインクルード
#include "CTriangle.h"
//数学関数のインクルード
#include <math.h>
//モデルクラスのインクルード
#include "CModel.h"
//キャラクタクラスのインクルード
#include "CCharacter.h"
//プレイヤークラスのインクルード
#include "CPlayer.h"
//タスクマネージャのインクルード
#include "CTaskManager.h"
//エネミークラスのインクルード
#include "CEnemy.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CEffect.h"
#include "CText.h"
#include "CRes.h"
#include "CC5.h"
#include "CObj.h"
#include "CKey.h"

//モデルクラスのインスタンス作成
CModel F14;
CModel Sky; //背景モデル
CModel F16;//エネミーモデル
CModel C5;

//スマートポインタの生成
std::shared_ptr<CTexture> TextureExp(new CTexture());

CSceneGame::~CSceneGame() {
}

void CSceneGame::Init() {
	//ミサイル
	CRes::sMissileM.Load("missile.obj", "missile.mtl");
	//爆発テクスチャの読み込み
	TextureExp->Load("exp.tga");
	//モデルファイルの入力
	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//1
	//背景モデルの生成
	Sky.Load("sky.obj", "sky.mtl");
	new CObj(&Sky, CVector(), CVector(), CVector(2.0f, 2.0f, 2.0f));

	//2
	//プレイヤーの設定
	F14.Load("f14.obj", "f14.mtl");
	Player.mpModel = &F14;
	Player.mScale = CVector(0.1f, 0.1f, 0.1f);

	//6
	//C5輸送機の生成
	C5.Load("c5.obj", "c5.mtl");
	new CC5(&C5, CVector(-100.0f, 10.0f, 300.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));

	//11
	//敵機の生成
	F16.Load("f16.obj", "f16.mtl");
	new CEnemy(&F16, CVector(-100.0f, 20.0f, 350.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.2f, 0.2f, 0.2f));
	new CEnemy(&F16, CVector(100.0f, 20.0f, 250.0f), CVector(0.0f, 180.0f, 0.0f), CVector(0.2f, 0.2f, 0.2f));

	//12
	//輸送機追加
	new CC5(&C5, CVector(50.0f, 50.0f, 380.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));
}


void CSceneGame::Update() {
	////static変数の作成
	static int frame = 0;//フレーム数のカウント
	frame++;

	//タスクマネージャの更新
	TaskManager.Update();
	//コリジョンマネージャの衝突処理
	CollisionManager.Collision();
	//タスクリストの削除
	TaskManager.Delete();

	//描画処理

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向

	//5
	//カメラのパラメータを設定する
	e = CVector(-2.0f, 5.0f, -22.0f) * CMatrix().Scale(0.3f, 0.5f, 0.36f);
	c = CVector(0.0f, 4.0f, 0.0f);
	u = CVector(0.0f, 1.0f, 0.0f);
	
	if (CKey::Push('U'))
	{
		e = CVector(-2.0f, 5.0f, 22.0f) * Player.mMatrix;
	}
	else
	{
		e = CVector(-2.0f, 5.0f, -22.0f) * Player.mMatrix;
	}
	c = CVector(0.0f, 4.0f, 0.0f) * Player.mMatrix;
	u = CVector(0.0f, 1.0f, 0.0f) * Player.mMatrixRotate;
	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	//タスクマネージャの描画
	TaskManager.Render();

	//2D描画開始
	Start2D(0, 800, 0, 600);

	if (frame < 150) {
		//2D描画
		CText::DrawString("MISSION START", 170, 400, 20, 20);
	}

	CText::DrawString("SPACE:SHOT M:MISSIL", 20, 50, 8, 12);
	CText::DrawString("W:DOWN S:UP A:LEFT D:RIGHT I:SPEEDUP K:SPEEDDOWN", 20, 20, 8, 12);

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

/*マップ上からの視点*/
void CSceneGame::RenderMiniMap() {

	glPushMatrix();
	glViewport(600, 450, 200, 150); //画面の描画エリアの指定
	glLoadIdentity();
	gluLookAt(0, 100, 0, 0, 0, 0, 0, 0, 1);

	glDisable(GL_DEPTH_TEST);

	Sky.Render(CMatrix());
	//タスクマネージャの描画
	TaskManager.Render();


	glPopMatrix();
	glViewport(0, 0, 800, 600); //画面の描画エリアの指定

	glEnable(GL_DEPTH_TEST);
}

