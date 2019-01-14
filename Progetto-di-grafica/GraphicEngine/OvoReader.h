#pragma once
#include "Engine.h"

static class OvoReader
{
public:
	static std::vector<Object *> readOVOfile(const char * name);
private:
	static int idCounter;
};

#pragma once
