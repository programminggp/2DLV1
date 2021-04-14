#ifndef CMODEL_H
#define CMODEL_H

#define MODEL_FILE "sample.blend.x"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}

class CModelX {
public:
	char* mpPointer;
	char mToken[1024];

	CModelX()
		: mpPointer(nullptr)
	{}

	void Load(char* file);

};

#endif
