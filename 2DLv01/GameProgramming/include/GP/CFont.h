#ifndef CFONT_H
#define CFONT_H

#include "CRectangle.h"

class CFont : public CRectangle {
public:
	int mStartNumIndex;
	int mStartAlphaIndex;
	CFont();
	CFont(char* filename, int row, int col, int num, int alpha);
	void Set(char* filename, int row, int col, int num, int alpha);
	void SetNumAlphaIndex(int num, int alpha);
	void Render(char *string, int x, int y, int w, int h);
};

#endif
