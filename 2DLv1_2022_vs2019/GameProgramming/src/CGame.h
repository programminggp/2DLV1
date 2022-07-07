#pragma once
#include "CUi.h"
#include "CPlayer2.h"

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
	~CGame();
	bool IsClear();
	void Clear();
	bool IsOver();
	void Over();
	void Start();
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
	};
	CGame(); //デフォルトコンストラクタ（初期処理）
	void Update(); //更新処理
private:
	CInput mInput;
	EState mState;
	int mTime; //経過時間
	CUi *mpUi; //UIクラスのポインタ
};
