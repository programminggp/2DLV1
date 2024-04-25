#pragma once

//------------------------------
// ポーズ種類のdefine（ビット値）
//------------------------------

//ゲームポーズ時
#define PAUSE_GAME (1 << 0)
//メニューを開いた時
#define PAUSE_MENU_OPEN (1 << 1)

//------------------------------

//Taskのポーズ種類
enum class ETaskPauseType
{
	//ポーズしない
	eNone = -1,
	//デフォルト（ポーズしない）
	eDefault = eNone,
	//ゲーム中のオブジェクト
	//（ゲームポーズ時とメニューを開いた時にポーズするTaskに設定）
	eGame = PAUSE_GAME | PAUSE_MENU_OPEN,
	//メニュー内のオブジェクト
	//（ゲームポーズ時のみポーズするTaskに設定）
	eMenu = PAUSE_GAME,
	//システム関連
	//（システム関連のTaskは常に動かすのでポーズしない）
	eSystem = eNone,

	Num
};
