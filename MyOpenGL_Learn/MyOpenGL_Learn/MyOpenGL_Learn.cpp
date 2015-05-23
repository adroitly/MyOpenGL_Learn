#include "stdafx.h"
#include "windows.h"
#include "FirstGL.h"
#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include <math.h>
#include <GL/gl.h>
#include "GL/GLAUX.H"

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
const int n = 200;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;
using namespace std;
void firstdisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	glFlush();
}
void twodisplay()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	//glBegin(GL_POINTS);
	//glBegin(GL_LINES);
	for (i = 0; i < n; ++i)
		glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
	glEnd();
	glFlush();
}
void displaywujiaoxing()
{
	GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
	GLfloat bx = a * cos(18 * Pi / 180);
	GLfloat by = a * sin(18 * Pi / 180);
	GLfloat cy = -a * cos(18 * Pi / 180);
	GLfloat
		PointA[2] = { 0, a },
		PointB[2] = { bx, by },
		PointC[2] = { 0.5, cy },
		PointD[2] = { -0.5, cy },
		PointE[2] = { -bx, by };

	glClear(GL_COLOR_BUFFER_BIT);
	// 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出
	glBegin(GL_LINE_LOOP);
	glVertex2fv(PointA);
	glVertex2fv(PointC);
	glVertex2fv(PointE);
	glVertex2fv(PointB);
	glVertex2fv(PointD);
	glEnd();
	glFlush();
}
const GLfloat factor = 0.1f;
void threedisplay(void)
{
	GLfloat x;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (x = -1.0f / factor; x < 1.0f / factor; x += 0.01f)
	{
		glVertex2f(x*factor, sin(x)*factor);
	}
	glEnd();
	glFlush();
}
void pointdisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);

	glVertex2f(0.5f, 0.5f);
	glEnd();
	glFlush();
}
void linedisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	//glVertex2f(-0.5f, -0.5f);
	//glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);

	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);

	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);

	glVertex2f(-0.5f, 0.5f);
	glVertex2f(-0.5f, -0.5f);

	glEnd();
	glFlush();
}

void twofacerectdisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT, GL_FILL); // 设置正面为填充模式

	glPolygonMode(GL_BACK, GL_LINE);   // 设置反面为线形模式

	glFrontFace(GL_CCW);               // 设置逆时针方向为正面

	glEnable(GL_CULL_FACE); //启动剔除功能
	glCullFace(GL_BACK);				//glCullFace的参数可以是GL_FRONT，GL_BACK或者GL_FRONT_AND_BACK，分别表示剔除正面、剔除反面、剔除正反两面的多边形。

	glBegin(GL_POLYGON);               // 按逆时针绘制一个正方形，在左下方

	glVertex2f(-0.5f, -0.5f);

	glVertex2f(0.0f, -0.5f);

	glVertex2f(0.0f, 0.0f);

	glVertex2f(-0.5f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);               // 按顺时针绘制一个正方形，在右上方

	glVertex2f(0.0f, 0.0f);

	glVertex2f(0.0f, 0.5f);

	glVertex2f(0.5f, 0.5f);

	glVertex2f(0.5f, 0.0f);

	glEnd();

	glFlush();
}

void bmpdisplay()
{
	static GLubyte Mask[128];

	FILE *fp;

	fp = fopen("mask.bmp", "rb");

	if (!fp)

		exit(0);
	// 移动文件指针到这个位置，使得再读sizeof(Mask)个字节就会遇到文件结束

	// 注意-(int)sizeof(Mask)虽然不是什么好的写法，但这里它确实是正确有效的

	// 如果直接写-sizeof(Mask)的话，因为sizeof取得的是一个无符号数，取负号会有问题
	if (fseek(fp, -(int)sizeof(Mask), SEEK_END))

		exit(0);
	// 读取sizeof(Mask)个字节到Mask
	if (!fread(Mask, sizeof(Mask), 1, fp))

		exit(0);

	fclose(fp);

	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_POLYGON_STIPPLE);

	glPolygonStipple(Mask);

	glRectf(-0.5f, -0.5f, 0.0f, 0.0f);   // 在左下方绘制一个有镂空效果的正方形

	glDisable(GL_POLYGON_STIPPLE);

	glRectf(0.0f, 0.0f, 0.5f, 0.5f);     // 在右上方绘制一个无镂空效果的正方形

	glFlush();
		
}

void colorrectdisplay()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0f, 1.0f, 1.0f);
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	//glFlush();
	//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0f, 1.0f, 1.0f);
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	//glFlush();

	int i;
	glShadeModel(GL_SMOOTH);    // 平滑方式，这也是默认方式
	//glShadeModel(GL_FLAT);      // 单色方式
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for(i=0; i<=8; ++i)
	{
		glColor3f(i&0x04, i&0x02, i&0x01);
		glVertex2f(cos(i*Pi/4), sin(i*Pi/4));
	}
	glEnd();
	glFlush();
}


void mycolortowDisplay()
{

	 int i;
     for(i=0; i<8; ++i)
         auxSetOneColor(i, (float)(i&0x04), (float)(i&0x02), (float)(i&0x01));
     glShadeModel(GL_FLAT);
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_TRIANGLE_FAN);
     glVertex2f(0.0f, 0.0f);
     for(i=0; i<=8; ++i)
     {
         glIndexi(i);
         glVertex2f(cos(i*Pi/4), sin(i*Pi/4));
     }
     glEnd();
     glFlush();
}
// 太阳、地球和月亮
// 假设每个月都是30天
// 一年12个月，共是360天
static int day = 359; // day的变化：从0到359
void earthdisplay(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 400000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);

	// 绘制红色的“太阳”
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(69600000, 20, 20);
	// 绘制蓝色的“地球”
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(150000000, 0.0f, 0.0f);
	glutSolidSphere(15945000, 20, 20);
	// 绘制黄色的“月亮”
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(38000000, 0.0f, 0.0f);
	glutSolidSphere(4345000, 20, 20);

	glFlush();
	glutSwapBuffers();
}
void myIdle(void)
{
	/* 新的函数，在空闲时调用，作用是把日期往后移动一天并重新绘制，达到动画效果 */
	++day;
	if( day >= 360 )
		day = 0;
	earthdisplay();
}
int main(int argc, char * argv[])
{
	FirstGL * fi = new FirstGL(argc, argv);
	glutDisplayFunc(&earthdisplay);
	glutIdleFunc(&myIdle);                // 新加入了这句
	glutMainLoop();



	//auxInitDisplayMode(AUX_SINGLE | AUX_INDEX);
	//auxInitPosition(100, 100, 400, 400);
	//auxInitWindow(L"");
	//mycolortowDisplay();
	////Sleep(10 * 1000);
	//system("pause");

	return 0;
}