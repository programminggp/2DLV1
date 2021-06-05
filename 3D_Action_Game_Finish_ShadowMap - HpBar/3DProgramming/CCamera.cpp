#include "Windows.h"
#include "glut.h"
#include "CCamera.h"
#include "CMatrix44.h"

//38
CMatrix44 CCamera::mCameraInverse;
extern CMatrix44 GMatrixModelView;

//カメラの上方向の初期化
CCamera::CCamera() : mUp(0.0f, 1.0f, 0.0f) {
	//視点と注視点の設定
//	setPos(0.0f, 0.0f, 0.0f);
}

/* 視点と注視点の設定
void setPos(float x, float y, float z)
x:注視点のX座標 y:注視点のY座標 z:注視点のZ座標
規定の視点は注視点よりYへ+2、Zへ+4移動
*/
void CCamera::setPos(float x, float y, float z) {
	//注視点の設定
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	//視点の設定
	eye[0] = pos[0];
	eye[1] = pos[1] + 1.0f;
	eye[2] = pos[2] + 10.0f;
	//カメラ行列の設定
	gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
}

/* 更新処理
キーにより視点を変更する
J：左前から　K：前面から　L：右前から
U：左後ろから　I：後ろから　O：右後ろから
*/
void CCamera::update() {
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();
	//視点の設定
	gluLookAt(eye[0], eye[1], eye[2], pos[0], pos[1], pos[2], mUp.x, mUp.y, mUp.z);
	//カメラの行列を取得
	glGetFloatv(GL_MODELVIEW_MATRIX, GMatrixModelView.f);
	//カメラの逆行列を取得
	mCameraInverse = GMatrixModelView.getInverse();
	//移動の要素を削除
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;
	//	update(CVector3(eye[0], eye[1], eye[2]), CVector3(pos[0], pos[1], pos[2]), CVector3(mUp.x, mUp.y, mUp.z));
}
//35
//カメラ行列の設定
void CCamera::update(CVector3 aeye, CVector3 pos, CVector3 up) {
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();
	//視点の設定
	gluLookAt(aeye.x, aeye.y, aeye.z, pos.x, pos.y, pos.z, up.x, up.y, up.z);
	//カメラの行列を取得
	glGetFloatv(GL_MODELVIEW_MATRIX, GMatrixModelView.f);
	//カメラの逆行列を取得
	mCameraInverse = GMatrixModelView.getInverse();
	//移動の要素を削除
	mCameraInverse.m[3][0] = mCameraInverse.m[3][1] = mCameraInverse.m[3][2] = 0.0f;

}
