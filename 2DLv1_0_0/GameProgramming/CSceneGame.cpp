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
	長方形を描画するメソッドを呼ぶ
	中心座標(80,60)、幅160、高さ120
	*/
	CRectangle::Render(80, 60, 80, 60);
	//長方形の追加
	CRectangle::Render(-80, -60, 80, 60);
	CRectangle::Render(-80-160, 60, 80, 60);
	CRectangle::Render(80 + 160, -60, 80, 60);
}

