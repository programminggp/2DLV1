#ifndef CMATRIX
#define CMATRIX

class CMatrix {
public:
	float mM[4][4];
	CMatrix();
	void Identity();
	void RotateY(float degree);
	void RotateX(float degree);
};

#endif
