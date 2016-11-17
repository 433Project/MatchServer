#include "LatencyGenerator.h"
#include <cstdlib>

LatencyGenerator::LatencyGenerator()
{
}


LatencyGenerator::~LatencyGenerator()
{
}

double LatencyGenerator::Generate() {
	return (double) rand() / (double)RAND_MAX;
}