#ifndef CEFFECT_H
#define CEFFECT_H
//ビルボードクラスのインクルード
#include "CBillBoard.h"
/*
エフェクトクラス
テクスチャのアニメーション
*/
class CEffect : public CBillBoard {
public:
	enum EType {
		EANIMATION,
		EFADE,
	};
	void Animation();
	void Fade();
	//コンストラクタ
	//CEffect(位置, 幅, 高さ, テクスチャ名, 行数, 列数, 1コマあたりのフレーム数)　行数、列数、フレーム数はデフォルト引数で呼出し時省略可能
	CEffect(const CVector &pos, float w, float h, char *texture, int row = 1, int col = 1, int fps = 1);
	//CEffect(位置, 幅, 高さ, 行数, 列数, 1コマあたりのフレーム数)　行数、列数、フレーム数はデフォルト引数で呼出し時省略可能
	CEffect(const CVector& pos, float w, float h, int row = 1, int col = 1, int fps = 1, EType type = EANIMATION, int frame = 0);
	//更新
	void Update();
	//描画
	void Render();
	void Render(CMaterial* material);
private:
	int mFadeCount;
	EType mType;
	//行数
	int mRows;
	//列数
	int mCols;
	//1コマのフレーム数
	int mFps;
	//フレームカウンタ
	int mFrame;
	//マテリアル
	static CMaterial sMaterial;
};


class CEffectDarkness17 : public CEffect
{
public:
	//コンストラクタ(位置, 幅, 高さ, 行数, 列数, 1コマあたりのフレーム数)　行数、列数、フレーム数はデフォルト引数で呼出し時省略可能
	CEffectDarkness17(const CVector& pos, float w, float h, int row = 1, int col = 1, int fps = 1);

	void Render();
private:
	static CMaterial sMaterial;
};

class CEffectFire7 : public CEffect
{
public:
	//コンストラクタ(位置, 幅, 高さ, 行数, 列数, 1コマあたりのフレーム数)　行数、列数、フレーム数はデフォルト引数で呼出し時省略可能
	CEffectFire7(const CVector& pos, float w, float h, int row = 1, int col = 1, int fps = 1, EType type = EANIMATION, int frame = 0);

	void Render();
private:
	static CMaterial sMaterial;
};

#endif

