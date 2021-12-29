#include <gl/glut.h>
#include <stdio.h.>
#include <Windows.h>
void draw_point();
void draw_line();
void draw_triangle();
void draw_quad();

void init(void) {
	/*ȭ���� �⺻������ dark blue ����*/
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);//R,G,B, ����
	//����: ���� ����

	/* ȭ�� ��ǥ ���� ���� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}
/*Display �ݹ� �Լ� �����*/
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);	//�� ����
	draw_point();					//���� �׸���.
	//draw_line();					//���� �׸���.
	//draw_triangle();				//�ﰢ���� �׸���.
	//draw_quad();					//�簢���� �׸���.
}

/*���� ��� �Լ�*/
void draw_point(void) {
	/*���� ������ ���� ������*/
	glColor3f(1.0f, 0.0f, 0.0f);	//���������� ����
	
	glPointSize(4.0f);				/*���� ũ�� -> �ʱⰪ�� 1.0*/
	glBegin(GL_POINTS);				//���� �׸� ���̶�� ���� ǥ��
		glVertex2i(80, 80);
		glVertex2i(200, 80);
		glVertex2i(200, 300);
	glEnd();						//��ǥ ��� ����
	glFlush();						//��ɾ� �о� �־� �ִ� ��.-> ����
}
/*���� �׸��� �Լ�*/
void draw_line(void){
	//glLineWidth(4.0f);
	//glEnable(GL_LINE_STIPPLE);	//���� �׸��� ������ ON
	//glLineStipple(3, 0xAAAA);	//3�� factor, 0xAAAA���� ����
	/* ���� ������ ��������� */
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2i(30, 40);
		glVertex2i(280, 350);
		glVertex2i(400, 250);
		glVertex2i(300, 200);
	glEnd();
	glFlush();						//��ɾ� �о� �־� �ִ� ��.-> ����
}
/*
-�� �β� �ٲٱ�
	glLineWidth (float Width)�� �̿��Ͽ� �β� ����
-�� �׸��� ��� ����
	glBegin�� ���ڸ� ����
		GL_LINES
		GL_LINE_STRIP
		GL_LINE_LOOP
*/
/*�� �׸���*/
void draw_triangle(void){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//������ �׸�
	/* ���� ������ ��������� */
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);			//�ﰢ�� �׸��� �Լ�
		glVertex2i(80, 80);
		glVertex2i(200, 80);
		glVertex2i(200, 300);
	glEnd();
	glFlush();						//��ɾ� �о� �־� �ִ� ��.-> ����
}
void draw_quad() {
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	/* ���� ������ ��������� */
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);				//�簢�� �׸��� �Լ�
		glVertex2i(150, 160);
		glVertex2i(150, 360);
		glVertex2i(300, 320);
		glVertex2i(360, 180);
	glEnd();
	glFlush();
}
//Menu ó�� �Լ� - �޴� ���ý� �����
void point_menu_function(int option) {
	glClear(GL_COLOR_BUFFER_BIT);
	if (option == 1) {
		printf("�� 3���� ����ϴ�.\n");
		draw_point();
	}
	else if (option == 2) {
		printf("�� 5���� ����ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		/*���� ũ�� -> �ʱⰪ�� 1.0*/
		glPointSize(10.0f);
		glBegin(GL_POINTS);
			glVertex2i(80, 80);
			glVertex2i(200, 80);
			glVertex2i(200, 300);
			glVertex2i(400, 380);
			glVertex2i(200, 400);
		glEnd();
		glFlush();
	}
}
void polygon_menu_function(int option) {	//sub menu call back
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (option == 1) { //�ﰢ��
		printf("�ﰢ���� �׸��ϴ�.\n");
		draw_triangle();
	}
	else if (option == 2) {
		printf("�̾��� �ﰢ��(Triangle Strip)���� �׸��ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
			glVertex2i(100, 300);
			glVertex2i(100, 100);
			glVertex2i(200, 300);
			glVertex2i(300, 100);
			glVertex2i(400, 300);
			glVertex2i(450, 50);
		glEnd();
		glFlush();
	}
	else if (option == 3) {
		printf("�ﰢ������ ��ä����(Triangle Fan)�� �׸��ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2i(100, 100);
			glVertex2i(150, 200);
			glVertex2i(200, 180);
			glVertex2i(250, 150);
			glVertex2i(220, 80);
		glEnd();
		glFlush();
	}
	else if (option == 4) {
		printf("�簢�� 1���� �׸��ϴ�.\n");
		draw_quad();
	}
	else if (option == 5) {
		printf("�簢������ �׸��ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex2i(100, 100);
			glVertex2i(100, 300);
			glVertex2i(200, 300);
			glVertex2i(300, 100);
			glVertex2i(400, 450);
			glVertex2i(400, 200);
			glVertex2i(300, 200);
			glVertex2i(200, 400);
		glEnd();
		glFlush();
	}
	else if (option == 6) {
		printf("�̾��� �簢��(Quads Strip)���� �׸��ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUAD_STRIP);
			glVertex2i(100, 100);
			glVertex2i(100, 300);
			glVertex2i(250, 100);
			glVertex2i(200, 300);
			glVertex2i(400, 100);
			glVertex2i(450, 350);
		glEnd();
		glFlush();
	}
	else if (option == 7) {
		printf("������ �ٰ����� �׸��ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
			glVertex2i(150, 280);
			glVertex2i(200, 380);
			glVertex2i(270, 300);
			glVertex2i(240, 100);
			glVertex2i(180, 90);
		glEnd();
		glFlush();
	}
}
void line_menu_function(int option){
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_LINE_STIPPLE);
	if (option == 1) {	//��
		printf("2���� ���� �׸��ϴ�.\n");
		draw_line();
	}
	else if (option == 2) { //�� ��
		printf("������ �ִ� ���� �׸��ϴ�.\n");
		glLineWidth(2.0f);			//���� �β� ����
		glEnable(GL_LINE_STIPPLE);	//���� �׸��� ������ ����
		glLineStipple(3, 0xAAAA);	//3�� factor, 0xAAAA���� ����
		draw_line();
	}
	else if (option == 3) { //���� ��
		printf("���� ���� �׸��ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2i(30, 40);
			glVertex2i(280, 350);
			glVertex2i(120, 250);
			glVertex2i(300, 200);
			glVertex2i(170, 100);
		glEnd();
		glFlush();
	}
	else if (option == 4) { //�̾��� ��
		printf("������ ������ ������ ����� ���� �׸��ϴ�.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
			glVertex2i(30, 40);
			glVertex2i(280, 350);
			glVertex2i(120, 250);
			glVertex2i(300, 200);
			glVertex2i(170, 100);
		glEnd();
		glFlush();
	}
}
void main_menu_function(int option) {	//main menu call back
	printf("Main menu %d has been elected\n", option);
	if (option == 999) {				//999�Է� �� 
		exit(0);						//����
	}
}

int main(int argc, char** argv) {
	int submenu1, submenu2, submenu3;	//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//���÷��� ��� ����
	glutInitWindowSize(500, 500);			//500 * 500���� ������
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����
	init();									//-> ����� �ʱ�ȭ �Լ�

	/*Poup menu ���� �� �߰�*/
	submenu1 = glutCreateMenu(polygon_menu_function);
	glutAddMenuEntry("Triangle", 1);
	glutAddMenuEntry("Triangle Strip", 2);
	glutAddMenuEntry("Triangle Fan", 3); 
	glutAddMenuEntry("Quad", 4);
	glutAddMenuEntry("Quads", 5);
	glutAddMenuEntry("Quads Strip", 6);
	glutAddMenuEntry("Polygon", 7);
	
	submenu2 = glutCreateMenu(line_menu_function);
	glutAddMenuEntry("Line", 1);
	glutAddMenuEntry("Stipple Dot Line", 2);
	glutAddMenuEntry("Loop Line", 3);
	glutAddMenuEntry("Strip Line ", 4);
	
	submenu3 = glutCreateMenu(point_menu_function);
	glutAddMenuEntry("3 points", 1);
	glutAddMenuEntry("5 points", 2);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddSubMenu("Polygon", submenu1);
	glutAddSubMenu("Lines", submenu2);
	glutAddSubMenu("Point", submenu3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�

	/*Looping ����*/
	glutMainLoop();

	return 0;
}