#pragma once
#include "bmpfuncs.h"
//readImageDataf, storeImage,  readImageData   ->�̷��� 3���� �Լ� ����
#include <GL/freeglut.h>
#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<cstring>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265
double theta = 45, phi=45;
double radius = 18;
double cam[3] = { radius * sin(theta * PI / 180) * sin(phi * PI / 180),radius * cos(theta * PI / 180),
radius * sin(theta * PI / 180) * cos(phi * PI / 180) };//ī�޶��� ��ǥ
double up = 1;	//upvector
int light_option = 4;//���� �ɼ�
bool axis_on = false;
bool spin = false;
bool spin_cube=false, spin_cylinder=false, spin_sphere=false;
double angle[4];
GLuint textName[6]; // cube
GLuint textName2[3]; //cylinder
GLuint *textName3=new GLuint();	//sphere
GLUquadricObj* qobj=gluNewQuadric();

const char* light_mode[4] = { "Cube Light", "Earth Light", "Cylinder Light", "Camera Light" };

void printinstruction();//o
void draw_axis();//o
void cubeTextureMapping();//o
void draw_cube();//o
void cylinderTextureMapping();//o
void draw_cylinder();//o
void sphereTextureMapping();//o
void draw_sphere();//o
void draw_string(void*, const char* ,int ,int );//o
void draw(void);//********************************************
void resize(int, int);//o
void light_default();//o
void init(void);//o
void setdefault();//o
void light_menu(int);//o
void light_select();//********************************************
void main_menu(int);//o
void idle();//o
void keyboard(unsigned char, int, int);//o
void special_keyboard(int, int, int);//o
void mouseWheel(int, int, int, int);//o
void spin_menu(int);//o
int main(int argc, char** argv) {
	int menu,spinM;							//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//���÷��� ��� ����
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);			
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����
	init();									//-> ����� �ʱ�ȭ �Լ�

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	menu = glutCreateMenu(light_menu);
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Earth", 2);
	glutAddMenuEntry("Cylinder", 3);
	glutAddMenuEntry("Camera", 4);

	spinM = glutCreateMenu(spin_menu);
	glutAddMenuEntry("Total", 1);
	glutAddMenuEntry("Cube", 2);
	glutAddMenuEntry("Cylinder", 3);
	glutAddMenuEntry("Earth", 4);
	
	/*Poup menu ���� �� �߰�*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Init", 2);
	glutAddSubMenu("Light", menu);
	glutAddSubMenu("Spin", spinM);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�
	glutReshapeFunc(resize);				//resize �Լ�
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);		//����Ű �Է�
	glutMouseWheelFunc(mouseWheel);			//mouseWheel
	/*Looping ����*/
	glutMainLoop();
	return 0;
}

void printinstruction() {
	printf("--------------------------keyboard--------------------------------\n");
	printf("Zoom in: ���콺 �� ��\n");
	printf("Zoom out: ���콺 �� ��\n");
	printf("����Ű: ī�޶��� ���� ����\n");
	printf("a: ��ǥ�� �׸���\n");
	printf("s: ȸ��\n");
	printf("1~4: ���� ����\n");
	printf("------------------------------------------------------------------\n");
}
void draw_axis() {
	glLineWidth(3); // ��ǥ���� �β�
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X���� red
	glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);

	glColor3f(0, 1, 0); // Y���� green
	glVertex3f(0, 0, 0); glVertex3f(0, 5, 0);

	glColor3f(0, 0, 1); // Z���� blue
	glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
	glEnd();
	glLineWidth(1); // �β� �ٽ� ȯ��
}
void cubeTextureMapping() {
	glGenTextures(6, textName);
	int imgX, imgY, channels;
	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, textName[i]);
		char buf[100];
		sprintf(buf, "img/TexImage%d.bmp", i);
		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgX, &imgY, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgX, imgY, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
void draw_cube() {
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textName[0]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0, 0);	// -x axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textName[1]);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0, 0);	//x axis
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textName[2]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1.0, 0);	// -y axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textName[3]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1.0, 0);	// y axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textName[4]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0);	//z axis
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textName[5]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1.0);	//-z��
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, -1.0);
	glEnd();
	if (axis_on)draw_axis();
}
void cylinderTextureMapping() {
	glGenTextures(3, textName2);
	uchar* img;
	int imgX, imgY, channels;
	const char* name[3] = { "img/CIDER_T.bmp","img/CIDER_S.bmp","img/CIDER_B.bmp" };
	for (int i = 0; i < 3; i++) {
		glBindTexture(GL_TEXTURE_2D, textName2[i]);
		img = readImageData(name[i], &imgX, &imgY, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgX, imgY, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
void draw_cylinder() {
	glRotatef(-90, 1, 0, 0);	// ���� �����
	glTranslatef(0, 0, -1);		// z������ -1 �̵�
	glColor3f(1.0, 1.0, 1.0);
	//������ ��ü���� ��� ȸ���� ���·� �׷����ϴ�.
	//��       |   z
	//     y<-- 
	//         /x    �� ���·� ��ǥ���� �׷����ٰ� �������ϴ�. 
	//�Ѳ�
	glPushMatrix();
	glTranslatef(0, 0, 2);		//�Ѳ��� z=2�� �׸��ϴ�. (world���� 1)
	glBindTexture(GL_TEXTURE_2D, textName2[0]);
	gluPartialDisk(qobj, 0, 1, 30, 3, 0, 360);
	glPopMatrix();

	//����						//world���� -1�� �׷������� 
								//���̰� 2 �̹Ƿ� -1<z<1�� �׷����� �˴ϴ�.
	glBindTexture(GL_TEXTURE_2D, textName2[1]);
	gluCylinder(qobj, 1, 1, 2, 20, 20);//���̴� 2

	//�ٴ�
	glPushMatrix();
	glRotatef(180, 1, 0, 0);	//x���� �������� �ٽ� 180�� ȸ����Ű��
				//���� z���� �������Ƿ� �״�� �׸���world���� z=-1�� �׷����ϴ�.
	glBindTexture(GL_TEXTURE_2D, textName2[2]);
	gluPartialDisk(qobj, 0, 1, 30, 3, 0, 360);
	glPopMatrix();
	if (axis_on)draw_axis();
}
void sphereTextureMapping() {
	glGenTextures(1, textName3);
	uchar* img;
	int imgX, imgY, channels;

	glBindTexture(GL_TEXTURE_2D, *textName3);
	img = readImageData("img/EARTH.bmp", &imgX, &imgY, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgX, imgY, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
void draw_sphere() {
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, *textName3);
	gluSphere(qobj, 1, 100, 100);

	if (axis_on)draw_axis();
}
void draw_string(void* font, const char* str, int x, int y) {
	glPushAttrib(GL_LIGHTING_BIT); //light�� ���� ���¸� �����մϴ�.
	glDisable(GL_LIGHTING);//text�� ����� �׸��� ȿ���� �����ݴϴ�.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10); 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1,1,0);
	glRasterPos3f(x, y, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	cam[0] = radius * sin(theta * PI / 180) * sin(phi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	cam[2] = radius * sin(theta * PI / 180) * cos(phi * PI / 180);
	gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, 0, up, 0);

	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, light_mode[light_option - 1], -9, 8);
	light_select();

	glRotatef(angle[0], 0, 1, 0);

	//ť��
	glPushMatrix();
	glTranslatef(2, 0, 2); //ť�� �߽��� ��ġ�� (2,0,2)
	glRotatef(angle[1], 0, 1, 0);
	draw_cube();
	glPopMatrix();

	//����
	glPushMatrix();
	glTranslatef(-3, 0, -2); //���� �߽��� ��ġ�� (-3,0,-2)
	glRotatef(angle[2], 0, 1, 0);
	draw_cylinder();
	glPopMatrix();

	//����
	glPushMatrix();
	glTranslatef(-1, 0, -5);
	glRotatef(angle[3], 0, 1, 0);
	draw_sphere();			//������ ��ġ�� (-1,0,-5)
	glPopMatrix();
	//���
	glutSwapBuffers();
}
void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (float)width / (float)height, 1, 500);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutReshapeFunc(resize);
	/* light setting */
	light_default();

	/* ���۹� ��� */
	printinstruction();

	/* TEXTURE MAPPING SET */
	gluQuadricTexture(qobj, GL_TRUE);

	cubeTextureMapping();
	cylinderTextureMapping();
	sphereTextureMapping();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}
void setdefault() {//�ʱ� ����
	theta = 45, phi = 45;
	radius = 18;
	cam[0] = radius * sin(theta * PI / 180) * sin(phi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	cam[2] = radius * sin(theta * PI / 180) * cos(phi * PI / 180);//ī�޶��� ��ǥ
	up = 1;
	light_option = 4;
	axis_on = false;
	spin = false;
	spin_cube = true, spin_cylinder = true, spin_sphere = true;
	for (int i = 0; i < 4; i++)angle[i] = 0;
	glutPostRedisplay();
}
void light_menu(int option) {
	if (option == 1) {
		printf("ť�� ���� ON\n");
		light_option = 1;
	}
	else if (option == 2) {
		printf("���� ���� ON\n");
		light_option = 2;
	}
	else if (option == 3) {
		printf("���� ���� ON\n");
		light_option = 3;
	}
	else if (option == 4) {
		printf("ī�޶� ���� ON\n");
		light_option = 4;
	}
	glutPostRedisplay();
}
void light_default() {
	glClearColor(0, 0, 0, 1.0f);

	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.3f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	GLfloat ambient_Sun[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Sun);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// ���� ����ġ�� 0�� ���� ����ġ �ѱ�
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void light_select() {
	if (light_option == 1) {//cube
		GLfloat light[] = { 2.0, 0.0, 2.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light);
	}
	else if (light_option == 2) {//sphere
		GLfloat light[] = { -1.0, 0.0, -5.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light);
	} 
	else if (light_option == 3) {//cylinder
		GLfloat light[] = { -3.0, 0.0, -2.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light);
	}
	else if (light_option == 4) {//camera
		GLfloat light[] = { cam[0],cam[1],cam[2],1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light);
	}
	glutPostRedisplay();
}
void main_menu(int option) {
	if (option == 1) {//quit
		printf("�����մϴ�.\n");
		exit(0);
	}
	else if (option == 2) {//init
		setdefault();
	}
}
void idle() {
	if (spin) {
		angle[0] += 0.1;
		if (angle[0] > 360)angle[0] = 0;
	}
	if (spin_cube) {
		angle[1] += 0.1;
		if (angle[1] > 360)angle[1] = 0;
	}
	if (spin_cylinder) {
		angle[2] += 0.1;
		if (angle[2] > 360)angle[2] = 0;
	}
	if (spin_sphere) {
		angle[3] += 0.1;
		if (angle[3] > 360)angle[3] = 0;
	}
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 'a') {
		if (!axis_on)axis_on = true;
		else axis_on = false;
	}
	else if (key=='s') {
		if (spin)spin = false;
		else spin = true;
	}
	else if (key == '1') {
		printf("ť�� ���� ON\n");
		light_option = 1;
	}
	else if (key == '2') {
		printf("���� ���� ON\n");
		light_option = 2;
	}
	else if (key == '3') {
		printf("���� ���� ON\n");
		light_option = 3;
	}
	else if (key == '4') {
		printf("ī�޶� ���� ON\n");
		light_option = 4;
	}
	glutPostRedisplay();
}
void special_keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		phi -= 5;
		if (phi < 0)phi = 355;
	}
	else if (key == GLUT_KEY_RIGHT) {
		phi += 5;
		if (phi >= 360)phi = 0;
	}
	else if (key == GLUT_KEY_UP) {
		theta -= 5;
		if (theta <= 0)theta = 360;

	}
	else if (key == GLUT_KEY_DOWN) {
		theta += 5;
		if (theta > 360)theta = 5;
	}
	if (theta > 0 && theta <= 180)up = 1;
	if (theta > 180 && theta <= 360)up = -1;
	glutPostRedisplay();
}
void mouseWheel(int buotton, int dir, int x, int y) {
	if (dir > 0) { //����� ���� ��
		radius *= 0.9;
	}
	else {
		radius = radius * 10 / 9;
	}
	cam[2] = radius * sin(theta * PI / 180) * cos(phi * PI / 180);
	cam[0] = radius * sin(theta * PI / 180) * sin(phi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	glutPostRedisplay();
}
void spin_menu(int opt) {
	if (opt == 1) { //��ü ȸ��
		if (spin)spin = false;
		else spin = true;
	}
	else if (opt == 2) { //ť�� ȸ��
		if (spin_cube)spin_cube = false;
		else spin_cube = true;
	}
	else if (opt == 3) { //���� ȸ��
		if (spin_cylinder)spin_cylinder = false;
		else spin_cylinder = true;
	}
	else if (opt == 4) { //���� ȸ��
		if (spin_sphere)spin_sphere = false;
		else spin_sphere = true;
	}
}