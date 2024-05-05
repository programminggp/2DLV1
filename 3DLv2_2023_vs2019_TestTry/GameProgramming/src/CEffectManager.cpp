#include "CEffectManager.h"
#include "CMaterial.h"
#include "CEffect.h"

#define EFFECTDATA_FILENAME "res\\effectdata.txt"


CEffectData CEffectManager::sEffectData[] =
{
	{"Effect\\tktk_Impact_14.png",2,5,3.0,1,2,5,nullptr},
	{"Effect\\Impact.png",3,5,3.0,1,1,10,nullptr},
};

CEffectManager::CEffectManager()
	:mpInstance(nullptr), mSize(0)
{

	FILE* fp = fopen(EFFECTDATA_FILENAME, "r");
	if (fp)
	{
		char buf[128];
		fgets(buf, sizeof(buf), fp);
		while (fgets(buf, sizeof(buf), fp) != NULL)
		{
			CEffectData e;
			int r = sscanf(buf, "%s %d,%d,%f,%d,%d,%d",
				e.mFileName,
				&e.mRows,
				&e.mCols,
				&e.mSize,
				&e.mFpk,
				&e.mIndex,
				&e.mDispframe
				);
			e.mpMaterial = new CMaterial();
			e.mpMaterial->Texture()->Load(e.mFileName);
			mEffectData.push_back(e);
		}
		fclose(fp);
	}

	/*
	mSize = sizeof(sEffectData) / sizeof(CEffectData);
	for (int i = 0; i < mSize ; i++)
	{
		sEffectData[i].mpMaterial = new CMaterial();
		sEffectData[i].mpMaterial->Texture()->Load(sEffectData[i].mFileName);
	}
	*/
}

CEffectManager* CEffectManager::Instance()
{
	static CEffectManager* instance = nullptr;
	if (instance == nullptr)
	{
		instance = new CEffectManager();
		instance->mpInstance = instance;
	}
	return instance;
}

#define POS CVector(0.0f, 0.0f, 0.0f)
#define ESIZE 2.0f

void CEffectManager::Update()
{
	char* num = "1234567890";
	bool flgPush = false;
	for (int i = 0; i < strlen(num); i++)
	{
		if (mInput.Key(num[i]))
		{
			flgPush = true;
			FILE* fp = fopen(EFFECTDATA_FILENAME, "r");
			int i = 0;
			if (fp)
			{
				char buf[128];
				fgets(buf, sizeof(buf), fp);
				while (fgets(buf, sizeof(buf), fp) != NULL)
				{
					CEffectData e;
					int r = sscanf(buf, "%s %d,%d,%f,%d,%d,%d",
						e.mFileName,
						&e.mRows,
						&e.mCols,
						&e.mSize,
						&e.mFpk,
						&e.mIndex,
						&e.mDispframe
					);
					mEffectData[i].mRows = e.mRows;
					mEffectData[i].mCols = e.mCols;
					mEffectData[i].mSize = e.mSize;
					mEffectData[i].mFpk = e.mFpk;
					mEffectData[i].mIndex = e.mIndex;
					mEffectData[i].mDispframe = e.mDispframe;
					if(strcmp(mEffectData[i].mFileName, e.mFileName)!=0)
					{
						mEffectData[i].mpMaterial->Texture()->Load(e.mFileName);
						strcpy(mEffectData[i].mFileName, e.mFileName);
					}
					i++;
				}
				fclose(fp);
			}
			break;
		}
	}
	if (flgPush)
	{
		for (int i = 0; i < strlen(num); i++)
		{
			if (i >= mEffectData.size()) break;
			if (mInput.Key(num[i]))
			{
				new CEffect2(POS,mEffectData[i].mSize, mEffectData[i].mSize
					, mEffectData[i].mpMaterial
					, mEffectData[i].mRows
					, mEffectData[i].mCols
					, mEffectData[i].mFpk
					, mEffectData[i].mIndex
					, mEffectData[i].mDispframe
				);
			}
		}
	}

	/*
	if (mInput.Key('1'))
	{
		new CEffect2(POS, sEffectData[0].mSize, sEffectData[0].mSize
			, sEffectData[0].mpMaterial
			, sEffectData[0].mRows
			, sEffectData[0].mCols
			, sEffectData[0].mFpk
			, sEffectData[0].mIndex
			, sEffectData[0].mDispframe
		);
	}
	if (mInput.Key('2'))
	{
		new CEffect2(POS, sEffectData[1].mSize, sEffectData[1].mSize
			, sEffectData[1].mpMaterial
			, sEffectData[1].mRows
			, sEffectData[1].mCols
			, sEffectData[1].mFpk
			, sEffectData[1].mIndex
			, sEffectData[1].mDispframe
		);
	}
	*/
}