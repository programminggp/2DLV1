#ifndef CTEXT_H
#define CTEXT_H

#include "CTexture.h"

/*
文字の描画
*/
class CText {
	//テクスチャのインスタンス
	CTexture mFont;
public:
	//テクスチャのロード
	//LoadTexture(テクスチャファイル名, 行数, 列数)
	void LoadTexture(const char *tga, int row, int col);
	//文字の描画
	void DrawChar(char ch, int x, int y, int w, int h);
	//文字列描画
	void DrawString(const char *s, int x, int y, int w, int h);
};
#endif