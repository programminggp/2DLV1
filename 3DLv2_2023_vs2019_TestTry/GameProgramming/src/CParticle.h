#ifndef CPARTICLE_H
#define CPARTICLE_H

#include "CBillBoard.h"
#include "glm/vec3.hpp"

/*

画像を指定フレームの間描画する
描画の間、移動、回転、拡大縮小を行うことができる
初期値の面の向きは(0,0,1)とする
面の向きは、ビルド―ドもしくは回転値を指定

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
