#include "CFont.h"
#include <string.h>
#include <ctype.h>

CTexture CFont::mTexture;

CFont::CFont()
	: mStartAlphaIndex(0)
	, mStartNumIndex(0)
	, mCol(0)
	, mRow(0)
{
}

CFont::CFont(char* filename, int row, int col, int num, int alpha) {
	Set(filename, row, col, num, alpha);
}

void CFont::SetNumAlphaIndex(int num, int alpha) {
	mStartNumIndex = 0x30 - num;
	mStartAlphaIndex = 0x41 - alpha;
}

void CFont::Render(char *string, int x, int y, int w, int h) {
	int len = strlen(string);
	for (int i = 0; i < len; i++) {
		CRectangle::Set(x + i * w * 2, y, w, h);
		if (isdigit(string[i])) {
			int index = string[i] - mStartNumIndex;
			float row = index / mCol;
			float col = index % mCol;
			CRectangle::Render(&mTexture,
				mTexture.mHeader.width * col / mCol,
				mTexture.mHeader.width * (col + 1) / mCol,
				mTexture.mHeader.height * (row + 1) / mRow,
				mTexture.mHeader.height * row / mRow);
		}
		else if (isalpha(string[i])) {
			int index = toupper(string[i]) - mStartAlphaIndex;
			float row = index / mCol;
			float col = index % mCol;
			CRectangle::Render(&mTexture,
				mTexture.mHeader.width * col / mCol,
				mTexture.mHeader.width * (col + 1) / mCol,
				mTexture.mHeader.height * (row+1) / mRow,
				mTexture.mHeader.height * row / mRow);
		}
	}
}

void CFont::Set(char* filename, int row, int col, int num, int alpha) {
	if (mTexture.mId == 0) {
		mTexture.Load(filename);
	}
	SetNumAlphaIndex(num, alpha);
	mCol = col;
	mRow = row;
}
