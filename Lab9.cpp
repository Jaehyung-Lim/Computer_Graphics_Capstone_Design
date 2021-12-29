#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdio.h.>
#include <math.h>
#include <Windows.h>

double angle[5];
bool spin_state = false;

bool light_sun = true; //defualt ���� �¾��� true
bool light_earth = false;
bool light_moon = false;

void init(void) {
	printf("init func called\n");
	glClearColor(0, 0, 0.50, 1.0f);

	// 0�� ���� ���� ���� ->������ ������ color & �Ӽ� ����
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//���� �Ӽ� ����
	
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
	
	//spotlight �Ӽ�
	//�ش� ���⿡ ���� ������ ȿ���� ���� �� ����

	/*glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	GLfloat spot_direction[] = { 1.0, 1.0, 0.0, 0.0 }; 
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);*/
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.5);


	//GLfloat lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);



	// ���� ����ġ�� 0�� ���� ����ġ �ѱ�
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//back face culling
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		printf("type s\n");
		if (spin_state)spin_state = false;
		else spin_state = true;
	}
	glutPostRedisplay();
}
/*Display �ݹ� �Լ� �����*/
void draw_axis() {
	glLineWidth(3); // ��ǥ���� �β�
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X���� red
	glVertex3f(0, 0, 0); glVertex3f(8, 0, 0);

	glColor3f(0, 1, 0); // Y���� green
	glVertex3f(0, 0, 0); glVertex3f(0, 8, 0);

	glColor3f(0, 0, 1); // Z���� blue
	glVertex3f(0, 0, 0); glVertex3f(0, 0, 8);
	glEnd();
	glLineWidth(1); // �β� �ٽ� ȯ��
}
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //���� model view Ȱ��ȭ
	//->��ǥ�迡�� ��ü�� ��ȯ, ������ �̵��� �ݿ�
	glLoadIdentity();//���� ��ķ� �ʱ�ȭ
	gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);

	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

	if (light_sun == true) {
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	//�¾�
	draw_axis();//���� ���� �׷����ϴ�.
	glRotatef(angle[0], 0, 1, 0);//�¾��� ���� 
	glColor3f(1, 0, 0);
	GLUquadricObj* gluNewQuadric();
	GLUquadricObj* qobj1 = gluNewQuadric();
	gluSphere(qobj1, 3, 50, 50);//�׸���.
	//�¾��� ��� ���� ����

	glPushMatrix();

	//���� 
	glRotatef(angle[1], 0, 1, 0);//���� ���� -> ȸ���� ��ǥ�迡��
	glTranslatef(5, 0, 0);		//x��ǥ�� 5 ������ ���� 
	glRotatef(angle[2], 0, 1, 0);//���� ���� ->������ ȸ���� ��ǥ�迡��
	glColor3f(0, 0, 1);
	GLUquadricObj* gluNewQuadric();
	GLUquadricObj* qobj2=gluNewQuadric();
	gluSphere(qobj2,1, 50,50);//�׸���.

	//������ �߽����� ������ ����
	if (light_earth==true) {
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	//��
	glRotatef(angle[3], 0, 1, 0);//�� ����
	glTranslatef(2, 0, 0);
	glRotatef(angle[4], 0, 1, 0);//�� ����
	glColor3f(1, 1, 0);
	GLUquadricObj* gluNewQuadric();
	GLUquadricObj* qobj3 = gluNewQuadric();
	gluSphere(qobj3, 0.5, 50, 50);//�׸���.

	//���� �߽����� ������ ����
	if (light_moon==true) {
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	glFlush();
	glutSwapBuffers();
}
void idle() {
	if (spin_state) {
		angle[0] += 0.01;//�¾� ����
		if (angle[0] > 360)angle[0] -= 360;
		angle[1] += 0.05;//���� ����
		if (angle[1] > 360)angle[1] -= 360;
		angle[2] += 0.2;//���� ���� 
		if (angle[2] > 360)angle[2] -= 360;
		angle[3] += 0.0001;//�� ����
		if (angle[3] > 360)angle[3] -= 360;
		angle[4] += 0.005;//������
		if (angle[4] > 360)angle[3] -= 360;
	}
	glutPostRedisplay();
}
void main_menu(int option) {
	if (option == 1)exit(1);
	else if (option == 2) {
		if (spin_state)spin_state = false;
		else spin_state = true;
	}
	else if (option == 3) {
		for (int i = 0; i < 5; i++) angle[i] = 0;
	}
	glutPostRedisplay();
}
void light_menu(int option) {
	if (option == 1) {
		printf("�¾� ���� ON\n");
		light_sun = true;
		light_earth = false;
		light_moon = false;
	}
	else if (option == 2) {
		printf("���� ���� ON\n");
		light_sun = false;
		light_earth = true;
		light_moon = false;
	}
	else if (option == 3) {
		printf("�� ���� ON\n");
		light_sun = false;
		light_earth = false;
		light_moon = true;
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


int main(int argc, char** argv) {
	int menu;							//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//���÷��� ��� ����
	glutInitWindowSize(700, 700);			//500 * 500���� ������
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����
	init();									//-> ����� �ʱ�ȭ �Լ�
	

	menu=glutCreateMenu(light_menu);
	glutAddMenuEntry("Sun", 1);
	glutAddMenuEntry("Earth", 2);
	glutAddMenuEntry("Moon", 3); 

	/*Poup menu ���� �� �߰�*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Spin", 2);
	glutAddMenuEntry("Init", 3);
	glutAddSubMenu("Light", menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�
	glutReshapeFunc(resize);				//resize �Լ�
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	/*Looping ����*/
	glutMainLoop();

	return 0;
}