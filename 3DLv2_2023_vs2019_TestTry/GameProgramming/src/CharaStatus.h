#pragma once

//キャラのステータス
struct CharaStatus
{
    int level;          // レベル
	int exp;            // 経験値
	int hp;             // HP
	int power;          // 攻撃力
	int defense;        // 防御力
	float mobility;     // 移動性
	int SpecialAttack;  // 特殊攻撃
	float volume;       // 大きさ
	float cameraHeight; // カメラの高さ

	// ステータスのリセット
	void Reset()
	{
		level = 1;
		exp = 0;
		power = 5;
		defense = 0;
		mobility = 1.0f;
		SpecialAttack = 2;
		volume = 1.02f;
		cameraHeight = 0.0f;
	}
}; 

// プレイヤーの最大レベル
#define PLAYER_LEVEL_MAX 100
// プレイヤーのレベルごとにステータスのテーブル
extern const CharaStatus PLAYER_STATUS[PLAYER_LEVEL_MAX];

// 敵の最大レベル
#define ENEMY__LEVEL_MAX 5
// 敵のレベルごとにステータスのテーブル
extern const CharaStatus ENEMY_STATUS[ENEMY__LEVEL_MAX];    // スライム
extern const CharaStatus ENEMY2_STATUS[ENEMY__LEVEL_MAX];   // マッシュルーム
extern const CharaStatus ENEMY3_STATUS[ENEMY__LEVEL_MAX];   // 亀
extern const CharaStatus ENEMY4_STATUS[ENEMY__LEVEL_MAX];   // エイ
extern const CharaStatus ENEMY5_STATUS[ENEMY__LEVEL_MAX];   // 蜂
extern const CharaStatus ENEMY6_STATUS[ENEMY__LEVEL_MAX];   // サボテン
extern const CharaStatus ENEMY7_STATUS[ENEMY__LEVEL_MAX];   // チェストモンスター
extern const CharaStatus ENEMY8_STATUS[ENEMY__LEVEL_MAX];   // 球体のモンスター
extern const CharaStatus ENEMY9_STATUS[ENEMY__LEVEL_MAX];   // ボクサー
extern const CharaStatus ENEMY10_STATUS[ENEMY__LEVEL_MAX];  // ドラゴン
