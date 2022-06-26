#pragma once
#include "CUi.h"

//定数の定義
#define TEXTURE "image.png" //テクスチャのファイル名
#define TIPSIZE 20.0f //マップ要素のサイズ
/*
* CGameクラス
* ゲームクラス
* ゲームのマップを作成し、
* キャラクタを配置する
*/
class CGame
{
public:
	static CUi* Ui();
	CGame(); //デフォルトコンストラクタ（初期処理）
	void Update(); //更新処理
private:
	static CUi *spUi;
};
