#pragma once
#include "init.h"

class ModelObject {
public:
	int countFaces;
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;


};