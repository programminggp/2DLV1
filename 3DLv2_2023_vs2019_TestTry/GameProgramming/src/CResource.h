#pragma once
class CResourceManager;

// リソース管理するクラスのベースクラス
class CResource
{
	friend CResourceManager;

public:
	// 参照カウント加算
	void Referenced();
	// リソース解放
	virtual void Release();

protected:
	// コンストラクタ
	CResource();
	// デストラクタ
	virtual ~CResource();

	// シーン切り替えで削除するかどうかを設定
	void SetDontDelete(bool del);
	// リソース読み込み
	virtual bool Load(std::string path, bool dontDelete) = 0;

	EScene mSceneType;		// 所属するシーンの種類
	int mReferenceCount;	// 参照カウント
};