#include "CMain2D.h"

#include "CScene.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CRectangle.h"
#include "CInput.h"

//クラスの定義
//ゲームシーンクラスの定義
class CSceneGame : public CScene {
public:
	//変数の宣言
	CCamera mCamera;//画面設定のインスタンス
	CTexture mTexBackGround;//背景画像のインスタンス
	CRectangle mBackGround;//背景四角形のインスタンス
	CTexture mTexFighters;//戦闘機画像のインスタンス
	CRectangle mPlayer;//プレイヤー四角形のインスタンス
	CRectangle mEnemy;//敵四角形のインスタンス
	CInput mInput;//入力処理のインスタンス

	//デフォルトコンストラクタ
	CSceneGame();

	//メソッド（プログラム）の宣言
	void Update();//更新処理
	void Render();//描画処理
};

//デフォルトコンストラクタ
//最初に１度だけ実行する処理
CSceneGame::CSceneGame()
{
	mTexBackGround.Load("bg_space_seamless.tga");
	mTexFighters.Load("4_fighters_sprites.tga");

	mBackGround.Set(200, 300, 640, 512);

	mPlayer.Set(200, 100, 32, 32);

	mEnemy.Set(100, 600, 18, 32);

	mCamera.Camera2D(200.0f, 300.0f, 200.0f, 300.0f);
}

//更新処理
//繰り返し実行する処理
void CSceneGame::Update() {
	//Enemy
	mEnemy.mX += 2;
	mEnemy.mY -= 4;
	if (mEnemy.mY < mCamera.GetBottom2D()) {
		mEnemy.mY = mCamera.GetTop2D();
	}
	if (mEnemy.mX > mCamera.GetRight2D()) {
		mEnemy.mX = mCamera.GetLeft2D();
	}

	//Player
	if (mInput.Key('A')) {
		mPlayer.mX -= 3.0f;
	}
	if (mInput.Key('D')) {
		mPlayer.mX += 3.0f;
	}
}

//描画処理
//繰り返し描画する処理
void CSceneGame::Render() {
	//画面設定
	mCamera.Camera2D(200.0f, 300.0f, 200.0f, 300.0f);
	//描画処理
	mBackGround.Render(&mTexBackGround);
	mPlayer.Render(&mTexFighters, 1, 46, 63, 0);
	mEnemy.Render(&mTexFighters, 165, 200, 0, 63);
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
