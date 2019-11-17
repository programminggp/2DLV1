#ifndef CEFFECT_H
#define CEFFECT_H

#include "CBillBoard.h"

class CEffect : public CBillBoard {
public:
	int mRows;
	int mCols;
	int mFps;
	int mFrame;

	CEffect();
	CEffect(const CVector &pos, float w, float h, std::shared_ptr<CTexture> texture, int row=1, int col=1, int fps=1);

	void Update();

};


#endif
