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

//モデルクラスのインスタンス作成
CModel Model;
CModel BackGround; //背景モデル

void CSceneGame::Init() {
	CMatrix matrix;
	//平行移動行列の作成
	matrix.Translate(1.0f, 2.0f, 3.0f);
	matrix.Print();
	//モデルファイルの入力
	Model.Load("f14.obj", "f14.mtl");
	BackGround.Load("sky.obj", "sky.mtl");
	//キャラクタの設定
	Character.mpModel = &Model;
	//スケールに1倍を設定
	Character.mScale = CVector(1.0f, 1.0f, 1.0f);
	//キャラクタの設定
	Player.mpModel = &Model;
	//スケールに1倍を設定
//	Player.mScale = CVector(1.0f, 1.0f, 1.0f);
	//スケールを0.2倍を変更
	Player.mScale = CVector(0.2f, 0.2f, 0.2f);
	//位置(0.0, 0.0, 55.0)にする
	Player.mPosition = CVector(0.0f, 0.0f, 55.0f);
}

//22#include "CBullet.h"
//22CBullet Bullet;

void CSceneGame::Update() {
	//static変数の作成
	static int degree = 0;//回転角度の作成
	degree++;//角度に1加算
	//視点の設定
	//gluLookAt(視点X, 視点Y, 視点Z, 中心X, 中心Y, 中心Z, 上向X, 上向Y, 上向Z)
	//gluLookAt(11.0f, 12.0f, 83.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//Y軸で回転させる
	Character.mRotation.mY++;
	//更新処理
//	Character.Update();
//	Player.Update();

	//タスクマネージャの更新
	TaskManager.Update();

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(0.0f, 10.0f, -30.0f) * Player.mMatrix;
	//注視点を求める
	c = Player.mPosition;
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * Player.mMatrixRotate;
	//カメラの設定
	gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//描画処理
//	Character.Render();
//	Player.Render();
	BackGround.Render();

	//タスクリストの削除
	TaskManager.Delete();
	//タスクマネージャの描画
	TaskManager.Render();

	return;

	CMatrix matrix;//行列作成

	//頂点1､頂点2､頂点3,法線データの作成
	CVector v0, v1, v2, n;

	//法線を上向きで設定する
	n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;

	//頂点1の座標を設定する
	v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
	//頂点2の座標を設定する
	v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
	//頂点3の座標を設定する
	v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

	//視点の設定
	//gluLookAt(視点X, 視点Y, 視点Z, 中心X, 中心Y, 中心Z, 上向X, 上向Y, 上向Z)
	gluLookAt(1.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//描画開始
	//glBegin(形)
	//GL_TRIANGLES：三角形
	glBegin(GL_TRIANGLES);

	//Y軸中心に角度だけ回転させる行列を設定
	matrix.RotateY(degree);
	//法線と頂点を回転させる
	//n = n.Multi(matrix);
	v0 = v0.Multi(matrix);
	v1 = v1.Multi(matrix);
	v2 = v2.Multi(matrix);

	//法線（面の向き）の設定
	//glNormal3f(X座標, Y座標, Z座標)
	glNormal3f(n.mX, n.mY, n.mZ);
	//頂点座標の設定
	//glVertex3f(X座標, Y座標, Z座標)
	glVertex3f(v0.mX, v0.mY, v0.mZ);
	glVertex3f(v1.mX, v1.mY, v1.mZ);
	glVertex3f(v2.mX, v2.mY, v2.mZ);

	//法線と頂点の設定
	n.Set(0.0f, 0.0f, 1.0f);
	v0.Set(0.5f, 0.0f, 0.0f);
	v1.Set(0.0f, 1.0f, 0.0f);
	v2.Set(-0.5f, 0.0f, 0.0f);

	matrix.RotateZ(degree);
	//法線と頂点を回転させる
	n = n.Multi(matrix);
	v0 = v0.Multi(matrix);
	v1 = v1.Multi(matrix);
	v2 = v2.Multi(matrix);

	//三角形2の描画
	glNormal3f(n.mX, n.mY, n.mZ);
	glVertex3f(v0.mX, v0.mY, v0.mZ);
	glVertex3f(v1.mX, v1.mY, v1.mZ);
	glVertex3f(v2.mX, v2.mY, v2.mZ);

	//法線と頂点の設定
	n.Set(1.0f, 0.0f, 0.0f);
	v0.Set(0.0f, 0.5f, 0.0f);
	v1.Set(0.0f, 0.0f, 1.0f);
	v2.Set(0.0f, -0.5f, 0.0f);

	matrix.RotateX(degree);
	//法線と頂点を回転させる
	n = n.Multi(matrix);
	v0 = v0.Multi(matrix);
	v1 = v1.Multi(matrix);
	v2 = v2.Multi(matrix);

	//三角形3の描画
	glNormal3f(n.mX, n.mY, n.mZ);
	glVertex3f(v0.mX, v0.mY, v0.mZ);
	glVertex3f(v1.mX, v1.mY, v1.mZ);
	glVertex3f(v2.mX, v2.mY, v2.mZ);

	//描画終了
	glEnd();

	//三角形クラスのインスタンス作成
	CTriangle t0;
	//法線と頂点の設定
	t0.SetVertex(CVector(0.0f, 0.0f, 0.5f), CVector(1.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, -0.5f));
	t0.SetNormal(CVector(0.0f, 1.0f, 0.0f));
	//三角形の描画
//	t0.Render(matrix.Translate(degree*0.01, 0.0f, 0.0f));
//	t0.Render(matrix.Scale(sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5, sinf(degree*0.01) +1.5));
	//回転行列と移動行列を掛けて合成行列を作る
	matrix = matrix.RotateY(degree) * matrix.Translate(2.0f, 0.0f, 0.0f);
	t0.Render(matrix);

	CTriangle t1;
	//法線と頂点の設定
	t1.SetVertex(CVector(0.5f, 0.0f, 0.0f), CVector(0.0f, 1.0f, 0.0f), CVector(-0.5f, 0.0f, 0.0f));
	t1.SetNormal(CVector(0.0f, 0.0f, 1.0f));
	//三角形の描画
//	t1.Render();
	matrix.Translate(0.0f, degree*0.01, 0.0f);
//	t1.Render(matrix.RotateZ(degree));
//	t1.Render(matrix);
//	t1.Render(matrix.Scale(sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5));
	matrix = matrix.RotateZ(degree) * matrix.Translate(0.0f, 2.0f, 0.0f);
	t1.Render(matrix);

	CTriangle t2;
	//法線と頂点の設定
	t2.SetVertex(CVector(0.0f, 0.5f, 0.0f), CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, -0.5f, 0.0f));
	t2.SetNormal(CVector(1.0f, 0.0f, 0.0f));
	//三角形の描画
//	t2.Render();
//	matrix.Translate(0.0f, 0.0f, degree*0.01);
//	t2.Render(matrix.RotateX(degree));
//	t2.Render(matrix);
//	t2.Render(matrix.Scale(sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5, sinf(degree*0.01) + 1.5));
	matrix = matrix.RotateX(degree) * matrix.Translate(0.0f, 0.0f, 2.0f);
	t2.Render(matrix);

}
