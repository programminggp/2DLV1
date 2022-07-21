#pragma once
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")
#pragma comment(lib,"winmm.lib")

/*
サウンドクラス
サウンドファイルを読み込み、再生する。
*/
class CSound {
	static int mNum;
	static IXAudio2 *mpXAudio;
	static IXAudio2MasteringVoice *mpMasterVoice;
	IXAudio2SourceVoice *mpSourceVoice;
	HMMIO g_hmmio;
	MMIOINFO g_mmioinfo;
	MMCKINFO g_riffchunkinfo;
	MMCKINFO g_datachunkinfo;
	WAVEFORMATEX g_wfx;
	unsigned char *buf;
	XAUDIO2_BUFFER mBufinfo;
	//オーディオファイル名の保存
	char	 file[100];
	//
	float mVolume;
public:

	CSound()
		: mpSourceVoice(0)
		, g_hmmio(0)
		, buf(nullptr)
		, mVolume(1.0f)
	{
		memset(&g_datachunkinfo, 0, sizeof(g_datachunkinfo));
		memset(&g_riffchunkinfo, 0, sizeof(g_riffchunkinfo));
		memset(&g_mmioinfo, 0, sizeof(g_mmioinfo));
		memset(&mBufinfo, 0, sizeof(mBufinfo));
		memset(&g_wfx, 0, sizeof(g_wfx));
		
		file[0] = 0;
		if (mNum == 0) {
			HRESULT hr;
			(void)CoInitializeEx(NULL, COINIT_MULTITHREADED);
			hr = XAudio2Create(&mpXAudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
			if (FAILED(hr))
			{
				CoUninitialize();
				mpXAudio = 0;
				return;
			}
			hr = mpXAudio->CreateMasteringVoice(&mpMasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL);
			if (FAILED(hr))
			{
				if (mpXAudio != NULL){ mpXAudio->Release(); }
				mpXAudio = 0;
				mpMasterVoice = 0;
				CoUninitialize();
				return;
			}
		}
		mNum++;
	}

	/*
	ファイルの読み込み
	*/
	bool Load(char* filename)
	{
		return Load(filename, 1.0f);
	}

	bool Load(char	*filename, float volume)
	{
		if (mpSourceVoice == 0)
		{
			//ファイル名保存
			strcpy(file, filename);
			MMCKINFO mmckinfo; PCMWAVEFORMAT pcmwf; MMRESULT mmret;
			memset(&g_mmioinfo, 0x00, sizeof(g_mmioinfo));
			g_hmmio = mmioOpen(const_cast<TCHAR *>(filename), &g_mmioinfo, MMIO_READ);
			if (g_hmmio == NULL) return false;
			memset(&g_riffchunkinfo, 0x00, sizeof(g_riffchunkinfo));
			g_riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
			mmret = mmioDescend(g_hmmio, &g_riffchunkinfo, NULL, MMIO_FINDRIFF);
			if (mmret != MMSYSERR_NOERROR) return false;
			memset(&mmckinfo, 0x00, sizeof(mmckinfo));
			mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
			mmret = mmioDescend(g_hmmio, &mmckinfo, &g_riffchunkinfo, MMIO_FINDCHUNK);
			if (mmret != MMSYSERR_NOERROR) return false;

			if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
			{
				mmioRead(g_hmmio, (HPSTR)&g_wfx, sizeof(g_wfx));
			}
			else
			{
				mmioRead(g_hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
				memset(&g_wfx, 0x00, sizeof(g_wfx));
				memcpy(&g_wfx, &pcmwf, sizeof(pcmwf));
				g_wfx.cbSize = 0;
			}
			mmioAscend(g_hmmio, &mmckinfo, 0);
			memset(&g_datachunkinfo, 0x00, sizeof(g_datachunkinfo));
			g_datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
			mmret = mmioDescend(g_hmmio, &g_datachunkinfo, &g_riffchunkinfo, MMIO_FINDCHUNK);
			if (mmret != MMSYSERR_NOERROR) return false;

			//return true;


			//XAUDIO2_VOICE_STATE state;
			unsigned char /**buf, */ *ptr; UINT32 buflen; LONG readlen; HRESULT hr; //DWORD dw;

			hr = mpXAudio->CreateSourceVoice(&mpSourceVoice, &g_wfx, XAUDIO2_VOICE_NOPITCH /*| XAUDIO2_VOICE_MUSIC*/, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL);
			if (FAILED(hr))
				return false;

			//buflen = g_wfx.nAvgBytesPerSec;
			buflen = g_datachunkinfo.cksize;
			buf = new unsigned char[buflen];
			ptr = buf; //cnt = (cnt + 1) % BUFFERQUEUE_ALLOC;
			readlen = mmioRead(g_hmmio, (HPSTR)ptr, buflen);
			if (readlen <= 0) return false;
			memset(&mBufinfo, 0x00, sizeof(mBufinfo));
//			mBufinfo.Flags = ((UINT32)readlen >= buflen) ? 0 : XAUDIO2_END_OF_STREAM;
			mBufinfo.Flags = XAUDIO2_END_OF_STREAM;
			mBufinfo.AudioBytes = readlen;
			mBufinfo.pAudioData = ptr;
			//mBufinfo.PlayLength = readlen / g_wfx.nBlockAlign;
			mVolume = volume;
		}
		return true;
	}
	/*
	サウンド再生（1回のみ）
	*/
	void Play(float vol)
	{
		mVolume = vol;
		Play();
	}
	void Play()
	{
		if (mpSourceVoice)
		{
			Stop();
			mBufinfo.LoopCount = 0;
			HRESULT hr = mpSourceVoice->SubmitSourceBuffer(&mBufinfo, NULL);
			if (FAILED(hr)) return;
			hr = mpSourceVoice->SetVolume(mVolume);
			if (FAILED(hr)) return;
			mpSourceVoice->Start();
		}

	}
	/*
	サウンド再生（リピート）
	*/
	void Repeat(float vol)
	{
		mVolume = vol;
		Repeat();
	}

	void Repeat()
	{
		if (mpSourceVoice)
		{
			Stop();
			mBufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
			HRESULT hr = mpSourceVoice->SubmitSourceBuffer(&mBufinfo, NULL);
			if (FAILED(hr)) return;
			hr = mpSourceVoice->SetVolume(mVolume);
			if (FAILED(hr)) return;
			mpSourceVoice->Start();
		}
	}
	/*
	サウンド停止
	*/
	void Stop()
	{
		if (mpSourceVoice)
		{
			mpSourceVoice->Stop();
			mpSourceVoice->FlushSourceBuffers();
		}
	}
	/*
	デストラクタ
	*/
	~CSound()
	{
		Stop();		//停止する
		mNum--;
		if (buf != NULL){ delete[] buf; }
		if (mpSourceVoice != NULL){ mpSourceVoice->DestroyVoice(); }
		if (g_hmmio != NULL){ mmioClose(g_hmmio, 0); }
		if (mNum == 0)
		{
			if (mpMasterVoice != NULL)
			{
				mpMasterVoice->DestroyVoice();
				mpMasterVoice = 0;
			}
			if (mpXAudio != NULL)
			{
				mpXAudio->Release();
				mpXAudio = 0;
			}
			CoUninitialize();
		}
	}
};
