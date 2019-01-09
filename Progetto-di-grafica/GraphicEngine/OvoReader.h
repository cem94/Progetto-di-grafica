#pragma once
#include "Object.h"
#include <vector>

static class OvoReader
{
public:
	static std::vector<Object *> readOVOfile(int argc, const char *argv);
	
};

#pragma once
