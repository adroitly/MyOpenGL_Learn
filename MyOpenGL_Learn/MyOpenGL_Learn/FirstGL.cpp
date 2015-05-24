#include "stdafx.h"
#include "windows.h"
#include "FirstGL.h"


FirstGL::FirstGL()
{
}

FirstGL::FirstGL(int argc, char *argv[])
{
	glutInit(&argc, argv);

	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(400, 400);

	glutCreateWindow("OpenGL");

	//glutDisplayFunc(&this->myDisplay);
	//glClear(GL_COLOR_BUFFER_BIT);

	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	//glFlush();

	//glutMainLoop();
	//system("pause");
}

FirstGL::~FirstGL()
{
	delete this;
}
void FirstGL::myDisplay()

{

	glClear(GL_COLOR_BUFFER_BIT);

	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	glFlush();

}
