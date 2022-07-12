#pragma once
/*
* カメラクラス
* 画面に表示するエリアを設定する
*/
class CCamera
{
public:
	//表示エリアの設定
	//Start(左座標,右座標,下座標,上座標)
	static void Start(double left, double right, double bottom, double top);
	static void End();
};