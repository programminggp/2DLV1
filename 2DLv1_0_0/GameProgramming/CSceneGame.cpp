//CSceneGameクラスのインクルード
#include "CSceneGame.h"
//CRectangleクラスのインクルード
#include "CRectangle.h"
/*
Updateメソッド
1フレームの更新処理を行う
*/
void CSceneGame::Update() {
	//命令の記述
	/*
	変数の作成
	x:長方形の中心x座標
	y:長方形の中心y座標 
	w:長方形の幅の半分 
	h:長方形の高さの半分
	*/
	float x;	//float型の変数xを作成する
	float y = 270.0;	//float型の変数yを作成し150.0を代入する
	float w, h = 30.0;	//float型の変数wと変数hを,区切りで一度に作成する

	x = 0.0;	//変数xに値を代入する
	w = 400.0;	//変数wに値を代入する

	//上の長方形を描画する
	//変数に代入されている値で命令を実行する
	CRectangle::Render(x, y, w, h);

	//下の長方形を描画する
	y = -270.0;	//代入されると前の値は上書きされる
	CRectangle::Render(x, y, w, h);

	//左の長方形を描画する
	x = -370.0;
	w = 30.0;
	y = 0.0;
	h = 300.0;
	CRectangle::Render(x, y, w, h);

	//右の長方形を描画する
	x = 370.0;
	CRectangle::Render(x, y, w, h);
}

