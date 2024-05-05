#pragma once
#include "CInput.h"


class CMaterial;

class CEffectData
{
public:
	char mFileName[64];	//ファイル名
	int mRows;			//行数
	int mCols;			//列数
    float mSize;          //
	int mFpk;			//コマ切り替えフレーム時間　0は切り替えなし
	int mIndex;			//表示するコマ　切り替えなし時
	int mDispframe;		//表示フレーム時間　切り替えなし時
	CMaterial *mpMaterial;
public:
    // パラメータ付きコンストラクタを追加
    CEffectData(const char* fileName, int rows, int cols,float size, int fpk, int index, int dispframe, CMaterial* material)
        : mRows(rows), mCols(cols), mSize(size), mFpk(fpk), mIndex(index), mDispframe(dispframe), mpMaterial(material)
    {
        // ファイル名をコピー
        strncpy(mFileName, fileName, sizeof(mFileName) - 1);
        mFileName[sizeof(mFileName) - 1] = '\0'; // 文字列の終端を追加
    }

    // デフォルトコンストラクタも提供
    CEffectData()
        : mRows(0), mCols(0), mSize(0.0f), mFpk(0), mIndex(0), mDispframe(0), mpMaterial(nullptr)
    {
        // ファイル名を空に初期化する
        memset(mFileName, 0, sizeof(mFileName));
    }

    // デストラクタを提供
    ~CEffectData() {
        // 必要なクリーンアップ処理を行う
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