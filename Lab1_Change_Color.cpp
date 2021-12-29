#include <gl/glut.h>
#include <stdio.h.>
#include <Windows.h>

void init(void) {
	/*ȭ���� �⺻������ dark blue ����*/
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);//R,G,B, ����
	//����: ���� ����
}
/*Display �ݹ� �Լ� �����*/
void draw(void) {
	//Ƽ�� �ӽ� ��ƾ
	glClear(GL_COLOR_BUFFER_BIT);	//�� ����
	glColor3f(1.0f, 1.0f, 1.0f);	//���ڸ� �ٲٸ� ���� ��ȭ
	glutWireTeapot(0.5f);			//wire�� ���� �� �����ڸ� �׸�
	glFlush();						//��ɾ� �о� �־� �ִ� ��.-> ����
}
/*���콺 ������ �ݹ� �Լ�*/
void mouse(int button, int state, int x, int y) { //
	//button: ����, ������, ��   state:��������, �ô���,   x,y: ��ǥ
	printf("Mouse button is clicked! (button: %d, state: %d, x: %d, y: %d)\n",
		button, state, x, y);
	//button: GLUT_LEFT_BUTTON (=0), GLUT_MIDDLE_BUTTON(=1),
	//		GLUT_RIGHT_BUTTON(=2)
	//state: GLUT_UP(=0), GLUT_DOWN(=1) UP: ������, DOWN: ������

}
/*Ű���� �Է� �ݹ� �Լ�*/
void keyboard(unsigned char key, int x, int y) {
	/*���ڵ��� �ؼ��ؼ� ���ϴ� ����� ����*/
	//Ű���忡�� � ������ ���ȴ��� ���
	printf("You pressed %c\n", key);

	//key: ���콺 ���� ��ȣ 
}
void idle(void) {
	/*���� ��ü�� ������(animation) ������ �̿�� ����*/
	printf("%d second has elapsed since the system was started\n",
		GetTickCount() / 1000);
}
//Menu ó�� �Լ� - �޴� ���ý� �����
void sub_menu_function(int option) {	//sub menu call back
	printf("Sub menu %d has been selected \n", option);
}
void main_menu_function(int option) {	//main menu call back
	printf("Main menu %d has been elected\n", option);
	if (option == 999) {				//999�Է� �� 
		exit(0);						//����
	}
}
//���� �ٲ� �Լ�
void sub_menu_function_change_color(int option) {		
	char color[5][20] = { "", "Red","Green","Blue","White"};
	float R[5] = {0,0.5f,0.0f,0.0f,1.0f},
	      G[5] = {0,0.0f,0.5f,0.0f,1.0f},
	      B[5] = {0,0.0f,0.5f,0.5f,1.0f};
	printf("Change to %s\n", color[option]);
	glClearColor(R[option], G[option], B[option], 1.0f);
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	int submenu1,submenu2;					//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//���÷��� ��� ����
	glutInitWindowSize(500, 500);			//500 * 500���� ������
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����
	init();									//-> ����� �ʱ�ȭ �Լ�

	/*Poup menu ���� �� �߰�*/
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Sub1", 1);
	glutAddMenuEntry("Sub2", 2);
	glutAddMenuEntry("Sub3", 3); /* 3���� �׸��� �ִ� �޴� ���� */

	submenu2 = glutCreateMenu(sub_menu_function_change_color);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3); 
	glutAddMenuEntry("White", 4);/* 4���� �׸��� �ִ� �޴� ���� */

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddMenuEntry("Go!", 11);
	glutAddSubMenu("Sub Menu", submenu1);
	glutAddSubMenu("Change Color", submenu2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);




	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�
	glutMouseFunc(mouse);					//���콺 ������, Ŭ���� ǥ��
	glutKeyboardFunc(keyboard);				//Ű���� �Է½� �ش� �Է��� ǥ��
	//glutIdleFunc(idle);						//���� ���� ���� off ��Ű���� ��
											//���޽ð��� �� �� ��� �Լ�


	/*Looping ����*/
	glutMainLoop();

	return 0;
}