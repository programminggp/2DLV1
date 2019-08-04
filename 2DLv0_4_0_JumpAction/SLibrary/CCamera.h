#ifndef CCAMERA_H
#define CCAMERA_H

class CCamera {
	float mX, mY, mW, mH;
public:
	/*
	Camera2D
	2Dのカメラを設定する
	x:描画するエリアの中心座標
	y:描画するエリアの中心座標
	w:描画するエリアの幅
	h:描画するエリアの高さ
	*/
	void Camera2D(float x, float y, float w, float h);
	void Camera2D();
};


#endif
