#include "CMain2D.h" //CMain2Dクラスのインクルード
#include "CScene.h" //CSceneクラスのインクルード
#include "CRectangle.h" //四角形クラスのインクルード
#include "CTexture.h" //テクスチャクラスのインクルード

//ゲームシーンクラスの定義
class CSceneGame : public CScene {
public:
	//変数の宣言
	CRectangle mPlayer; //CRectangleクラスの変数mPlayerを宣言
	CTexture mTexFighter; //戦闘機の画像

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
	//戦闘機の画像を読み込み
	mTexFighter.Load("4_fighters_sprites.tga");
	//プレイヤーの設定
	//X座標：0 Y座標：-200 幅：32 高さ：32
	mPlayer.Set(0, -200, 32, 32);
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
	//プレイヤーの描画
	mPlayer.Render(&mTexFighter, 1, 46, 63, 1);
//	mPlayer.Render();

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
