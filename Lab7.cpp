#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdio.h.>
#include <math.h>
#include <Windows.h>

double angle[22];
bool spin_state=true;

void init(void) {
	printf("init func called\n");

	glClearColor(0, 0, 0, 1.0f);
	for (int i = 0; i < 22; i++) angle[i]=i * 10;
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
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //���� model view Ȱ��ȭ
	//->��ǥ�迡�� ��ü�� ��ȯ, ������ �̵��� �ݿ�
	glLoadIdentity();//���� ��ķ� �ʱ�ȭ
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	//�¾�
	draw_axis();//���� ���� �׷����ϴ�.
	glRotatef(angle[0], 0, 1, 0);//�¾��� ���� 
	glColor3f(1, 0, 0);
	glutWireSphere(3,50,50); //�¾��� �׸���.
	
	//�¾��� ��� ���� ����
	glPushMatrix(); 

	//���� 
	glRotatef(angle[1], 0, 1, 0);//���� ���� -> ȸ���� ��ǥ�迡��
	glTranslatef(5, 0, 0);		//x��ǥ�� 5 ������ ���� 
	glRotatef(angle[2], 0, 1, 0);//���� ���� ->������ ȸ���� ��ǥ�迡��
	glColor3f(0, 0, 1);
	glutWireSphere(1, 50, 50);//�׸���.

	//��
	glRotatef(angle[9], 0, 1, 0);//�� ����
	glTranslatef(2, 0, 0);
	glRotatef(angle[10], 0, 1, 0);//�� ����
	glColor3f(1, 1, 0);
	glutWireSphere(0.5, 50, 50);

	//�ٽ� �¾� ��ķ�
	glPopMatrix();
	glPushMatrix();//�ٽ� �¾� ��� ����

	//ȭ�� �׸�
	glRotatef(angle[3], 0, 1, 0);//ȭ���� ���� ����
	glTranslatef(6.5, 0, 0);//�߽����κ��� �̵�
	glRotatef(angle[4], 0, 1, 0);//ȭ�� ����
	glColor3f(1,0.65,0 );
	glutWireSphere(1, 50, 50);

	glPopMatrix();
	glPushMatrix();

	//�ݼ� �׸�
	glRotatef(angle[5], 0, 1, 0);//�ݼ��� ���� ����
	glTranslatef(3.5, 0, 0);//�߽����κ��� �̵�
	glRotatef(angle[6], 0, 1, 0);//�ݼ� ����
	glColor3f(0.59, 0.29, 0);
	glutWireSphere(0.6, 50, 50);
	
	glPopMatrix();
	glPushMatrix();
	//��
	glRotatef(angle[7], 0, 1, 0);//���� ���� ����
	glTranslatef(8, 0, 0);//�߽����κ��� �̵�
	glRotatef(angle[8], 0, 1, 0);//�� ����
	glColor3f(0, 1, 1);
	glutWireSphere(1.5, 50, 50);

	glPopMatrix();
	glPushMatrix();
	//�伺
	glRotatef(angle[11], 0, 1, 0);//�伺�� ���� ����
	glTranslatef(10, 0, 0);//�߽����κ��� �̵�
	glRotatef(angle[12], 0, 1, 0);//�伺 ����
	glColor3f(0.5, 0.2, 0);
	glutWireSphere(1, 50, 50);

	glFlush();
	glutSwapBuffers();
}
void idle() {
	if (spin_state) {
		angle[0] += 0.01;//�¾� ����
		if (angle[0] > 360)angle[0] -= 360;
		angle[1] += 0.1;//���� ����
		if (angle[1] > 360)angle[1] -= 360;
		angle[2] += 1.3;//���� ���� 
		if (angle[2] > 360)angle[2] -= 360;
		angle[3] += 0.12;//ȭ�� ����
		if (angle[3] > 360)angle[3] -= 360;
		angle[4] += 1.3;//ȭ�� ����
		if (angle[4] > 360)angle[4] -= 360;
		angle[5] += 0.08;//�ݼ� ����
		if (angle[5] > 360)angle[5] -= 360;
		angle[6] += 0.9;//�ݼ� ����
		if (angle[6] > 360)angle[6] -= 360;
		angle[7] += 0.05;//�� ����
		if (angle[7] > 360)angle[7] -= 360;
		angle[8] += 0.9;//�� ����
		if (angle[8] > 360)angle[8] -= 360;
		angle[9] += 0.001;//�� ����
		if (angle[9] > 360)angle[9] -= 360;
		angle[10] += 0.005;//������
		if (angle[10] > 360)angle[10] -= 360;
		angle[11] += 0.08;//�伺 ����
		if (angle[11] > 360)angle[11] -= 360;
		angle[12] += 0.005;//�伺 ����
		if (angle[12] > 360)angle[12] -= 360;

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
		for (int i = 0; i < 10; i++) angle[i] = i * 10;
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

	/*Poup menu ���� �� �߰�*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Spin", 2);
	glutAddMenuEntry("Init", 3);
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