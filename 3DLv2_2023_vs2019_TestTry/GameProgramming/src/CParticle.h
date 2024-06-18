#ifndef CPARTICLE_H
#define CPARTICLE_H

#include "CBillBoard.h"
#include "glm/vec3.hpp"

/*

�摜���w��t���[���̊ԕ`�悷��
�`��̊ԁA�ړ��A��]�A�g��k�����s�����Ƃ��ł���
�����l�̖ʂ̌�����(0,0,1)�Ƃ���
�ʂ̌����́A�r���h�\�h�������͉�]�l���w��

*/

class CParticle : public CBillBoard
{
public:
	CParticle(CMaterial* m, CVector& pos, CVector& rot, CVector& sca, CVector& posA, CVector& rotA, CVector& scaA, float alpha, int life, bool b=false);

	void Update();

	void Render();

private:
	//CTexture* mpTexture;
	CMaterial* mpMaterial;
	CVector mPositionAdd;
	CVector mRotationAdd;
	CVector mScaleAdd;
	float mAlpha;
	float mA;
	int mLife;
	bool mBillboard;
};


#endif
