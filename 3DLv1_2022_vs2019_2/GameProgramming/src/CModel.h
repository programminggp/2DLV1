#ifndef CMODEL_H
#define CMODEL_H

#include "CVertex.h"
#include <vector>

class CModel
{
public:
	CModel();
	void Render();

	CVertex mVertex[6];
	std::vector<CVertex> mVector;

};

#endif
