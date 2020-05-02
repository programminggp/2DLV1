#pragma once
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*
サウンドクラス
サウンドファイルを読み込み、再生する。
*/
class CSound {
public:
	//オーディオファイル名の保存
	char	 file[100];
	//ファイルオープンの結果
	int result;
	CSound()
	{
		result = 0;
	}
	/*
	サウンドのWindowsAPIを実行する
	*/
	void sendstring(char* w) {
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
	void Load(char	*filename)
	{
		//ファイル名保存
		strcpy(file, filename);
		sendstring("open %s");
	}
	/*
	サウンド再生（1回のみ）
	*/
	void Play()
	{
		sendstring("play %s from 0");
	}
	/*
	サウンド再生（リピート）
	*/
	void Repeat()
	{
		sendstring("play %s from 0 repeat");
	}
	/*
	サウンド停止
	*/
	void Stop()
	{
		sendstring("stop %s");
	}
	/*
	ファイルのクローズ
	*/
	void Close()
	{
		sendstring("close %s");
	}
	/*
	デストラクタ
	*/
	~CSound()
	{
		Stop();		//停止する
		Close();	//ファイルをクローズする
	}
};
