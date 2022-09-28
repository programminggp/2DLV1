#ifndef CUTIL_H
#define CUTIL_H
/*
ユーティリティクラス
共通に使用できるプログラム
*/
class CUtil
{
public:
	//2D描画スタート
	//Start2D(左座標, 右座標, 下座標, 上座標)
	static void Start2D(float left, float right, float bottom, float top);
	static void End2D();
};

#endif
