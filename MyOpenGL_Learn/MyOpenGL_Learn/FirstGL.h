#pragma once
#include "glut.h"
#include <GL/gl.h>
#include <glut.h>

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut.lib")
class FirstGL
{
public:
	FirstGL();;
	FirstGL(int argc, char *argv[]);
	~FirstGL();
	void myDisplay(void);
};

