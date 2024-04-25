#pragma once
#include "CObjectBase.h"
#include "CharaStatus.h"


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


/// <summary>
/// キャラクターのベースクラス
/// </summary>
class CCharaBase : public CObjectBase
{
public:
	CCharaBase(ETag tag, ETaskPriority prio, int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eGame);
	virtual ~CCharaBase();

	/// <summary>
	/// 被ダメージ処理
	/// </summary>
	/// <param name="damage">受ける処理</param>
	virtual void TakeDamage(int damage, CObjectBase* causedObj);

	/// <summary>
	/// 最大ステータスを取得
	/// </summary>
	/// <returns></returns>
	const CharaStatus& MaxStatus() const;
	/// <summary>
	/// 現在のステータスを取得
	/// </summary>
	/// <returns></returns>
	const CharaStatus& Status() const;

	virtual float GetAtkBuff()const;

	virtual float GetDefBuff(const CVector&attackDir)const;

protected:
	CharaStatus mCharaMaxStatus;  //最大ステータス
	CharaStatus mCharaStatus;  //現在のステータス

	float mBaseAttackBuffRatio;  // 攻撃力の強化割合 (1.0で等値)
	float mBaseDefenseBuffRatio; // 防御力の強化割合 (1.0で等値)
};

/// <summary>
/// ダメージ量を算出
/// </summary>
/// <param name="attaker">攻撃側のキャラ</param>
/// <param name="defender">防御力のキャラ</param>
/// <returns>ダメージ量</returns>
extern int CalcDamage(const CCharaBase* attaker, const CCharaBase* defender);
