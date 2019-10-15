#ifndef CBULLET_H
#define CBULLET_H

#include "CCharacter.h"
#include "CTriangle.h"

class CBullet : public CCharacter {
public:
	//三角形
	CTriangle mT;
	//幅と奥行きの設定
	//Set(幅, 奥行)
	void Set(float w, float d);
	//更新
	void Update();
	//描画
	void Render();
};


#endif
