#pragma once
class CRectangle
{
private:
	float mX; //X���W
	float mY; //Y���W
	float mW; //��
	float mH; //����
public:
	CRectangle();
	~CRectangle();
	void Render();
	void Render(float x, float y, float w, float h);
	virtual void Set(float x, float y, float w, float h);
	float X();
	float Y();
	float W();
	float H();
	void Y(float y);
	void X(float x);
	//bool Collision(�l�p�`�̃|�C���^)
	//�߂�l
	//true:�Փ˂��Ă���
	//false;�Փ˂��Ă��Ȃ�
	bool Collision(CRectangle* pRect);
};