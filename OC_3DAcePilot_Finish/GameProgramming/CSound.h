#pragma once
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*
�T�E���h�N���X
�T�E���h�t�@�C����ǂݍ��݁A�Đ�����B
*/
class CSound {
public:
	//�I�[�f�B�I�t�@�C�����̕ۑ�
	char	 file[100];
	//�t�@�C���I�[�v���̌���
	int result;
	CSound()
	{
		result = 0;
	}
	/*
	�T�E���h��WindowsAPI�����s����
	*/
	void sendstring(char* w) {
		if (!result) {
			//���ߕҏW�̈�̍쐬
			char	 buf[100];
			//���ߕҏW
			sprintf(buf, w, file);
			//���ߎ��s
			result = mciSendString(buf, NULL, 0, NULL);
		}
	}
	/*
	�t�@�C���̓ǂݍ���
	*/
	void Load(char	*filename)
	{
		//�t�@�C�����ۑ�
		strcpy(file, filename);
		sendstring("open %s");
	}
	/*
	�T�E���h�Đ��i1��̂݁j
	*/
	void Play()
	{
		sendstring("play %s from 0");
	}
	/*
	�T�E���h�Đ��i���s�[�g�j
	*/
	void Repeat()
	{
		sendstring("play %s from 0 repeat");
	}
	/*
	�T�E���h��~
	*/
	void Stop()
	{
		sendstring("stop %s");
	}
	/*
	�t�@�C���̃N���[�Y
	*/
	void Close()
	{
		sendstring("close %s");
	}
	/*
	�f�X�g���N�^
	*/
	~CSound()
	{
		Stop();		//��~����
		Close();	//�t�@�C�����N���[�Y����
	}
};
