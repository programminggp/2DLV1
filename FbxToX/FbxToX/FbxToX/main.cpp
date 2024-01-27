#include <stdio.h>
#include "CModelX.h"

int main()
{
	printf("Hello\n");

	CModelX model;

	model.Load(MODEL_FILE);

	return 0;
}