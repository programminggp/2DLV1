#ifndef CSCENE_H
#define CSCENE_H

/*
シーンの基底クラス
*/
class CScene {
public:
	static CScene *mpInstance;
	//画面投影範囲の変数
	int mLeft, mRight, mBottom, mTop;

	//virtual 仮想関数
	//ポリモーフィズムの実装
	//=0 純粋仮想関数の設定
	virtual void Init() = 0;	//純粋仮想関数 初期化処理
	virtual void Update() = 0; //純粋仮想関数 更新処理

	//シーンの識別子
	enum EScene {
		EGAME,
	};
	//次のシーンの取得
	EScene mScene;


	virtual EScene GetNextScene() = 0;
	virtual ~CScene() {}	//デストラクタの定義
};


#endif
