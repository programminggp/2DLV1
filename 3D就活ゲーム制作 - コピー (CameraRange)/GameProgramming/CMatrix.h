#ifndef CMATRIX_H
#define CMATRIX_H
/*
マトリクスクラス
4行4列の行列データを扱います
*/
class CMatrix {
public:
	//4×4の行列データを設定
	float mM[4][4];
	//表示確認用
	//4×4の行列を画面出力
	void Print();
	//デフォルトコンストラクタ
	CMatrix();
	//単位行列の作成
	CMatrix Identity();
	//回転行列（Y軸）の作成
	//RotateY(角度)
	CMatrix RotateY(float degree);
	//回転行列（X軸）の作成
	//RotateX(角度)
	CMatrix RotateX(float degree);
	//回転行列（Z軸）の作成
	//RotateZ(角度)
	CMatrix RotateZ(float degree);
	//平行移動行列の作成
	//Translate(移動量X, 移動量Y, 移動量Z)
	CMatrix Translate(float x, float y, float z);
	//拡大縮小行列の作成
	//Scale(倍率X, 倍率Y, 倍率Z)
	CMatrix Scale(float x, float y, float z);
	//*演算子のオーバーロード
	//CMatrix * CMatrix の演算結果を返す
	CMatrix operator*(const CMatrix &m);

};

#endif
