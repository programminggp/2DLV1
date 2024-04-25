#pragma once
#include <initializer_list>

// オブジェクト識別用のタグ
enum class ETag
{
	eNone = -1,

	eField,	 // フィールドを構成するオブジェクト
	eExp,    // 経験値
	eRideableObject,	// 乗ることができるオブジェクト
	eItem,	 // アイテムの攻撃力アップ
	eItem2,  // アイテムの回復
	eItem3,  // アイテムの移動速度アップ

	eWeapon, // 武器

	ePlayer, // プレイヤー
	eEnemy,  // エネミー
	eBullet, // 弾丸
	eFlame,	 // 炎
	eSlash,	 // スラッシュ
	eWave,   // 波動
	eNeedle, // 針
	eLightningBall,  // 雷球
	eElectricShock,  // 電撃
	eImpact, // 衝撃

	eCamera, // カメラ

	Num
};
// オブジェクト識別用のタグの初期化リスト
using Tags = std::initializer_list<ETag>;
