#ifndef CSCENE_H
#define CSCENE_H

class CScene {
public:
	//仮想関数の宣言
	//デストラクタ
	virtual ~CScene();
	//Init：初期化処理
	virtual void Init();
	//Update：更新処理
	virtual void Update();
	//Render：描画処理
	virtual void Render();
};

#endif
