#ifndef CSCENE_H
#define CSCENE_H

/*
シーンの基底クラス
*/
class CScene {
public:
	//virtual 仮想関数
	//ポリモーフィズムの実装
	//=0 純粋仮想関数の設定
	virtual void Init() = 0;	//純粋仮想関数 初期化処理
	virtual void Update() = 0; //純粋仮想関数 更新処理
	//次のシーンの取得
	//virtual EScene GetNextScene() = 0;
	virtual ~CScene() {}	//デストラクタの定義

	//2D描画スタート
	//Start2D(左座標, 右座標, 下座標, 上座標)
	void Start2D(float left, float right, float bottom, float top);
	//2D描画終了
	void End2D();
	//カメラの設定
	//Camera3D(視点X座標, 視点Y座標, 視点Z座標, 注視点X座標, 注視点Y座標, 注視点Z座標, 上方向X, 上方向Y, 上方向Z)
	void Camera3D(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz);
};


#endif
