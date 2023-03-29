#pragma once
class CRectangle
{
private:
	float mX; //X座標
	float mY; //Y座標
	float mZ; //Z座標
	float mW; //幅
	float mH; //高さ
	float maz; //Z座標判定値

public:
	//コンストラクタ
	CRectangle();
	//デストラクタ
	~CRectangle();

	//bool Collision(四角形のポインタ, X調整ポインタ,Y調整ポインタ)
	//戻り値
	//true:衝突している
	//false;衝突していない
	bool Collision(CRectangle* pRect, float* ax, float* ay);
	//bool Collision(四角形のポインタ)
    //戻り値
    //true:衝突している
    //false;衝突していない
	bool Collision(CRectangle* pRect);

	void Render();
	void Render(float x, float y, float w, float h);
	void Set(float x, float y, float w, float h);
	float X();
	float Y();
	float Z();
	float W();
	float H();
	void Y(float y);
	void X(float x);
};