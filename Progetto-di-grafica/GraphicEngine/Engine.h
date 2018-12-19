#pragma once
#define GLM_FORCE_RADIANS
#ifdef _WINDOWS
#ifdef GAUNTLET_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif
#else
#define LIB_API
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LIB_API Engine
{
public:

	void  initEngine(int width, int height);

	void renderMain(int argc, char *argv[]);

	void loadMatrix(glm::mat4 matrix);

	void startLoop();

	void clear();

	void clearColor(float r, float g, float b);

	void beginLines();

	void beginTriangles();

	void beginTriangleStrip();

	void end3D();

	void swapBuffer();

	void loadFile();

	void redisplay();
};
