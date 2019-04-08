#include "CSound.h"

CSound::CSound()
{
	result = 0;
}
/*
サウンドのWindowsAPIを実行する
*/
void CSound::sendstring(char* w) {
	if (!result) {
		//命令編集領域の作成
		char	 buf[100];
		//命令編集
		sprintf(buf, w, file);
		//命令実行
		result = mciSendString(buf, NULL, 0, NULL);
	}
}
/*
ファイルの読み込み
*/
void CSound::Load(char	*filename)
{
	//ファイル名保存
	strcpy(file, filename);
	sendstring("open %s");
}
/*
サウンド再生（1回のみ）
*/
void CSound::Play()
{
	sendstring("play %s from 0");
}
/*
サウンド再生（リピート）
*/
void CSound::Repeat()
{
	sendstring("play %s from 0 repeat");
}
/*
サウンド停止
*/
void CSound::Stop()
{
	sendstring("stop %s");
}
/*
ファイルのクローズ
*/
void CSound::Close()
{
	sendstring("close %s");
}
/*
デストラクタ
*/
CSound::~CSound()
{
	Stop();		//停止する
	Close();	//ファイルをクローズする
}
