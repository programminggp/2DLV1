#pragma once

/*
サウンドクラス
サウンドファイルを読み込み、再生する。
*/
class CSound {
	//オーディオファイル名の保存
	char	 file[100];
	//ファイルオープンの結果
	int result;
	/*
	サウンドのWindowsAPIを実行する
	*/
	void sendstring(char* w);
public:
	CSound();
	/*
	ファイルの読み込み
	*/
	void Load(char	*filename);
	/*
	サウンド再生（1回のみ）
	*/
	void Play();
	/*
	サウンド再生（リピート）
	*/
	void Repeat();
	/*
	サウンド停止
	*/
	void Stop();
	/*
	ファイルのクローズ
	*/
	void Close();
	/*
	デストラクタ
	*/
	~CSound();
};
