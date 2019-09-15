#include "CMatrix.h"
#include <stdio.h>

//表示確認用
void CMatrix::Print() {
	printf("%10f %10f %10f %10f \n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%10f %10f %10f %10f \n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%10f %10f %10f %10f \n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f %10f %10f %10f \n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
	/*
	printf("%f %f %f %f \n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%18.8f %18.6f %18.4f %18.2f \n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%.8f %.6f %.4f %.2f \n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f %10f %10f %10f \n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
	*/
}

//デフォルトコンストラクタ
CMatrix::CMatrix() {
	Identity();
}

//単位行列の作成
CMatrix CMatrix::Identity() {
	mM[0][0] = mM[0][1] = mM[0][2] = mM[0][3] = 0.0f;
	mM[1][0] = mM[1][1] = mM[1][2] = mM[1][3] = 0.0f;
	mM[2][0] = mM[2][1] = mM[2][2] = mM[2][3] = 0.0f;
	mM[3][0] = mM[3][1] = mM[3][2] = mM[3][3] = 0.0f;
	mM[0][0] = mM[1][1] = mM[2][2] = mM[3][3] = 1.0f;
	return *this;
}
