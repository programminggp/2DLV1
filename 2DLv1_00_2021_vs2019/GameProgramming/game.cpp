#include <stdio.h> //printf関数を取り込む
#include "glut.h" //グラフィックライブラリOpenGLを取り込む

/*
Lesson2
四角形の描画
課題
四角形の描画位置の変更
*/

//class クラスとはプログラムの作成単位です
//クラスの定義
//class クラス名

//ゲームクラスの定義
//クラス名；CGame
class CGame //CGameクラスの定義 
{ //定義の開始
public: //アクセス制限なし

	//メソッドの宣言
	//戻り値の型　メソッド名(引数)

	//デフォルトコンストラクタの宣言
	//戻り値の型：記述なし
	//メソッド名：クラス名と同じ
	//引数：なし
	CGame(); //デフォルトコンストラクタの宣言

	//デストラクタの宣言
	//戻り値の型：記述なし
	//メソッド名：クラス名の前に~
	//引数：なし
	~CGame(); //デストラクタの宣言

	//更新処理の宣言
	//戻り値の型：voidは戻り値なし
	//メソッド名：Update
	//引数：なし
	void Update(); //Updateメソッドの宣言

}; //定義の終了;必要

//メソッドとは 処理を集めた処理です
//メソッドの定義では、メソッドの処理を作成します
//メソッド名の前にクラス名と::を付けます

//ゲームクラスのデフォルトコンストラクタの定義
CGame::CGame()
{ //処理の開始
	printf("CGame::CGame\n"); //コンソール画面に出力する
} //処理の終了

//ゲームクラスのデストラクタの定義
CGame::~CGame()
{ //処理の開始
	printf("CGame::~CGame\n"); //コンソール画面に出力する
} //処理の終了

//ゲームクラスの更新メソッドの定義
void CGame::Update()
{ //処理の開始

	//四角形を描画する
	glBegin(GL_QUADS); //描画開始（四角形）
	glVertex2f(0.0f, 0.0f); //頂点座標設定（X座標,Y座標）
	glVertex2f(100.0f, 0.0f); //頂点は反時計回りに設定
	glVertex2f(100.0f, 100.0f);
	glVertex2f(0.0f, 100.0f);
	glEnd(); //描画終了

} //処理の終了

//ゲームクラスのポインタ変数
//ゲームクラスのインスタンスを代入する
//ポインタ変数を作成する
CGame *gpGame; //ゲームクラスのポインタ変数gpGameの作成

//初期化処理
//プログラム実行の最初に1度だけ実行される処理
void Init()
{
	//new命令で、ゲームクラスのインスタンスを作成し、
	//変数gpGameへ代入する
	gpGame = new CGame(); //この時ゲームクラスのコンストラクタが呼ばれる
}

//更新処理
//プログラムの実行中に繰り返し実行される処理
void Update()
{
	//代入されたポインタ変数を使い、
	//ゲームクラスのUpdateメソッドを呼び出す
	gpGame->Update(); //gpGameのUpdateメソッドの呼び出し
}

//終了処理
//プログラムの終了時に一度だけ実行される処理
void Destroy()
{
	//delete命令でgpGameに代入された
	//ゲームクラスのインスタンスを削除する
	delete gpGame; //この時ゲームクラスのデストラクタが呼ばれる
	printf("Push Any Key");
	getchar(); //キーボード入力待ち
}
