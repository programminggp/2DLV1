#ifndef CIMAGE_H
#define CIMAGE_H

#include "CBillBoard.h"

class CImage : public CBillBoard {
public:
//	float mU[2];
//	float mV[2];

	CImage(std::shared_ptr<CTexture> texture, const CVector &pos, const CVector &rot, const CVector &sca);
	void SetUv(float left, float right, float bottom, float top);
	void Update();
};

#endif
