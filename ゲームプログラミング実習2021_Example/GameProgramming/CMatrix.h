#ifndef CMATRIX_H
#define CMATRIX_H
/*
マトリクスクラス
4行4列の行列データを扱います
*/
class CMatrix {
public:
	union {
		//4×4の行列データを設定
		float mM[4][4];
		//1次元配列として使う
		float mF[16];
	};
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
	//回転行列（Y軸）の作成
	//RotateY(角度)
	CMatrix RotateY(float degree);
	//回転行列（Z軸）の作成
	//RotateZ(角度)
	CMatrix RotateZ(float degree);
	//回転行列（X軸）の作成
	//RotateX(角度)
	CMatrix RotateX(float degree);
	//移動行列の作成
	//Translate(移動量X, 移動量Y, 移動量Z)
	CMatrix Translate(float mx, float my, float mz);
	//*演算子のオーバーロード
	//CMatrix * CMatrix の演算結果を返す
	CMatrix operator*(const CMatrix &m);
	//クオータニオンで回転行列を設定する
	CMatrix SetQuaternion(float x, float y, float z, float w);
	//*演算子のオーバーロード
	//CMatrix * float の演算結果を返す
	CMatrix operator*(const float& f);
	//+演算子のオーバーロード
	//CMatrix1 + CMatrix2 の演算結果を返す
	CMatrix operator+(const CMatrix& m);
	//+=演算子のオーバーロード
	//CMatrix1 += CMatrix2 の演算を行う
	void operator+=(const CMatrix& m);


};
#endif

