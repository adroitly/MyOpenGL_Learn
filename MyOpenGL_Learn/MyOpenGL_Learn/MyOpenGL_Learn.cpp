#include "stdafx.h"
#include "windows.h"
#include "FirstGL.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "iostream"
#include <math.h>
#include <GL/gl.h>
#include "GL/GLAUX.H"


#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

using namespace std;
/* 函数grab
* 抓取窗口中的像素
* 假设窗口宽度为WindowWidth，高度为WindowHeight
*/
float WindowWidth = 400;
float WindowHeight =  400;
#define BMP_Header_Length 54
const int n = 200;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;
void ChangeSize(int w, int h)
{
	WindowWidth = w;
	WindowHeight = h;
}
void grab(const char * _filename)
{

	FILE*     pDummyFile;
	FILE*     pWritingFile;
	GLubyte* pPixelData;
	GLubyte   BMP_Header[BMP_Header_Length];
	GLint     i, j;
	GLint     PixelDataLength;

	// 计算像素数据的实际长度
	//glutReshapeFunc(ChangeSize);
	//glutInitWindowSize(WindowWidth , WindowHeight);
	i = WindowWidth * 3;    // 得到每一行的像素数据长度
	while( i%4 != 0 )       // 补充数据，直到i是的倍数
		++i;                // 本来还有更快的算法，
	// 但这里仅追求直观，对速度没有太高要求
	PixelDataLength = i * WindowHeight;

	// 分配内存和打开文件
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if( pPixelData == 0 )
		exit(0);

	pDummyFile = fopen("dummy.bmp", "rb");
	if( pDummyFile == 0 )
		exit(0);

	pWritingFile = fopen(_filename, "wb");
	if( pWritingFile == 0 )
		exit(0);
	//读取前面的
	glReadBuffer(GL_FRONT);
	// 读取像素
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把dummy.bmp的文件头复制为新文件的文件头
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 写入像素数据
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}
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

	fp = fopen("mytest.bmp", "rb");

	if( !fp )

		exit(0);

	if( fseek(fp, -(int)sizeof(Mask), SEEK_END) )

		exit(0);

	if( !fread(Mask, sizeof(Mask), 1, fp) )

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

double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if( count <= 50 )
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current-last)/(double)CLK_TCK;
	save = 50.0/timegap;
	return save;
}
// 太阳、地球和月亮
// 假设每个月都是30天
// 一年12个月，共是360天
static int day = 359; // day的变化：从0到359
#define WIDTH 400
#define HEIGHT 400

static GLfloat angle = 0.0f;

void lineopen(GLenum linename)
{

	//GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	//GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
	//GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	//glLightfv(linename, GL_POSITION, sun_light_position);
	//glLightfv(linename, GL_AMBIENT,   sun_light_ambient);
	//glLightfv(linename, GL_DIFFUSE,   sun_light_diffuse);
	//glLightfv(linename, GL_SPECULAR, sun_light_specular);
	static const GLfloat light_position[] = {1.0f, 1.0f, -1.0f, 1.0f};
	static const GLfloat light_ambient[]   = {0.2f, 0.2f, 0.2f, 1.0f};
	static const GLfloat light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
	static const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv(linename, GL_POSITION, light_position);
	glLightfv(linename, GL_AMBIENT,   light_ambient);
	glLightfv(linename, GL_DIFFUSE,   light_diffuse);
	glLightfv(linename, GL_SPECULAR, light_specular);
	glEnable(linename);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
void earthdisplay(void)
{
	double FPS = CalFrequency();
	printf("FPS = %f\n", FPS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 创建透视效果视图
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 定义太阳光源，它是一种白色的光源
	{
		lineopen(GL_LIGHT0);
	}

	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_shininess   = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
		glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(2.0, 40, 32);
	}

	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
		GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat earth_mat_shininess   = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
		glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 0.0f, -1.0f, 0.0f);
		glTranslatef(5.0f, 0.0f, 0.0f);
		glutSolidSphere(2.0, 40, 32);
	}

	glutSwapBuffers();
}
void caizhi(float size)
{

	GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat earth_mat_shininess   = size;

	glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
}
#define ColoredVertex(c, v) do{ /*glColor3fv(c);*/lineopen(GL_LIGHT0);caizhi(30.0f); glVertex3fv(v); }while(0)

void d3Rectdisplay()
{
	static int list = 0;
     if( list == 0 )
     {
         // 如果显示列表不存在，则创建
         GLfloat
             PointA[] = { 0.5f, -sqrt(6.0f)/12, -sqrt(3.0f)/6},
             PointB[] = {-0.5f, -sqrt(6.0f)/12, -sqrt(3.0f)/6},
             PointC[] = { 0.0f, -sqrt(6.0f)/12,   sqrt(3.0f)/3},
             PointD[] = { 0.0f,    sqrt(6.0f)/4,              0};
         GLfloat
             ColorR[] = {1, 0, 0},
             ColorG[] = {0, 1, 0},
             ColorB[] = {0, 0, 1},
             ColorY[] = {1, 1, 0};

         list = glGenLists(1);
         glNewList(list, GL_COMPILE);
         glBegin(GL_TRIANGLES);
         // 平面ABC
         ColoredVertex(ColorR, PointA);
         ColoredVertex(ColorG, PointB);
         ColoredVertex(ColorB, PointC);
         // 平面ACD
         ColoredVertex(ColorR, PointA);
         ColoredVertex(ColorB, PointC);
         ColoredVertex(ColorY, PointD);
         // 平面CBD
         ColoredVertex(ColorB, PointC);
         ColoredVertex(ColorG, PointB);
         ColoredVertex(ColorY, PointD);
         // 平面BAD
         ColoredVertex(ColorG, PointB);
         ColoredVertex(ColorR, PointA);
         ColoredVertex(ColorY, PointD);
         glEnd();
         glEndList();

         glEnable(GL_DEPTH_TEST);
     }
	 // 已经创建了显示列表，在每次绘制正四面体时将调用它
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  //glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	 glPushMatrix();
	 glRotatef(angle, 1, 0.5, 0);
	 glCallList(list);
	 glPopMatrix();
	 glutSwapBuffers();

}

void setMatirial(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
{
	static const GLfloat mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	static const GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION,   mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);
}
void mydisplay3dCral()
{

	// 定义一些材质颜色
	const static GLfloat red_color[] = {1.0f, 0.0f, 0.0f, 1.0f};
	const static GLfloat green_color[] = {0.0f, 1.0f, 0.0f, 0.3333f};
	const static GLfloat blue_color[] = {0.0f, 0.0f, 1.0f, 0.5f};

	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 启动混合并设置混合因子
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 设置光源
	lineopen(GL_LIGHT0);

	// 以(0, 0, 0.5)为中心，绘制一个半径为.3的不透明红色球体（离观察者最远）
	setMatirial(red_color, 30.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// 下面将绘制半透明物体了，因此将深度缓冲设置为只读
	glDepthMask(GL_FALSE);

	// 以(0.2, 0, -0.5)为中心，绘制一个半径为.2的半透明蓝色球体（离观察者最近）
	setMatirial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// 以(0.1, 0, 0)为中心，绘制一个半径为.15的半透明绿色球体（在前两个球体之间）
	setMatirial(green_color, 30.0);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// 完成半透明物体的绘制，将深度缓冲区恢复为可读可写的形式
	glDepthMask(GL_TRUE);

	glutSwapBuffers();
	grab("mydisplay3dCral.bmp");
}
void hunheRect()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ZERO);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_ONE, GL_ONE);

	glColor4f(1, 0, 0, 0.5);
	glRectf(-1, -1, 0.5, 0.5);
	glColor4f(0, 1, 0, 0.5);
	glRectf(-0.5, -0.5, 1, 1);

	glutSwapBuffers();
	grab("hunheRect.bmp");
}
void myIdle(void)
{
	//++day;
	//if( day >= 360 )
	//	day = 0;
	angle += 1.0f;
	if( angle >= 360.0f )
		angle = 0.0f;
	mydisplay3dCral();
}
static GLint     ImageWidth;
static GLint     ImageHeight;
static GLint     PixelLength;
static GLubyte* PixelData;
void openfile(char * filename)
{

	// 打开文件
	FILE* pFile = fopen(filename, "rb");
	if( pFile == 0 )
		exit(0);

	// 读取图象的大小信息
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);

	// 计算像素数据长度
	PixelLength = ImageWidth * 3;
	while( PixelLength % 4 != 0 )
		++PixelLength;
	PixelLength *= ImageHeight;

	// 读取像素数据
	PixelData = (GLubyte*)malloc(PixelLength);
	if( PixelData == 0 )
		exit(0);

	fseek(pFile, 54, SEEK_SET);
	fread(PixelData, PixelLength, 1, pFile);

	// 关闭文件
	fclose(pFile);
}
void displaybmp()
{

	// 清除屏幕并不必要
	// 每次绘制时，画面都覆盖整个屏幕
	// 因此无论是否清除屏幕，结果都一样
	// glClear(GL_COLOR_BUFFER_BIT);

	// 绘制像素
	glDrawPixels(ImageWidth, ImageHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	//glRasterPos2f(10 , 10);
	//glPixelZoom(0.5f, 0.8f);
	// 完成绘制
	glutSwapBuffers();
}
void savedisplay()
{

	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f , 0.0f , 0.0f , 0.0f);
	// 绘制
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);     glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     glVertex2f(1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     glVertex2f(0.5f, 1.0f);
	glEnd();
	glPixelZoom(-0.5f, -0.5f);
	glRasterPos2i(1, 1);
	glCopyPixels(WindowWidth/2, WindowHeight/2,
		WindowWidth/2, WindowHeight/2, GL_COLOR);

	// 完成绘制，并抓取图象保存为BMP文件
	glutSwapBuffers();
	grab("saveTest.bmp");
}
int power_of_two(int n)
{
	if( n <= 0 )
		return 0;
	return (n & (n-1)) == 0;
}
/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(char * file_name)
{

	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint texture_ID = 0;
	GLint last_texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if( pFile == 0 )
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while( line_bytes % 4 != 0 )
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if( pixels == 0 )
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if( fread(pixels, total_bytes, 1, pFile) <= 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 在旧版本的OpenGL中
	// 如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 这里并没有检查OpenGL版本，出于对版本兼容性的考虑，按旧版本处理
	// 另外，无论是旧版本还是新版本，
	// 当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，也要进行缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if( !power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max )
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while( new_line_bytes % 4 != 0 )
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if( new_pixels == 0 )
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if( texture_ID == 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	// 之前为pixels分配的内存可在使用glTexImage2D以后释放
	// 因为此时像素数据已经被OpenGL另行保存了一份（可能被保存到专门的图形硬件中）
	free(pixels);
	fclose(pFile);
	return texture_ID;
}
/* 将当前纹理BGR格式转换为BGRA格式
* 纹理中像素的RGB值如果与指定rgb相差不超过absolute，则将Alpha设置为0.0，否则设置为1.0
*/
void texture_colorkey(GLubyte r, GLubyte g, GLubyte b, GLubyte absolute)
{

	GLint width, height;

	GLubyte * pixels = 0;


	//获取纹理大小
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D , 0 , GL_TEXTURE_HEIGHT , & height);

	pixels = (GLubyte *)malloc(width * height * 4);
	if (pixels == 0)
	{
		return;
	}

	glGetTexImage(GL_TEXTURE_2D , 0 , GL_BGRA_EXT , GL_UNSIGNED_BYTE , pixels);

	// 修改像素中的Alpha值
	// 其中pixels[i*4], pixels[i*4+1], pixels[i*4+2], pixels[i*4+3]
	//    分别表示第i个像素的蓝、绿、红、Alpha四种分量，0表示最小，255表示最大
	{

		GLint i;
		GLint count = width * height;
		for(i = 0 ; i < count ; ++ i)
		{

			if (abs(pixels[i * 4] - b ) <= absolute && abs(pixels[i*4+1] - g) <= absolute
				&& abs(pixels[i*4+2] - r) <= absolute )
			{
				pixels[i * 4 + 3] = 0;
			}
			else
			{
				pixels[ i * 4 + 3] = 255;
			}
		}
	}
	 // 将修改后的像素重新设置到纹理中，释放内存
	glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGBA , width , height , 0 , GL_BGRA_EXT , GL_UNSIGNED_BYTE , pixels);
	free(pixels);
}
/* 两个纹理对象的编号
*/
GLuint texGround;
GLuint texWall;
void useTexture_display()
{

	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);

	// 使用“地”纹理绘制土地
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();
	// 使用“墙”纹理绘制栅栏
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// 旋转后再绘制一个
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// 旋转后再绘制一个
	glRotatef(-180, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// 旋转后再绘制一个
	glRotatef(-270, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// 交换缓冲区，并保存像素数据到文件
	glutSwapBuffers();
	grab("useTexture.bmp");
}
void Alphadisplay(void)
{
	static int initialized    = 0;
	static GLuint texWindow   = 0;
	static GLuint texPicture = 0;

	// 执行初始化操作，包括：读取相片，读取相框，将相框由BGR颜色转换为BGRA，启用二维纹理
	if( !initialized )
	{
		texPicture = load_texture("pic.bmp");
		texWindow   = load_texture("window.bmp");
		glBindTexture(GL_TEXTURE_2D, texWindow);
		texture_colorkey(255, 255, 255, 10);

		glEnable(GL_TEXTURE_2D);

		initialized = 1;
	}

	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT);

	// 绘制相片，此时不需要进行Alpha测试，所有的像素都进行绘制
	glBindTexture(GL_TEXTURE_2D, texPicture);
	glDisable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);      glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0, 1);      glVertex2f(-1.0f,   1.0f);
	glTexCoord2f(1, 1);      glVertex2f( 1.0f,   1.0f);
	glTexCoord2f(1, 0);      glVertex2f( 1.0f, -1.0f);
	glEnd();

	// 绘制相框，此时进行Alpha测试，只绘制不透明部分的像素
	glBindTexture(GL_TEXTURE_2D, texWindow);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);      glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0, 1);      glVertex2f(-1.0f,   1.0f);
	glTexCoord2f(1, 1);      glVertex2f( 1.0f,   1.0f);
	glTexCoord2f(1, 0);      glVertex2f( 1.0f, -1.0f);
	glEnd();

	// 交换缓冲
	glutSwapBuffers();
	grab("Alpha.bmp");
}

void draw_sphere()
{

	// 设置光源
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	{

		GLfloat pos[]  = {5.0f, 5.0f, 0.0f, 1.0f},
			ambient[] = {0.0f, 0.0f, 1.0f, 1.0f};
		glLightfv(GL_LIGHT0 , GL_POSITION , pos);
		glLightfv(GL_LIGHT0 , GL_AMBIENT , ambient);

	}

	//绘制一个球体
	glColor3f(1 , 0 , 0);
	glPushMatrix();
	glTranslatef(0 , 0 , 2);
	glutSolidSphere(0.5 , 20 , 20);
	glPopMatrix();
}

void modeldisplay()
{

	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 设置观察点
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 5, 25);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 0, 6.5, 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);

	// 绘制球体
	glDisable(GL_STENCIL_TEST);
	draw_sphere();

	// 绘制一个平面镜。在绘制的同时注意设置模板缓冲。
	// 另外，为了保证平面镜之后的镜像能够正确绘制，在绘制平面镜时需要将深度缓冲区设置为只读的。
	// 在绘制时暂时关闭光照效果
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_STENCIL_TEST);

	glDisable(GL_LIGHTING);
	glColor3f(0.5f, 0.5f, 0.5f);
	glDepthMask(GL_FALSE);
	glRectf(-1.5f, -1.5f, 1.5f, 1.5f);
	glDepthMask(GL_TRUE);

	// 绘制一个与先前球体关于平面镜对称的球体，注意光源的位置也要发生对称改变
	// 因为平面镜是在X轴和Y轴所确定的平面，所以只要Z坐标取反即可实现对称
	// 为了保证球体的绘制范围被限制在平面镜内部，使用模板测试
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glScalef(1.0f, 1.0f, -1.0f);
	draw_sphere();

	// 交换缓冲
	glutSwapBuffers();

	// 截图
	grab("modeldisplay.bmp");

}
void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// 计算字符的个数
	// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
	// 否则一个字节算一个字符
	len = 0;
	for(i=0; str[i]!='\0'; ++i)
	{
		if( IsDBCSLeadByte(str[i]) )
			++i;
		++len;
	}

	// 将混合字符转化为宽字符
	wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// 逐个输出字符
	for(i=0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// 回收所有临时资源
	free(wstring);
	glDeleteLists(list, 1);
}
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}
// ASCII字符总共只有0到127，一共128种字符
#define MAX_CHAR       128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if( isFirstCall ) { // 如果是第一次调用，执行初始化
		// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for(; *str!='\0'; ++str)
		glCallList(lists + *str);
}
void DrawTypeface()
{

	glClear(GL_COLOR_BUFFER_BIT);

	selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.7f, 0.4f);
	drawString("Hello, World!");

	selectFont(48, GB2312_CHARSET, "楷体_GB2312");
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos2f(-0.7f, -0.1f);
	drawCNString("当代的中国汉字");

	selectFont(48, DEFAULT_CHARSET, "华文仿宋");
	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos2f(-0.7f, -0.6f);
	drawCNString("傳統的中國漢字");

	glutSwapBuffers();
	grab("DrawTypeface.bmp");
}

int main(int argc, char * argv[])
{
	//openfile("dummy.bmp");
	const char* version = (const char*)glGetString(GL_VERSION);
	printf("OpenGL 版本：%s\n", version);
	FirstGL * fi = new FirstGL(argc, argv);
	glutDisplayFunc(&DrawTypeface);
	////glutIdleFunc(&myIdle);    
	// 在这里做一些初始化
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	//texGround = load_texture("ground.bmp");
	//texWall = load_texture("wall.bmp");
	glutMainLoop();
	 //free(PixelData);
	//Shell(argc , argv);


	//auxInitDisplayMode(AUX_SINGLE | AUX_INDEX);
	//auxInitPosition(100, 100, 400, 400);
	//auxInitWindow(L"");
	//mycolortowDisplay();
	////Sleep(10 * 1000);
	//system("pause");

	return 0;
}