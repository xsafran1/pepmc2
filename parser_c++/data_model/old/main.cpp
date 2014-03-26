#include "Normalizer.h"
#include "Model.h"

int main()
{
	Model model;

	model.AddVariable("X0");
	model.AddParam("gfi");

	Normalizer normalizer;

	normalizer.PutRmCoor("X0", 0.156, 0.5465, 0.41541, 0.214);

	return 0;
}