#pragma once
#include "bmpfuncs.h"
//readImageDataf, storeImage,  readImageData   ->이렇게 3개의 함수 존재
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
radius * sin(theta * PI / 180) * cos(phi * PI / 180) };//카메라의 좌표
double up = 1;	//upvector
int light_option = 4;//조명 옵션
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
	int menu,spinM;							//서브 메뉴

	/*Window 초기화*/
	glutInit(&argc, argv);					//윈도우 초기화 함수
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//디스플레이 모드 설정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);			
	glutInitWindowPosition(300, 300);		//300, 300으로 위치 설정
	glutCreateWindow("12171841 임재형 ");	//윈도우 이름을 설정 -> 학번이랑 이름으로
	init();									//-> 사용자 초기화 함수

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
	
	/*Poup menu 생성 및 추가*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Init", 2);
	glutAddSubMenu("Light", menu);
	glutAddSubMenu("Spin", spinM);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수
	glutReshapeFunc(resize);				//resize 함수
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);		//방향키 입력
	glutMouseWheelFunc(mouseWheel);			//mouseWheel
	/*Looping 시작*/
	glutMainLoop();
	return 0;
}

void printinstruction() {
	printf("--------------------------keyboard--------------------------------\n");
	printf("Zoom in: 마우스 휠 ↑\n");
	printf("Zoom out: 마우스 휠 ↓\n");
	printf("방향키: 카메라의 각도 변경\n");
	printf("a: 좌표축 그리기\n");
	printf("s: 회전\n");
	printf("1~4: 광원 변경\n");
	printf("------------------------------------------------------------------\n");
}
void draw_axis() {
	glLineWidth(3); // 좌표축의 두께
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X축은 red
	glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);

	glColor3f(0, 1, 0); // Y축은 green
	glVertex3f(0, 0, 0); glVertex3f(0, 5, 0);

	glColor3f(0, 0, 1); // Z축은 blue
	glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
	glEnd();
	glLineWidth(1); // 두께 다시 환원
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
	glNormal3f(0, 0, -1.0);	//-z축
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
	glRotatef(-90, 1, 0, 0);	// 깡통 세우기
	glTranslatef(0, 0, -1);		// z축으로 -1 이동
	glColor3f(1.0, 1.0, 1.0);
	//이후의 물체들은 모두 회전된 상태로 그려집니다.
	//즉       |   z
	//     y<-- 
	//         /x    의 형태로 좌표축이 그려진다고 생각힙니다. 
	//뚜껑
	glPushMatrix();
	glTranslatef(0, 0, 2);		//뚜껑을 z=2에 그립니다. (world에선 1)
	glBindTexture(GL_TEXTURE_2D, textName2[0]);
	gluPartialDisk(qobj, 0, 1, 30, 3, 0, 360);
	glPopMatrix();

	//몸통						//world에서 -1에 그려지지만 
								//높이가 2 이므로 -1<z<1에 그려지게 됩니다.
	glBindTexture(GL_TEXTURE_2D, textName2[1]);
	gluCylinder(qobj, 1, 1, 2, 20, 20);//높이는 2

	//바닥
	glPushMatrix();
	glRotatef(180, 1, 0, 0);	//x축을 기준으로 다시 180도 회전시키면
				//기존 z축이 뒤집히므로 그대로 그리면world에서 z=-1에 그려집니다.
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
	glPushAttrib(GL_LIGHTING_BIT); //light에 관한 상태를 저장합니다.
	glDisable(GL_LIGHTING);//text에 생기는 그림자 효과를 지워줍니다.
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

	//큐브
	glPushMatrix();
	glTranslatef(2, 0, 2); //큐브 중심의 위치는 (2,0,2)
	glRotatef(angle[1], 0, 1, 0);
	draw_cube();
	glPopMatrix();

	//깡통
	glPushMatrix();
	glTranslatef(-3, 0, -2); //깡통 중심의 위치는 (-3,0,-2)
	glRotatef(angle[2], 0, 1, 0);
	draw_cylinder();
	glPopMatrix();

	//지구
	glPushMatrix();
	glTranslatef(-1, 0, -5);
	glRotatef(angle[3], 0, 1, 0);
	draw_sphere();			//지구의 위치는 (-1,0,-5)
	glPopMatrix();
	//출력
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

	/* 조작법 출력 */
	printinstruction();

	/* TEXTURE MAPPING SET */
	gluQuadricTexture(qobj, GL_TRUE);

	cubeTextureMapping();
	cylinderTextureMapping();
	sphereTextureMapping();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}
void setdefault() {//초기 설정
	theta = 45, phi = 45;
	radius = 18;
	cam[0] = radius * sin(theta * PI / 180) * sin(phi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	cam[2] = radius * sin(theta * PI / 180) * cos(phi * PI / 180);//카메라의 좌표
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
		printf("큐브 조명 ON\n");
		light_option = 1;
	}
	else if (option == 2) {
		printf("지구 조명 ON\n");
		light_option = 2;
	}
	else if (option == 3) {
		printf("깡통 조명 ON\n");
		light_option = 3;
	}
	else if (option == 4) {
		printf("카메라 조명 ON\n");
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

	// 조명 스위치와 0번 조명 스위치 켜기
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
		printf("종료합니다.\n");
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
		printf("큐브 조명 ON\n");
		light_option = 1;
	}
	else if (key == '2') {
		printf("지구 조명 ON\n");
		light_option = 2;
	}
	else if (key == '3') {
		printf("깡통 조명 ON\n");
		light_option = 3;
	}
	else if (key == '4') {
		printf("카메라 조명 ON\n");
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
	if (dir > 0) { //가까워 지는 것
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
	if (opt == 1) { //전체 회전
		if (spin)spin = false;
		else spin = true;
	}
	else if (opt == 2) { //큐브 회전
		if (spin_cube)spin_cube = false;
		else spin_cube = true;
	}
	else if (opt == 3) { //깡통 회전
		if (spin_cylinder)spin_cylinder = false;
		else spin_cylinder = true;
	}
	else if (opt == 4) { //지구 회전
		if (spin_sphere)spin_sphere = false;
		else spin_sphere = true;
	}
}