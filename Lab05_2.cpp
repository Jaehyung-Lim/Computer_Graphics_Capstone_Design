#include <gl/glut.h>
#include <stdio.h.>
#include <Windows.h>
double spin;
int spin_state=1;
int draw_mode=3; //default�� �ﰢ������ 
int dx=250, dy=250;

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
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(dx%500, dy%500, 0);		//3�� ����: 250, 250 �����̵� -> �ٽ� ��ǥ ���󺹱�
	glRotatef(spin, 0, 0, 1);				//2�� ����: z���� ������ 60�� ȸ��
	glTranslatef((-dx)%500, (-dy)%500, 0);	//1�� ����: -250,-250���� �����̵�						

	switch (draw_mode) {
		case 1: {//��
			glColor3f(1.0f, 0.0f, 0.0f);
			/*���� ũ�� -> �ʱⰪ�� 1.0*/
			glPointSize(4.0f);
				glBegin(GL_POINTS);
				glVertex2i(80, 80);
				glVertex2i(200, 80);
				glVertex2i(200, 300);
			glEnd();
			glFlush();
			break;
		}
		case 2: {//��
			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_LINES);
				glVertex2i(30, 40);
				glVertex2i(280, 350);
				glVertex2i(400, 250);
				glVertex2i(300, 200);
			glEnd();
			glFlush();
			break;
		}
		case 3: {//�ﰢ��
			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);
				glVertex2i(80, 80);
				glVertex2i(200, 80);
				glVertex2i(200, 300);
				glEnd();
			glFlush();
			break;
		}
		case 4: {//�簢��
			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_QUAD_STRIP);
				glVertex2i(150, 160);
				glVertex2i(350, 160);
				glVertex2i(160, 380);
				glVertex2i(300, 320);
			glEnd();
			glFlush();
			break;
		}
		case 5: {//polygon
			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex2i(150, 280);
				glVertex2i(200, 380);
				glVertex2i(270, 300);
				glVertex2i(240, 100);
				glVertex2i(180, 90);
			glEnd();
			glFlush();
			break;
		}
	}
	glutSwapBuffers();
}

/*Ű���� �Է� �ݹ� �Լ�*/
void keyboard(unsigned char key, int x, int y) {
	printf("You pressed %c\n", key);
	if (key == 's') {
		if (spin_state == 1) spin_state = 0;
		else spin_state = 1;
	}
}
void keyboard_special(int key, int x, int y){
	switch (key){
	case GLUT_KEY_LEFT: {
		printf("move left\n");
		dx -= 10;
		break;
	}
	case GLUT_KEY_RIGHT: {
		printf("move right\n");
		dx += 10;
		break;
	}
	case GLUT_KEY_UP: {
		printf("move up\n");
		dy += 10;
		break;
	}
	case GLUT_KEY_DOWN: {
		printf("move down\n");
		dy -= 10;
		break;
	}
	default:
	break;
	}
	glutPostRedisplay();
}
void idle(void) {
	if (spin_state==1) {
		spin += 0.1;
		if (spin > 360) spin -= 360;
		glutPostRedisplay();
	}
}
void shape_menu_function(int option) {
	if (option == 1) {
		printf("���� �׸��ϴ�.\n");
		draw_mode = 1;
	}
	else if (option == 2) {
		printf("���� �׸��ϴ�.\n");
		draw_mode = 2;
	}
	else if (option == 3) {	
		printf("�ﰢ���� �׸��ϴ�.\n");
		draw_mode = 3;
	}
	else if (option == 4) {
		printf("�簢���� �׸��ϴ�.\n");
		draw_mode = 4;
	}
	else if (option == 5) {
		printf("�ٰ����� �׸��ϴ�.\n");
		draw_mode = 5;
	}
	glutPostRedisplay();
}
void spin_menu(int option) {
	if (option == 1) { 
		printf("Spin On\n");
		spin_state = 1; 
	}
	else {
		printf("Spin Off\n");
		spin_state = 0; 
	}
}
void x_menu(int option) {
	if (option == 1) { //left
		printf("�������� �̵�\n");
		dx -= 10; 
	}
	else { //right
		printf("���������� �̵�\n");
		dx += 10; 
	}	
}
void y_menu(int option) {
	if (option == 1) { 
		printf("�������� �̵�\n");
		dy += 10; 
	}
	else {
		printf("�Ʒ������� �̵�\n");
		dy -= 10; 
	}
}
void main_menu_function(int option) {	//main menu call back
	printf("Main menu %d has been elected\n", option);
	if (option == 999) {				//999�Է� �� 
		exit(0);						//����
	}
}
int main(int argc, char** argv) {
	int submenu1, submenu2, submenu3, submenu4;	//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//���÷��� ��� ����
	glutInitWindowSize(500, 500);			//500 * 500���� ������
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����
	
	init();									//-> ����� �ʱ�ȭ �Լ�

	/*Poup menu ���� �� �߰�*/
	submenu1 = glutCreateMenu(shape_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3); /* 5���� �׸��� �ִ� �޴� ���� */
	glutAddMenuEntry("Quad", 4);
	glutAddMenuEntry("Polygon", 5);
	
	
	submenu2 = glutCreateMenu(x_menu);
	glutAddMenuEntry("Left", 1);
	glutAddMenuEntry("Right", 2);
	
	submenu3 = glutCreateMenu(y_menu);
	glutAddMenuEntry("Up", 1);
	glutAddMenuEntry("Down", 2);

	submenu4 = glutCreateMenu(spin_menu);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Stop", 2);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddSubMenu("Shape", submenu1);
	glutAddSubMenu("X trans", submenu2);
	glutAddSubMenu("Y trans", submenu3);
	glutAddSubMenu("Spin", submenu4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�
	glutKeyboardFunc(keyboard);				//Ű���� �Է½� �ش� �Է��� ǥ��
	glutSpecialFunc(keyboard_special);
	glutIdleFunc(idle);					//�ִϸ��̼�
											
	/*Looping ����*/
	glutMainLoop();

	return 0;
}