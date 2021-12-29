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

double m_RotateAngle;		 //ȸ��
bool spin=true;				 //ȸ�� ����


void setup() {
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat specularMaterial[] = { 1.0f, 1.0f, 1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, 20);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void init(void) {
	printf("init func called\n");
	glClearColor(1,1,1,1.0f);
	glClearDepth(1.0f);

	setup();
	// Depth-Test Enable
	glFrontFace(GL_CW); // Teapot�� CW�� ���ǵ�
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);			//�޸��� ������ �ʰ� �ϴ� ��

	//glPolygonMode(GL_BACK, GL_LINE);//teapot�� ���θ� wire�� ǥ���Ѵ�.
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
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cam[0], cam[1], cam[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	glPushMatrix();
		glRotatef(m_RotateAngle, 0, 1, 0);
		GLdouble eq[4] = { 1.0, 0.0, 0.0, 0.0 };
		glClipPlane(GL_CLIP_PLANE0, eq);
		glEnable(GL_CLIP_PLANE0);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glutSolidTeapot(4);
	draw_axis();

	glFlush();
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
	if (theta > 0 && theta <= 180)up[1] = 1;
	if (theta > 180 && theta <= 360)up[1] = -1;
	cam[0] = radius * sin(theta * PI / 180) * sin(pi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	cam[2] = radius * sin(theta * PI / 180) * cos(pi * PI / 180);
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
		m_RotateAngle = 0;
		glutPostRedisplay();
	}
	else if (option == 2) {
		printf("�����մϴ�!\n");
		exit(0);
	}
	else if(option == 3) {
		if (spin == true)spin = false;
		else spin = true;
	}
}
void face_menu(int option) {
	if (option == 1) {
		glPolygonMode(GL_BACK,GL_POINT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);	
	}
	else if (option == 2) {
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_BACK, GL_LINE);//teapot�� ���θ� wire�� ǥ���Ѵ�.
	}
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		printf("type s\n");
		if (spin)spin = false;
		else spin = true;
	}
	glutPostRedisplay();
}
void idle() {
	if (spin == true) {
		m_RotateAngle += 0.1; 
		if (m_RotateAngle >= 360)m_RotateAngle = 0;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	int menu;							//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);	//���÷��� ��� ����
	glutInitWindowSize(500, 500);			//500 * 500���� ������
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����
	init();									//-> ����� �ʱ�ȭ �Լ�


	menu = glutCreateMenu(face_menu);
	glutAddMenuEntry("culling", 1);
	glutAddMenuEntry("back: wire", 2);
	/*Poup menu ���� �� �߰�*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Init", 1);
	glutAddMenuEntry("Quit", 2);
	glutAddMenuEntry("Spin", 3);
	glutAddSubMenu("Back Menu", menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�
	glutSpecialFunc(special_keyboard);		//����Ű �Է�
	glutReshapeFunc(resize);				//resize �Լ�
	glutMouseWheelFunc(mouseWheel);			//mouseWheel
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	/*Looping ����*/
	glutMainLoop();

	return 0;
}