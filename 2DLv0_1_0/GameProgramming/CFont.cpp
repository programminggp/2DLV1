#include "CFont.h"
#include <string.h>
#include <ctype.h>

CFont::CFont()
	: mStartAlphaIndex(0)
	, mStartNumIndex(0)
{}

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
		SetXYWH(x + i * w, y, w, h);
		if (isdigit(string[i])) {
			CRectangle::Render(string[i] - mStartNumIndex);
		}
		else if (isalpha(string[i])) {
			CRectangle::Render(toupper(string[i]) - mStartAlphaIndex);
		}
	}
}

void CFont::Set(char* filename, int row, int col, int num, int alpha) {
	LoadTexture(filename, row, col);
	SetNumAlphaIndex(num, alpha);
}
