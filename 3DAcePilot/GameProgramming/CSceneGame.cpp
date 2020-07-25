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
//
#include "CCollisionManager.h"
//
#include "CCamera.h"
//ビルボードクラスのインクルード
#include "CBillBoard.h"
#include "CEffect.h"
//空軍基地
#include "CAirBase.h"
//
#include "CText.h"
//
#include "CRes.h"
//
#include "CC5.h"
//
#include "CObj.h"

//モデルクラスのインスタンス作成
CModel Model;
CModel BackGround; //背景モデル
CModel ModelEnemy;//エネミーモデル
CModel ModelAirBase;//空軍基地モデル

//スマートポインタの生成
std::shared_ptr<CTexture> TextureExp(new CTexture());

CSceneGame::~CSceneGame() {
//	delete[] mpEnemyPoint;
}

void CSceneGame::Init() {
	//ミサイル
	CRes::sMissileM.Load("missile.obj", "missile.mtl");
	//C5輸送機
	CRes::sC5.Load("c5.obj", "c5.mtl");
	//モデルファイルの入力
	Model.Load("f14.obj", "f14.mtl");
	BackGround.Load("sky.obj", "sky.mtl");

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//ポイントの設定
	//CEnemy::mPointSize = 3;//ポイント数の設定
	//mpEnemyPoint = new CPoint[CEnemy::mPointSize];
	//mpEnemyPoint[0].Set(CVector(35.0f, 25.0f, 100.0f), 10.0f);
	//mpEnemyPoint[1].Set(CVector(35.0f, 5.0f, 0.0f), 10.0f);
	//mpEnemyPoint[2].Set(CVector(-35.0f, 45.0f, 50.0f), 10.0f);
	//CEnemy::mPoint = mpEnemyPoint;


	//キャラクタの設定
	Player.mpModel = &Model;
	//スケールを0.2倍を変更
	Player.mScale = CVector(0.1f, 0.1f, 0.1f);
	//位置(0.0, 0.0, 55.0)にする
//	Player.mPosition = CVector(-20.0f, 30.0f, -100.0f);
	Player.mPosition = CVector(-20.0f, 30.0f, 400.0f);
	Player.mRotation.mY = 180.0f;

	//エネミーモデルの入力
//	ModelEnemy.Load("f16.obj", "f16.mtl");

	//敵機の生成
	//爆発テクスチャの読み込み
	TextureExp->Load("exp.tga");

	//空軍基地モデルの読み込み
//	ModelAirBase.Load("airbase.obj", "airbase.mtl");
	//空軍基地クラスのインスタンスを生成
//	mpAirBase = new CAirBase(&ModelAirBase, CVector(0.0f, 0.0f, 180.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CObj(&BackGround, CVector(), CVector(), CVector(2.0f, 2.0f, 2.0f));

	CC5 *cc5;
	cc5 = new CC5(&CRes::sC5, CVector(-100.0f, 10.0f, 400.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));
	cc5 = new CC5(&CRes::sC5, CVector(50.0f, 50.0f, 450.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));

}


void CSceneGame::Update() {
	//static変数の作成
	//static int degree = 0;//回転角度の作成
	//degree++;//角度に1加算

	////static変数の作成
	static int frame = 0;//フレーム数のカウント
	frame++;//フレーム数に1加算
	//if (frame < 1000 && frame % 150 == 0) {
	//	//敵機の生成
	//	new CEnemy(&ModelEnemy, CVector(-10.0f, 7.0f, 200.0f), CVector(0.0f, 180.0f, -30.0f), CVector(0.2f, 0.2f, 0.2f));
	//}

	//タスクマネージャの更新
	TaskManager.Update();

	//描画処理

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(-2.0f, 5.0f, -22.0f) * Player.mMatrix;
	//注視点を求める
	c = CVector(0.0f, 4.0f, 0.0f) * Player.mMatrix;
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * Player.mMatrixRotate;
	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	//コリジョンマネージャの衝突処理
	CollisionManager.Collision();

	//タスクリストの削除
	TaskManager.Delete();
	//タスクマネージャの描画
	TaskManager.Render();
	//コライダの描画
//	CollisionManager.Render();

	//2D描画開始
	Start2D(0, 800, 0, 600);

	if (frame < 150) {
		//2D描画
		CText::DrawString("MISSION START", 170, 400, 20, 20);
	}

//	CText::DrawString("PLAYER DAMAGE ", 20, 50, 10, 12);
	CText::DrawString("SPACE:SHOT", 20, 50, 8, 12);
	CText::DrawString("W:DOWN S:UP A:LEFT D:RIGHT I:SPEEDUP K:SPEEDDOWN", 20, 20, 8, 12);

	//2D描画終了
	End2D();

	//ミニマップ描画
//	RenderMiniMap();

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

	BackGround.Render(CMatrix());
	//タスクマネージャの描画
	TaskManager.Render();


	glPopMatrix();
	glViewport(0, 0, 800, 600); //画面の描画エリアの指定

	glEnable(GL_DEPTH_TEST);
}

