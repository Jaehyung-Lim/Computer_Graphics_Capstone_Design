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
double theta = 45, phi = 45;
double radius = 18;
double cam[3] = { radius * sin(theta * PI / 180) * sin(phi * PI / 180),radius * cos(theta * PI / 180),
radius * sin(theta * PI / 180) * cos(phi * PI / 180) };//카메라의 좌표
double up = 1;	//upvector
int select = 1;
bool axis_on = false;

GLUquadricObj* qobj = gluNewQuadric();

void printinstruction();//o
void draw_axis();//o
void draw_cube();//o
void draw_cylinder();//o
void draw_sphere();//o
void draw_string(void*, const char*, int, int);//o
void draw(void);//
void resize(int, int);//o
void light_default();//o
void init(void);//o
void main_menu(int);
void keyboard(unsigned char, int, int);//o
void special_keyboard(int, int, int);//o
void mouseWheel(int, int, int, int);//o
void Menu();
void CallBack();
void draw_teapot();
void draw_can();
void draw_partialdisk();
void draw_text();
void draw_cone();
void draw_disk();

int menu, spinM;							//서브 메뉴
int main(int argc, char** argv) {
	/*Window 초기화*/
	glutInit(&argc, argv);					//윈도우 초기화 함수
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//디스플레이 모드 설정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(300, 300);		//300, 300으로 위치 설정
	glutCreateWindow("12171841 임재형 ");	//윈도우 이름을 설정 -> 학번이랑 이름으로
	init();									//-> 사용자 초기화 함수


	/*여기 인자를 변경해주기*/
	gluQuadricDrawStyle(qobj, GLU_FILL); //GLU_LINE, GLU_SILHOUETTE, GLU_POINT,GLU_FILL
	gluQuadricNormals(qobj, GLU_FLAT);//GLU_NONE, GLU_FLAT, GLU_SMOOTH

	Menu();

	CallBack();

	/*Looping 시작*/
	glutMainLoop();
	return 0;
}

void printinstruction() {
	printf("--------------------------keyboard--------------------------------\n");
	printf("Zoom in: 마우스 휠 ↑\n");
	printf("Zoom out: 마우스 휠 ↓\n");
	printf("방향키: 카메라의 각도 변경\n");
	printf("1:Multiple viewport\n");
	printf("2~5: 물체 변경\n ");
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
void draw_cylinder() {
	glRotatef(-90, 1, 0, 0);	
	glTranslatef(0, 0, -1);		
	glColor3f(1.0, 1.0, 1.0);
	//뚜껑
	glPushMatrix();
	glTranslatef(0, 0, 2);		
	gluPartialDisk(qobj, 0, 1, 30, 3, 0, 360);
	glPopMatrix();

	//몸통						
	gluCylinder(qobj, 1, 1, 2, 20, 20);

	//바닥
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	gluPartialDisk(qobj, 0, 1, 30, 3, 0, 360);
	glPopMatrix();
	if (axis_on)draw_axis();
}

/*Lab12, 13실습*/
void draw_sphere() {
	glColor3f(1.0, 1.0, 0);
	gluSphere(qobj, 1, 100, 100);
	if (axis_on)draw_axis();
	glFlush();
}
void draw_text() {
	glViewport(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	glPushMatrix();
	gluOrtho2D(-10, 10, -10, 10);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "12171841 Lim Jae Hyung!!!!", -5, 5);

	glColor3f(0.5f, 1.0f, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "MultiViewport Example", -5, 3);

	glFlush();
	glPopMatrix();
}
void draw_partialdisk() {
	glViewport(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	glColor3f(1.0f, 1.0f, 0);
	gluPartialDisk(qobj, 3, 6, 50, 3, 90, 270);

	if (axis_on)draw_axis();

	glFlush();
}
void draw_can() {
	glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	glRotatef(-90, 1, 0, 0);	
	glTranslatef(0, 0, -2);		
	glColor3f(1.0, 1.0, 1.0);

	//뚜껑
	glPushMatrix();
	glTranslatef(0, 0, 2);
	gluPartialDisk(qobj, 0, 2, 30, 3, 0, 360);
	glPopMatrix();

	//몸통						
	gluCylinder(qobj, 2, 2, 4, 20, 20);

	//바닥
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	gluPartialDisk(qobj, 0, 2, 30, 3, 0, 360);
	glPopMatrix();
	if (axis_on)draw_axis();
}
void draw_teapot() {
	glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	glColor3f(1.0f, 1.0f, 0);
	glutWireTeapot(5);

	if (axis_on)draw_axis();

	glFlush();
}
void draw_cone() {
	glColor3f(1.0, 1.0, 0);
	gluCylinder(qobj, 4, 0, 4, 20, 20);
	if (axis_on)draw_axis();
	glFlush();
}
void draw_disk() {
	glColor3f(1.0, 1.0, 0);
	gluDisk(qobj, 1, 5, 20,20);
	if (axis_on)draw_axis();
	glFlush();
}
/*Lab12, 13실습*/
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
	glColor3f(1, 1, 0);
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
void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam[0] = radius * sin(theta * PI / 180) * sin(phi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	cam[2] = radius * sin(theta * PI / 180) * cos(phi * PI / 180);
	gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, 0, up, 0);
	if (select == 1) { // multi viewport
		draw_text(); // 2사분면에 그리기
		draw_partialdisk(); // 1사분면에 그리기
		draw_can(); // 3사분면에 그리기
		draw_teapot(); // 4사분면에 그리기
	}
	else if (select == 2) {
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		draw_sphere();
	}
	else if (select == 3) {
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		draw_cone();
	}
	else if (select == 4) {
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		draw_disk();
	}
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
	GLfloat light[] = { cam[0],cam[1],cam[2],1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light);
}

void main_menu(int option) {
	if (option == 1) {//quit
		printf("종료합니다.\n");
		gluDeleteQuadric(qobj);
		exit(0);
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == '1') {
		printf("multiple view port\n");
		select = 1;
	}
	else if (key == '2') {
		printf("Sphere\n");
		select = 2;
	}
	else if (key == '3') {
		printf("Cone\n");
		select = 3;
	}
	else if (key == '4') {
		printf("disk\n");
		select = 4;
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

void Menu() {


	/*Poup menu 생성 및 추가*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Init", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void CallBack() {
	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수
	glutReshapeFunc(resize);				//resize 함수
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);		//방향키 입력
	glutMouseWheelFunc(mouseWheel);			//mouseWheel
}
