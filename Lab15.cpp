#include "bmpfuncs.h"
#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include "GL/glext.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.141592
double g_nGLWidth = 800;
double g_nGLHeight = 600;
double phi, theta, radius = 10;
double upVector = cos(phi * PI / 180);
double eyex, eyey, eyez;

GLuint g_nCubeTex; //환경맵 set variable
GLUquadricObj* qobj = gluNewQuadric();
void resize(int, int);
bool gluInvertMatrix(const GLfloat* , GLfloat* );
void special_keyboard(int , int , int);
void init();
void draw();
void draw_skyBox();
void draw_sphere();
void environmentMapsetting();


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_nGLWidth, g_nGLHeight);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12171841 임재형");
	init();

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	glutDisplayFunc(draw);
	glutSpecialFunc(special_keyboard);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}
bool gluInvertMatrix(const GLfloat* m, GLfloat* inv) {
	float det;

	inv[0] =
		+m[5] * m[10] * m[15]
		- m[5] * m[11] * m[14]
		- m[9] * m[6] * m[15]
		+ m[9] * m[7] * m[14]
		+ m[13] * m[6] * m[11]
		- m[13] * m[7] * m[10];

	inv[1] =
		-m[1] * m[10] * m[15]
		+ m[1] * m[11] * m[14]
		+ m[9] * m[2] * m[15]
		- m[9] * m[3] * m[14]
		- m[13] * m[2] * m[11]
		+ m[13] * m[3] * m[10];

	inv[2] =
		+m[1] * m[6] * m[15]
		- m[1] * m[7] * m[14]
		- m[5] * m[2] * m[15]
		+ m[5] * m[3] * m[14]
		+ m[13] * m[2] * m[7]
		- m[13] * m[3] * m[6];

	inv[3] =
		-m[1] * m[6] * m[11]
		+ m[1] * m[7] * m[10]
		+ m[5] * m[2] * m[11]
		- m[5] * m[3] * m[10]
		- m[9] * m[2] * m[7]
		+ m[9] * m[3] * m[6];

	inv[4] =
		-m[4] * m[10] * m[15]
		+ m[4] * m[11] * m[14]
		+ m[8] * m[6] * m[15]
		- m[8] * m[7] * m[14]
		- m[12] * m[6] * m[11]
		+ m[12] * m[7] * m[10];

	inv[5] =
		+m[0] * m[10] * m[15]
		- m[0] * m[11] * m[14]
		- m[8] * m[2] * m[15]
		+ m[8] * m[3] * m[14]
		+ m[12] * m[2] * m[11]
		- m[12] * m[3] * m[10];

	inv[6] =
		-m[0] * m[6] * m[15]
		+ m[0] * m[7] * m[14]
		+ m[4] * m[2] * m[15]
		- m[4] * m[3] * m[14]
		- m[12] * m[2] * m[7]
		+ m[12] * m[3] * m[6];

	inv[7] =
		+m[0] * m[6] * m[11]
		- m[0] * m[7] * m[10]
		- m[4] * m[2] * m[11]
		+ m[4] * m[3] * m[10]
		+ m[8] * m[2] * m[7]
		- m[8] * m[3] * m[6];

	inv[8] =
		+m[4] * m[9] * m[15]
		- m[4] * m[11] * m[13]
		- m[8] * m[5] * m[15]
		+ m[8] * m[7] * m[13]
		+ m[12] * m[5] * m[11]
		- m[12] * m[7] * m[9];

	inv[9] =
		-m[0] * m[9] * m[15]
		+ m[0] * m[11] * m[13]
		+ m[8] * m[1] * m[15]
		- m[8] * m[3] * m[13]
		- m[12] * m[1] * m[11]
		+ m[12] * m[3] * m[9];

	inv[10] =
		+m[0] * m[5] * m[15]
		- m[0] * m[7] * m[13]
		- m[4] * m[1] * m[15]
		+ m[4] * m[3] * m[13]
		+ m[12] * m[1] * m[7]
		- m[12] * m[3] * m[5];

	inv[11] =
		-m[0] * m[5] * m[11]
		+ m[0] * m[7] * m[9]
		+ m[4] * m[1] * m[11]
		- m[4] * m[3] * m[9]
		- m[8] * m[1] * m[7]
		+ m[8] * m[3] * m[5];

	inv[12] =
		-m[4] * m[9] * m[14]
		+ m[4] * m[10] * m[13]
		+ m[8] * m[5] * m[14]
		- m[8] * m[6] * m[13]
		- m[12] * m[5] * m[10]
		+ m[12] * m[6] * m[9];

	inv[13] =
		+m[0] * m[9] * m[14]
		- m[0] * m[10] * m[13]
		- m[8] * m[1] * m[14]
		+ m[8] * m[2] * m[13]
		+ m[12] * m[1] * m[10]
		- m[12] * m[2] * m[9];

	inv[14] =
		-m[0] * m[5] * m[14]
		+ m[0] * m[6] * m[13]
		+ m[4] * m[1] * m[14]
		- m[4] * m[2] * m[13]
		- m[12] * m[1] * m[6]
		+ m[12] * m[2] * m[5];

	inv[15] =
		+m[0] * m[5] * m[10]
		- m[0] * m[6] * m[9]
		- m[4] * m[1] * m[10]
		+ m[4] * m[2] * m[9]
		+ m[8] * m[1] * m[6]
		- m[8] * m[2] * m[5];

	/* Compute determinant: */

	det = +m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	if (det == 0) return false;

	/* Multiply adjoint with reciprocal of determinant: */

	det = 1.0f / det;
	for (int i = 0; i < 16; i++) {
		inv[i] *= det;
	}

	return true;
}
void environmentMapsetting() {
	glGenTextures(1, &g_nCubeTex);
	int width, height, channels;
	uchar* img0 = readImageData("img/1024px.bmp", &width, &height, &channels);
	uchar* img1 = readImageData("img/1024nx.bmp", &width, &height, &channels);
	uchar* img2 = readImageData("img/1024py.bmp", &width, &height, &channels);
	uchar* img3 = readImageData("img/1024ny.bmp", &width, &height, &channels);
	uchar* img4 = readImageData("img/1024pz.bmp", &width, &height, &channels);
	uchar* img5 = readImageData("img/1024nz.bmp", &width, &height, &channels);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);
}
void draw_sphere() {
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);

	glutSolidSphere(3.0f, 50, 50);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
}
void draw_skyBox() {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	float skySize = 50.0f;

	glBegin(GL_QUADS);

	glTexCoord3d(1, -1, -1); glVertex3f(skySize, -skySize, -skySize);
	glTexCoord3d(1, -1, 1); glVertex3f(skySize, -skySize, skySize);
	glTexCoord3d(1, 1, 1);  glVertex3f(skySize, skySize, skySize);
	glTexCoord3d(1, 1, -1); glVertex3f(skySize, skySize, -skySize);
	//nx
	glTexCoord3d(-1, -1, -1); glVertex3f(-skySize, -skySize, -skySize);
	glTexCoord3d(-1, -1, 1); glVertex3f(-skySize, -skySize, skySize);
	glTexCoord3d(-1, 1, 1); glVertex3f(-skySize, skySize, skySize);
	glTexCoord3d(-1, 1, -1); glVertex3f(-skySize, skySize, -skySize);
	//py
	glTexCoord3d(1, 1, 1); glVertex3f(skySize, skySize, skySize);
	glTexCoord3d(-1, 1, 1); glVertex3f(-skySize, skySize, skySize);
	glTexCoord3d(-1, 1, -1); glVertex3f(-skySize, skySize, -skySize);
	glTexCoord3d(1, 1, -1); glVertex3f(skySize, skySize, -skySize);
	//ny
	glTexCoord3d(1, -1, 1); glVertex3f(skySize, -skySize, skySize);
	glTexCoord3d(-1, -1, 1); glVertex3f(-skySize, -skySize, skySize);
	glTexCoord3d(-1, -1, -1); glVertex3f(-skySize, -skySize, -skySize);
	glTexCoord3d(1, -1, -1); glVertex3f(skySize, -skySize, -skySize);
	//pz
	glTexCoord3d(1, -1, 1); glVertex3f(skySize, -skySize, skySize);
	glTexCoord3d(-1, -1, 1); glVertex3f(-skySize, -skySize, skySize);
	glTexCoord3d(-1, 1, 1); glVertex3f(-skySize, skySize, skySize);
	glTexCoord3d(1, 1, 1); glVertex3f(skySize, skySize, skySize);
	//nz
	glTexCoord3d(1, -1, -1); glVertex3f(skySize, -skySize, -skySize);
	glTexCoord3d(-1, -1, -1); glVertex3f(-skySize, -skySize, -skySize);
	glTexCoord3d(-1, 1, -1); glVertex3f(-skySize, skySize, -skySize);
	glTexCoord3d(1, 1, -1); glVertex3f(skySize, skySize, -skySize);
	glEnd();

} 
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	eyex = radius * sin(theta * PI / 180) * sin(phi * PI / 180);
	eyex = radius * cos(theta * PI / 180);
	eyez = radius * sin(theta * PI / 180) * cos(phi * PI / 180);
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);

	draw_skyBox();

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	GLfloat cam[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, cam);
	cam[14] = 0.f;
	GLfloat cam_inv[16]; //역행렬 저장할 곳을 선언
	gluInvertMatrix(cam, cam_inv);

	glMultMatrixf(cam_inv);

	glMatrixMode(GL_MODELVIEW);
	draw_sphere();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}
void init() {
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glutReshapeFunc(resize);
	gluQuadricTexture(qobj, GL_TRUE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	environmentMapsetting();
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
}
void special_keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		theta += 5;
		if (theta > 360)theta = 5;
	}
	else if (key == GLUT_KEY_RIGHT) {
		theta -= 5;
		if (theta <= 0)theta = 360;
	}
	else if (key == GLUT_KEY_UP) {
		phi += 5;
		if (phi >= 360)phi = 0;
	}
	else if (key == GLUT_KEY_DOWN) {
		
		phi -= 5;
		if (phi < 0)phi = 355;
	}
	glutPostRedisplay();
}
void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (float)width / (float)height, 1, 500);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}