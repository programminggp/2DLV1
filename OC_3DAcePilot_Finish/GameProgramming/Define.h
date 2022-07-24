#ifndef DEFINE_H
#define DEFINE_H

//プレイヤーパラメータ
#define POWER_UP				0.001f	//出力変位:0.005f
#define PLAYER_POWER_MIN		0.1f	//最小出力:0.1f
#define PLAYER_POWER_MAX		0.45f	//最大出力:0.45f
#define PLAYER_BULLET_INTERVAL	10		//機銃発射間隔:10
#define PLAYER_MISSILE_INTERVAL	60		//ミサイル発射間隔:60

//敵機パラメータ
#define ENEMY_TURN_DEG		0.25f	//旋回性能:1.0f
#define ENEMY_POWER_MAX		0.15f	//エンジン出力:0.4f
#define ENEMY_POWER_MIN		0.11f	//エンジン出力小:0.2f
#define ENEMY_POINTCOUNT	150		//飛行ポイント更新頻度:100

//C5パラメータ
#define C5_POWER	1.2f	//エンジンパワー:1.2f
#define C5_HP		20		//HP:20


#endif
