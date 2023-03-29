#pragma once
class CRectangle
{
private:
	float mX; //X���W
	float mY; //Y���W
	float mZ; //Z���W
	float mW; //��
	float mH; //����
	float maz; //Z���W����l

public:
	//�R���X�g���N�^
	CRectangle();
	//�f�X�g���N�^
	~CRectangle();

	//bool Collision(�l�p�`�̃|�C���^, X�����|�C���^,Y�����|�C���^)
	//�߂�l
	//true:�Փ˂��Ă���
	//false;�Փ˂��Ă��Ȃ�
	bool Collision(CRectangle* pRect, float* ax, float* ay);
	//bool Collision(�l�p�`�̃|�C���^)
    //�߂�l
    //true:�Փ˂��Ă���
    //false;�Փ˂��Ă��Ȃ�
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