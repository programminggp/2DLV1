#pragma once
#include "CVector.h"

// 矩形クラス
class CRect
{
public:
	// コンストラクタ（引数なし）
	CRect();
	// コンストラクタ（xywh）
	CRect(float x, float y, float w, float h);
	// コンストラクタ（pos + size）
	CRect(const CVector2& pos, const CVector2& size);
	// デストラクタ
	~CRect();

	/// <summary>
	/// 矩形情報の設定
	/// </summary>
	/// <param name="x">X軸の開始位置</param>
	/// <param name="y">Y軸の開始位置</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void Set(float x, float y, float w, float h);
	/// <summary>
	/// 矩形情報の設定（CVector2）
	/// </summary>
	/// <param name="pos">開始位置</param>
	/// <param name="size">サイズ</param>
	void Set(const CVector2& pos, const CVector2& size);

	/// <summary>
	/// 矩形の開始位置を設定
	/// </summary>
	/// <param name="x">X軸の開始位置</param>
	/// <param name="y">Y軸の開始位置</param>
	void SetPos(float x, float y);
	/// <summary>
	/// 矩形の開始位置を設定（CVector2）
	/// </summary>
	/// <param name="pos">開始位置</param>
	void SetPos(const CVector2& pos);
	/// <summary>
	/// 矩形の開始位置を取得
	/// </summary>
	/// <returns></returns>
	const CVector2& GetPos() const;

	/// <summary>
	/// 矩形のサイズを設定
	/// </summary>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void SetSize(float w, float h);
	/// <summary>
	/// 矩形のサイズを設定（CVector2）
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(const CVector2& size);
	/// <summary>
	/// 矩形のサイズを取得
	/// </summary>
	/// <returns></returns>
	const CVector2& GetSize() const;

	float X() const;
	void X(float x);
	float Y() const;
	void Y(float y);
	float W() const;
	void W(float w);
	float H() const;
	void H(float h);

private:
	CVector2 mPosition;	// 矩形の開始位置
	CVector2 mSize;		// 矩形のサイズ
};
