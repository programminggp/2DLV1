#ifndef CFONT_H
#define CFONT_H

#include "CRectangle.h"
/*
CFont
文字の表示
*/
class CFont : public CRectangle {
	static CTexture mTexture;
	int mStartNumIndex;
	int mStartAlphaIndex;
	int mCol, mRow;
public:
	CFont();
	/*
	フォントクラスの作成
	filename:画像ファイルの指定
	row:文字データの行数
	col:文字データの列数
	num:数字データの開始文字位置
	alpha:英字データの開始文字位置
	*/
	CFont(char* filename, int row, int col, int num, int alpha);
	/*
	フォントクラスの設定
	filename:画像ファイルの指定
	row:文字データの行数
	col:文字データの列数
	num:数字データの開始文字位置
	alpha:英字データの開始文字位置
	*/
	void Set(char* filename, int row, int col, int num, int alpha);
	/*
	データ位置の設定
	num:数字データの開始文字位置
	alpha:英字データの開始文字位置
	*/
	void SetNumAlphaIndex(int num, int alpha);
	/*
	文字の描画
	string:描画する文字列
	x:画面に描画する位置のX座標
	y:画面に描画する位置のY座標
	w:画面に描画する文字の幅
	h:画面に描画する文字の高さ
	*/
	void Render(char *string, int x, int y, int w, int h);
};

#endif
