#include "CRectangle.h"
#include "CTriangle.h"

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {


}
//Update関数
//プログラムの実行中、繰り返し呼ばれる関数
void Update() {
	CRectangle rectangle(400.0f, 300.0f, 80.0f, 60.0f);
	CRectangle rectangle2(240.0f, 180.0f, 80.0f, 60.0f);
	CRectangle rectangle3(560.0f, 420.0f, 80.0f, 60.0f);
	//rectangle.Render();
	//CRectangle rectangle2(400.0f, 800.0f, 300.0f, 600.0f);
	//CRectangle rectangle3(550.0f, 650.0f, 100.0f, 200.0f);
	//CRectangle rectangle4(150.0f, 250.0f, 400.0f, 500.0f);
}
