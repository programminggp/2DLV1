#pragma once
#include "CInput.h"


class CMaterial;

class CEffectData
{
public:
	char mFileName[64];	//�t�@�C����
	int mRows;			//�s��
	int mCols;			//��
    float mSize;          //
	int mFpk;			//�R�}�؂�ւ��t���[�����ԁ@0�͐؂�ւ��Ȃ�
	int mIndex;			//�\������R�}�@�؂�ւ��Ȃ���
	int mDispframe;		//�\���t���[�����ԁ@�؂�ւ��Ȃ���
	CMaterial *mpMaterial;
public:
    // �p�����[�^�t���R���X�g���N�^��ǉ�
    CEffectData(const char* fileName, int rows, int cols,float size, int fpk, int index, int dispframe, CMaterial* material)
        : mRows(rows), mCols(cols), mSize(size), mFpk(fpk), mIndex(index), mDispframe(dispframe), mpMaterial(material)
    {
        // �t�@�C�������R�s�[
        strncpy(mFileName, fileName, sizeof(mFileName) - 1);
        mFileName[sizeof(mFileName) - 1] = '\0'; // ������̏I�[��ǉ�
    }

    // �f�t�H���g�R���X�g���N�^����
    CEffectData()
        : mRows(0), mCols(0), mSize(0.0f), mFpk(0), mIndex(0), mDispframe(0), mpMaterial(nullptr)
    {
        // �t�@�C��������ɏ���������
        memset(mFileName, 0, sizeof(mFileName));
    }

    // �f�X�g���N�^���
    ~CEffectData() {
        // �K�v�ȃN���[���A�b�v�������s��
        //if (mpMaterial)
        //{
        //    delete mpMaterial;
        //    mpMaterial = nullptr;
        //}
    }
};

#include <vector>

class CEffectManager
{
	CEffectManager();
public:
    std::vector<CEffectData> mEffectData;
	static CEffectManager* Instance();
	static CEffectData sEffectData[];
	CEffectManager* mpInstance;
	void Update();
	CInput mInput;
	int mSize;
};