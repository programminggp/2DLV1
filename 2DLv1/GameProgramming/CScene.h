#ifndef CSCENE_H
#define CSCENE_H
#include "CRectangle.h"


//シーンクラス
class CScene {
public:
	CRectangle mRectangle;
	//一度だけ実行されるメソッド
	void Init();
	//繰り返し実行されるメソッド
	void Update();
};

#endif
