#ifndef CXAUDIO2_H
#define CXAUDIO2_H
#include <windows.h>
#include <mmsystem.h>
#include <xaudio2.h>

class CXAudio2
{
public:
//	static IXAudio2 *g_lpXAudio;
//	static IXAudio2MasteringVoice *g_lpMasterVoice;
	IXAudio2 *g_lpXAudio;
	IXAudio2MasteringVoice *g_lpMasterVoice;
	IXAudio2SourceVoice *g_lpSourceVoice;
	HMMIO g_hmmio = NULL;
	MMIOINFO g_mmioinfo;
	MMCKINFO g_riffchunkinfo;
	MMCKINFO g_datachunkinfo;
	WAVEFORMATEX g_wfx;
	unsigned char *buf;

	CXAudio2();
	~CXAudio2();

	bool LoadSound(const TCHAR *lpFileName);
	int Play(void);

};

class CSoundCallback : public IXAudio2VoiceCallback{
public:
	HANDLE g_hEvent;

	CSoundCallback(){ }
	~CSoundCallback(){ }
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired){ }
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd(void){ }
	void STDMETHODCALLTYPE OnStreamEnd(void){ SetEvent(g_hEvent); }
	void STDMETHODCALLTYPE OnBufferStart(void *pBufferContext){ SetEvent(g_hEvent); }
	void STDMETHODCALLTYPE OnBufferEnd(void *pBufferContext){ }
	void STDMETHODCALLTYPE OnLoopEnd(void *pBufferContext){ }
	void STDMETHODCALLTYPE OnVoiceError(void *pBufferContext, HRESULT Error){ }
};

#endif
