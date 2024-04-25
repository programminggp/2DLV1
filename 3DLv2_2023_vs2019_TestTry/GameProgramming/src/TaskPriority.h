#pragma once

// Taskの優先順序
enum class ETaskPriority
{
	eNone = -1,

	// 3D関連
	eBackground,// 背景
	eDefault,	// デフォルト
	ePlayer,	// プレイヤー
	eEnemy,     // エネミー

	eWeapon,	// 武器
	eExp,       // 経験値
	eItem,      // アイテム

	eEffect,	// エフェクト
	eBillboard,	// ビルボードイメージ

	eCamera,	// カメラ

	// 2D関連
	eUI,		// UI関連のデフォルト
	eFade,		// 画面フェード
	eSystem,	// システム関連
	eDebug,		// デバッグ関連

	Num,

	// 2D関連のタスクの開始位置
	Start2d = eUI,
};