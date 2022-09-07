#ifndef CMATRIX_H
#define CMATRIX_H
/*
マトリクスクラス
4行4列の行列データを扱います
*/
class CMatrix {
public:
	//表示確認用
	//4×4の行列を画面出力
	void Print();
	//デフォルトコンストラクタ
	CMatrix();
	//単位行列の作成
	CMatrix Identity();
	//拡大縮小行列の作成
	//Scale(倍率X, 倍率Y, 倍率Z)
	CMatrix Scale(float sx, float sy, float sz);
	//行列値の取得
	//M(行, 列)
	//mM[行][列]を取得
	float M(int r, int c) const;
	//回転行列（Y軸）の作成
	//RotateY(角度)
	CMatrix RotateY(float degree);
	//回転行列（Z軸）の作成
	//RotateZ(角度)
	CMatrix RotateZ(float degree);
	//回転行列（X軸）の作成
	//RotateX(角度)
	CMatrix RotateX(float degree);

private:
	//4×4の行列データを設定
	float mM[4][4];
};
#endif
