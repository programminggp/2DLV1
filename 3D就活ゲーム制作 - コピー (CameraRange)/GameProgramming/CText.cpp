#include "CText.h"

//staticのテクスチャのインスタンス
CTexture CText::mFont;
CTexture CText::mFont2;
CTexture CText::mFont3;
/*
DrawChar
文字を描画する
ch:文字データ x:X座標 y:Y座標 w:幅 h:高さ fontnumber:使うフォントの番号
*/
void CText::DrawChar(char ch, int x, int y, int w, int h, int fontnumber) {
	if (fontnumber == 1){
		mFont.DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
	}
	if (fontnumber == 2){
		mFont2.DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
	}
	if (fontnumber == 3){
		mFont3.DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
	}

	/*//スマート案:mFontは配列
	for (int i = 0; i < 3; i++){
		if (fontnumber == i){
			mFont[i].DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
		}
	}*/
	
}
// s:文字列データ x:先頭文字のX座標 y:先頭文字のY座標
void CText::DrawString(char *s, int x, int y, int w, int h, int font_number) {
	//1文字ずつ描画します
	for (int i = 0; s[i] != '\0'; i++) {
		//文字を描画する
		DrawChar(s[i], x, y, w, h, font_number);
		//右へ移動
		x += w * 2;
	}
}
