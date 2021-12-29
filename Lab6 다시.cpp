#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdio.h.>
#include <math.h>
#include <Windows.h>
#define PI 3.141592653589

double radius = 13 * sqrt(3);
double theta = 45, pi = 45;
double cam[3] = { radius * sin(theta * PI / 180) * sin(pi * PI / 180),radius * cos(theta * PI / 180),
radius * sin(theta * PI / 180) * cos(pi * PI / 180) };//ī�޶��� ��ǥ
double center[3] = { 0,0,0 };//ī�޶� ���� ��ü�� ��ǥ
double up[3] = { 0,1,0 };	 //ī�޶��� ����

void init(void) {
	printf("init func called\n");

	glClearColor(0, 0, 0, 1.0f);

	//set blend for checking x,y,z axis
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//set antialiasing
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_LINE_SMOOTH);
}
/*Display �ݹ� �Լ� �����*/
void draw_axis() {
	glLineWidth(3); // ��ǥ���� �β�
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X���� red
	glVertex3f(0, 0, 0); glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0); // Y���� green
	glVertex3f(0, 0, 0); glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1); // Z���� blue
	glVertex3f(0, 0, 0); glVertex3f(0, 0, 4);
	glEnd();
	glLineWidth(1); // �β� �ٽ� ȯ��
}
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (theta > 0 && theta <= 180)up[1] = 1;
	if (theta > 180 && theta <= 360)up[1] = -1;

	cam[0] = radius * sin(theta * PI / 180) * sin(pi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	cam[2] = radius * sin(theta * PI / 180) * cos(pi * PI / 180);
	gluLookAt(cam[0], cam[1], cam[2], center[0], center[1], center[2], up[0], up[1], up[2]);
	//gluLookAt(cam[0], cam[1], cam[2], center[0], center[1], center[2], up[0], -up[1], up[2]);
	//gluLookAt(cam[0], 0, 0, 0, 0, 0, up[0], up[1], up[2]);
	//gluLookAt(2*cam[0], 0, 0, 0, 0, 0, up[0], up[1], up[2]);
	//gluLookAt(0, 0, cam[2], 0, 0, 0, up[0], up[1], up[2]);
	//gluLookAt(0, 0, 2*cam[2], 0, 0, 0, up[0], up[1], up[2]);
	//gluLookAt(0, cam[1],0, 0, 0, 0, 1, 0, 0);
	//gluLookAt(0, 2*cam[1],0, 0, 0, 0, 1, 0, 0);

	glColor3f(1, 1, 0);
	glutWireTeapot(4);
	//glutWireCube(4);
	//glutWireSphere(4,20,20);
	draw_axis();

	glFlush();
	glutSwapBuffers();
}


void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (float)width / (float)height, 1, 500);
	//glOrtho(-15, 15, -15, 15, -15, 15);//����ü ������ ���ú��Ǹ� ���� -> �߽��� 0,0,0
	//glFrustum(-10, 10, -15, 15, 1, 500);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
/*Ű���� �Է� �ݹ� �Լ�*/
void special_keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		pi -= 5;
		if (pi < 0)pi = 355;
	}
	else if (key == GLUT_KEY_RIGHT) {
		pi += 5;
		if (pi >= 360)pi = 0;
	}
	else if (key == GLUT_KEY_UP) {
		theta -= 5;
		if (theta <= 0)theta = 360;

	}
	else if (key == GLUT_KEY_DOWN) {
		theta += 5;
		if (theta > 360)theta = 5;
	}
	printf("theta: %d , pi: %d \n", int(theta), int(pi));

	glutPostRedisplay();
}
void mouseWheel(int buotton, int dir, int x, int y) {

	if (dir > 0) { //����� ���� ��
		printf("Zoom in\n");
		radius *= 0.9;
	}
	else {
		printf("Zoon out\n");
		radius = radius * 10 / 9;
	}
	cam[2] = radius * sin(theta * PI / 180) * cos(pi * PI / 180);
	cam[0] = radius * sin(theta * PI / 180) * sin(pi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	glutPostRedisplay();
}
void main_menu(int option) {
	if (option == 1) {
		theta = 45, pi = 45;
		radius = 13 * sqrt(3);
		cam[0] = radius * sin(theta * PI / 180) * sin(pi * PI / 180),
			cam[1] = radius * cos(theta * PI / 180), cam[2] = radius * sin(theta * PI / 180) * cos(pi * PI / 180);
		center[0] = 0, center[1] = 0, center[2] = 0;
		up[0] = 0, up[1] = 1, up[2] = 0;

		glutPostRedisplay();
	}
	else if (option == 2) {
		printf("�����մϴ�!\n");
		exit(0);
	}
}
int main(int argc, char** argv) {
	int menu;							//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//���÷��� ��� ����
	glutInitWindowSize(500, 500);			//500 * 500���� ������
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����
	init();									//-> ����� �ʱ�ȭ �Լ�

	/*Poup menu ���� �� �߰�*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Init", 1);
	glutAddMenuEntry("Quit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�
	glutSpecialFunc(special_keyboard);		//����Ű �Է�
	glutReshapeFunc(resize);				//resize �Լ�
	glutMouseWheelFunc(mouseWheel);			//mouseWheel
	/*Looping ����*/
	glutMainLoop();

	return 0;
}