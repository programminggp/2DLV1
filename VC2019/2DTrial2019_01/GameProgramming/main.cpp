#include "CMain2D.h" //CMain2Dクラスのインクルード
#include "CScene.h" //CSceneクラスのインクルード

//ゲームシーンクラスの定義
class CSceneGame : public CScene {
public:
	//デフォルトコンストラクタの宣言
	CSceneGame();
	//更新メソッドの宣言
	void Update();
	//描画メソッドの宣言
	void Render();
};

/*
デフォルトコンストラクタの定義
最初に１度だけ実行する処理
*/
CSceneGame::CSceneGame() {
}

/*
更新メソッドの定義
繰り返し実行する処理
*/
void CSceneGame::Update() {
}

/*
描画メソッドの定義
繰り返し描画する処理
*/
void CSceneGame::Render() {
}

/*
main関数
C言語プログラムの開始
*/
int main(void)
{
	//2D画面設定 横：400　縦：600
	CMain2D main(400, 600);
	//ゲームシーンのインスタンス生成
	main.SetScene(new CSceneGame());
}
