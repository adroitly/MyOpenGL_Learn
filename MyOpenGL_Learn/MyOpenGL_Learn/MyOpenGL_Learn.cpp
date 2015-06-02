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
/* ����grab
* ץȡ�����е�����
* ���贰�ڿ��ΪWindowWidth���߶�ΪWindowHeight
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

	// �����������ݵ�ʵ�ʳ���
	//glutReshapeFunc(ChangeSize);
	//glutInitWindowSize(WindowWidth , WindowHeight);
	i = WindowWidth * 3;    // �õ�ÿһ�е��������ݳ���
	while( i%4 != 0 )       // �������ݣ�ֱ��i�ǵı���
		++i;                // �������и�����㷨��
	// �������׷��ֱ�ۣ����ٶ�û��̫��Ҫ��
	PixelDataLength = i * WindowHeight;

	// �����ڴ�ʹ��ļ�
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if( pPixelData == 0 )
		exit(0);

	pDummyFile = fopen("dummy.bmp", "rb");
	if( pDummyFile == 0 )
		exit(0);

	pWritingFile = fopen(_filename, "wb");
	if( pWritingFile == 0 )
		exit(0);
	//��ȡǰ���
	glReadBuffer(GL_FRONT);
	// ��ȡ����
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// д����������
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// �ͷ��ڴ�͹ر��ļ�
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
	// ����A->C->E->B->D->A��˳�򣬿���һ�ʽ�����ǻ���
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
	glVertex2f(1.0f, 0.0f);         // ������������Ի�x��
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // ������������Ի�y��
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

	glPolygonMode(GL_FRONT, GL_FILL); // ��������Ϊ���ģʽ

	glPolygonMode(GL_BACK, GL_LINE);   // ���÷���Ϊ����ģʽ

	glFrontFace(GL_CCW);               // ������ʱ�뷽��Ϊ����

	glEnable(GL_CULL_FACE); //�����޳�����
	glCullFace(GL_BACK);				//glCullFace�Ĳ���������GL_FRONT��GL_BACK����GL_FRONT_AND_BACK���ֱ��ʾ�޳����桢�޳����桢�޳���������Ķ���Ρ�

	glBegin(GL_POLYGON);               // ����ʱ�����һ�������Σ������·�

	glVertex2f(-0.5f, -0.5f);

	glVertex2f(0.0f, -0.5f);

	glVertex2f(0.0f, 0.0f);

	glVertex2f(-0.5f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);               // ��˳ʱ�����һ�������Σ������Ϸ�

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

	glRectf(-0.5f, -0.5f, 0.0f, 0.0f);   // �����·�����һ�����ο�Ч����������

	glDisable(GL_POLYGON_STIPPLE);

	glRectf(0.0f, 0.0f, 0.5f, 0.5f);     // �����Ϸ�����һ�����ο�Ч����������

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
	glShadeModel(GL_SMOOTH);    // ƽ����ʽ����Ҳ��Ĭ�Ϸ�ʽ
	//glShadeModel(GL_FLAT);      // ��ɫ��ʽ
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
// ̫�������������
// ����ÿ���¶���30��
// һ��12���£�����360��
static int day = 359; // day�ı仯����0��359
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

	// ����͸��Ч����ͼ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
	{
		lineopen(GL_LIGHT0);
	}

	// ����̫���Ĳ��ʲ�����̫��
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

	// �������Ĳ��ʲ����Ƶ���
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
         // �����ʾ�б����ڣ��򴴽�
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
         // ƽ��ABC
         ColoredVertex(ColorR, PointA);
         ColoredVertex(ColorG, PointB);
         ColoredVertex(ColorB, PointC);
         // ƽ��ACD
         ColoredVertex(ColorR, PointA);
         ColoredVertex(ColorB, PointC);
         ColoredVertex(ColorY, PointD);
         // ƽ��CBD
         ColoredVertex(ColorB, PointC);
         ColoredVertex(ColorG, PointB);
         ColoredVertex(ColorY, PointD);
         // ƽ��BAD
         ColoredVertex(ColorG, PointB);
         ColoredVertex(ColorR, PointA);
         ColoredVertex(ColorY, PointD);
         glEnd();
         glEndList();

         glEnable(GL_DEPTH_TEST);
     }
	 // �Ѿ���������ʾ�б���ÿ�λ�����������ʱ��������
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

	// ����һЩ������ɫ
	const static GLfloat red_color[] = {1.0f, 0.0f, 0.0f, 1.0f};
	const static GLfloat green_color[] = {0.0f, 1.0f, 0.0f, 0.3333f};
	const static GLfloat blue_color[] = {0.0f, 0.0f, 1.0f, 0.5f};

	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ������ϲ����û������
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���ù�Դ
	lineopen(GL_LIGHT0);

	// ��(0, 0, 0.5)Ϊ���ģ�����һ���뾶Ϊ.3�Ĳ�͸����ɫ���壨��۲�����Զ��
	setMatirial(red_color, 30.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// ���潫���ư�͸�������ˣ���˽���Ȼ�������Ϊֻ��
	glDepthMask(GL_FALSE);

	// ��(0.2, 0, -0.5)Ϊ���ģ�����һ���뾶Ϊ.2�İ�͸����ɫ���壨��۲��������
	setMatirial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// ��(0.1, 0, 0)Ϊ���ģ�����һ���뾶Ϊ.15�İ�͸����ɫ���壨��ǰ��������֮�䣩
	setMatirial(green_color, 30.0);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// ��ɰ�͸������Ļ��ƣ�����Ȼ������ָ�Ϊ�ɶ���д����ʽ
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

	// ���ļ�
	FILE* pFile = fopen(filename, "rb");
	if( pFile == 0 )
		exit(0);

	// ��ȡͼ��Ĵ�С��Ϣ
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);

	// �����������ݳ���
	PixelLength = ImageWidth * 3;
	while( PixelLength % 4 != 0 )
		++PixelLength;
	PixelLength *= ImageHeight;

	// ��ȡ��������
	PixelData = (GLubyte*)malloc(PixelLength);
	if( PixelData == 0 )
		exit(0);

	fseek(pFile, 54, SEEK_SET);
	fread(PixelData, PixelLength, 1, pFile);

	// �ر��ļ�
	fclose(pFile);
}
void displaybmp()
{

	// �����Ļ������Ҫ
	// ÿ�λ���ʱ�����涼����������Ļ
	// ��������Ƿ������Ļ�������һ��
	// glClear(GL_COLOR_BUFFER_BIT);

	// ��������
	glDrawPixels(ImageWidth, ImageHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	//glRasterPos2f(10 , 10);
	//glPixelZoom(0.5f, 0.8f);
	// ��ɻ���
	glutSwapBuffers();
}
void savedisplay()
{

	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f , 0.0f , 0.0f , 0.0f);
	// ����
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);     glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     glVertex2f(1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     glVertex2f(0.5f, 1.0f);
	glEnd();
	glPixelZoom(-0.5f, -0.5f);
	glRasterPos2i(1, 1);
	glCopyPixels(WindowWidth/2, WindowHeight/2,
		WindowWidth/2, WindowHeight/2, GL_COLOR);

	// ��ɻ��ƣ���ץȡͼ�󱣴�ΪBMP�ļ�
	glutSwapBuffers();
	grab("saveTest.bmp");
}
int power_of_two(int n)
{
	if( n <= 0 )
		return 0;
	return (n & (n-1)) == 0;
}
/* ����load_texture
* ��ȡһ��BMP�ļ���Ϊ����
* ���ʧ�ܣ�����0������ɹ�������������
*/
GLuint load_texture(char * file_name)
{

	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint texture_ID = 0;
	GLint last_texture_ID = 0;

	// ���ļ������ʧ�ܣ�����
	FILE* pFile = fopen(file_name, "rb");
	if( pFile == 0 )
		return 0;

	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	{
		GLint line_bytes = width * 3;
		while( line_bytes % 4 != 0 )
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// �����������ֽ��������ڴ�
	pixels = (GLubyte*)malloc(total_bytes);
	if( pixels == 0 )
	{
		fclose(pFile);
		return 0;
	}

	// ��ȡ��������
	if( fread(pixels, total_bytes, 1, pFile) <= 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// �ھɰ汾��OpenGL��
	// ���ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
	// ���ﲢû�м��OpenGL�汾�����ڶ԰汾�����ԵĿ��ǣ����ɰ汾����
	// ���⣬�����Ǿɰ汾�����°汾��
	// ��ͼ��Ŀ�Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ��ҲҪ��������
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if( !power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max )
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// ����ÿ����Ҫ���ֽ��������ֽ���
			new_line_bytes = new_width * 3;
			while( new_line_bytes % 4 != 0 )
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// �����ڴ�
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if( new_pixels == 0 )
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// ������������
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// ����һ���µ�������
	glGenTextures(1, &texture_ID);
	if( texture_ID == 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// ���µ������������������������
	// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
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

	// ֮ǰΪpixels������ڴ����ʹ��glTexImage2D�Ժ��ͷ�
	// ��Ϊ��ʱ���������Ѿ���OpenGL���б�����һ�ݣ����ܱ����浽ר�ŵ�ͼ��Ӳ���У�
	free(pixels);
	fclose(pFile);
	return texture_ID;
}
/* ����ǰ����BGR��ʽת��ΪBGRA��ʽ
* ���������ص�RGBֵ�����ָ��rgb������absolute����Alpha����Ϊ0.0����������Ϊ1.0
*/
void texture_colorkey(GLubyte r, GLubyte g, GLubyte b, GLubyte absolute)
{

	GLint width, height;

	GLubyte * pixels = 0;


	//��ȡ�����С
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D , 0 , GL_TEXTURE_HEIGHT , & height);

	pixels = (GLubyte *)malloc(width * height * 4);
	if (pixels == 0)
	{
		return;
	}

	glGetTexImage(GL_TEXTURE_2D , 0 , GL_BGRA_EXT , GL_UNSIGNED_BYTE , pixels);

	// �޸������е�Alphaֵ
	// ����pixels[i*4], pixels[i*4+1], pixels[i*4+2], pixels[i*4+3]
	//    �ֱ��ʾ��i�����ص������̡��졢Alpha���ַ�����0��ʾ��С��255��ʾ���
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
	 // ���޸ĺ�������������õ������У��ͷ��ڴ�
	glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGBA , width , height , 0 , GL_BGRA_EXT , GL_UNSIGNED_BYTE , pixels);
	free(pixels);
}
/* �����������ı��
*/
GLuint texGround;
GLuint texWall;
void useTexture_display()
{

	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �����ӽ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);

	// ʹ�á��ء������������
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();
	// ʹ�á�ǽ���������դ��
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// ��ת���ٻ���һ��
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// ��ת���ٻ���һ��
	glRotatef(-180, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// ��ת���ٻ���һ��
	glRotatef(-270, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// �������������������������ݵ��ļ�
	glutSwapBuffers();
	grab("useTexture.bmp");
}
void Alphadisplay(void)
{
	static int initialized    = 0;
	static GLuint texWindow   = 0;
	static GLuint texPicture = 0;

	// ִ�г�ʼ����������������ȡ��Ƭ����ȡ��򣬽������BGR��ɫת��ΪBGRA�����ö�ά����
	if( !initialized )
	{
		texPicture = load_texture("pic.bmp");
		texWindow   = load_texture("window.bmp");
		glBindTexture(GL_TEXTURE_2D, texWindow);
		texture_colorkey(255, 255, 255, 10);

		glEnable(GL_TEXTURE_2D);

		initialized = 1;
	}

	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT);

	// ������Ƭ����ʱ����Ҫ����Alpha���ԣ����е����ض����л���
	glBindTexture(GL_TEXTURE_2D, texPicture);
	glDisable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);      glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0, 1);      glVertex2f(-1.0f,   1.0f);
	glTexCoord2f(1, 1);      glVertex2f( 1.0f,   1.0f);
	glTexCoord2f(1, 0);      glVertex2f( 1.0f, -1.0f);
	glEnd();

	// ������򣬴�ʱ����Alpha���ԣ�ֻ���Ʋ�͸�����ֵ�����
	glBindTexture(GL_TEXTURE_2D, texWindow);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);      glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0, 1);      glVertex2f(-1.0f,   1.0f);
	glTexCoord2f(1, 1);      glVertex2f( 1.0f,   1.0f);
	glTexCoord2f(1, 0);      glVertex2f( 1.0f, -1.0f);
	glEnd();

	// ��������
	glutSwapBuffers();
	grab("Alpha.bmp");
}

void draw_sphere()
{

	// ���ù�Դ
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	{

		GLfloat pos[]  = {5.0f, 5.0f, 0.0f, 1.0f},
			ambient[] = {0.0f, 0.0f, 1.0f, 1.0f};
		glLightfv(GL_LIGHT0 , GL_POSITION , pos);
		glLightfv(GL_LIGHT0 , GL_AMBIENT , ambient);

	}

	//����һ������
	glColor3f(1 , 0 , 0);
	glPushMatrix();
	glTranslatef(0 , 0 , 2);
	glutSolidSphere(0.5 , 20 , 20);
	glPopMatrix();
}

void modeldisplay()
{

	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ���ù۲��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 5, 25);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 0, 6.5, 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);

	// ��������
	glDisable(GL_STENCIL_TEST);
	draw_sphere();

	// ����һ��ƽ�澵���ڻ��Ƶ�ͬʱע������ģ�建�塣
	// ���⣬Ϊ�˱�֤ƽ�澵֮��ľ����ܹ���ȷ���ƣ��ڻ���ƽ�澵ʱ��Ҫ����Ȼ���������Ϊֻ���ġ�
	// �ڻ���ʱ��ʱ�رչ���Ч��
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

	// ����һ������ǰ�������ƽ�澵�ԳƵ����壬ע���Դ��λ��ҲҪ�����ԳƸı�
	// ��Ϊƽ�澵����X���Y����ȷ����ƽ�棬����ֻҪZ����ȡ������ʵ�ֶԳ�
	// Ϊ�˱�֤����Ļ��Ʒ�Χ��������ƽ�澵�ڲ���ʹ��ģ�����
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glScalef(1.0f, 1.0f, -1.0f);
	draw_sphere();

	// ��������
	glutSwapBuffers();

	// ��ͼ
	grab("modeldisplay.bmp");

}
void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// �����ַ��ĸ���
	// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	// ����һ���ֽ���һ���ַ�
	len = 0;
	for(i=0; str[i]!='\0'; ++i)
	{
		if( IsDBCSLeadByte(str[i]) )
			++i;
		++len;
	}

	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// �������ַ�
	for(i=0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// ����������ʱ��Դ
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
// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR       128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if( isFirstCall ) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
		// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
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

	selectFont(48, GB2312_CHARSET, "����_GB2312");
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos2f(-0.7f, -0.1f);
	drawCNString("�������й�����");

	selectFont(48, DEFAULT_CHARSET, "���ķ���");
	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos2f(-0.7f, -0.6f);
	drawCNString("���y���Ї��h��");

	glutSwapBuffers();
	grab("DrawTypeface.bmp");
}

int main(int argc, char * argv[])
{
	//openfile("dummy.bmp");
	const char* version = (const char*)glGetString(GL_VERSION);
	printf("OpenGL �汾��%s\n", version);
	FirstGL * fi = new FirstGL(argc, argv);
	glutDisplayFunc(&DrawTypeface);
	////glutIdleFunc(&myIdle);    
	// ��������һЩ��ʼ��
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