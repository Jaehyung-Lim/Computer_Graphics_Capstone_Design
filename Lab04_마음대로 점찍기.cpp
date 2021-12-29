#include <stdio.h>
#include <Windows.h>
#include <gl/glut.h>


int x_pos[3][500], y_pos[3][500];		//���� ��ġ
int cnt_pos[3];							//���� ����
int mode[3] = { GL_POINTS,GL_LINES,GL_TRIANGLES };	
int draw_mode = 0;						//defaut: ��
bool blending_state = false;
bool antialiasing_state = false;

void init(void) {
	/*ȭ���� �⺻������ dark blue ����*/
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);//R,G,B, ����
	//����: ���� ����

	/* ȭ�� ��ǥ ���� ���� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 500, 0);
}
void draw_string(void* font, const char* str, int x, int y) {
	unsigned int i;
	glRasterPos2i(x, y);				   //���� ��� ��ġ ����
	for (i = 0; i < strlen(str); i++) {	   //���ڿ��� ���̸�ŭ ����
		glutBitmapCharacter(font, str[i]); //���
	}
}
/*���콺 �ݹ� �Լ�*/
void mouse(int button, int state, int x, int y) { //
	if (button == 0 && state == 0) { //���� ��ư, ������
		printf("x�� %d, y�� %d ������\n", x, y);
		x_pos[draw_mode][cnt_pos[draw_mode]] = x; //x��ǥ ����
		y_pos[draw_mode][cnt_pos[draw_mode]] = y; //y��ǥ ����
		cnt_pos[draw_mode]++;					  //��ǥ ���� ����
	}
}
/*Display �ݹ� �Լ� �����*/
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(20.0f);
	glLineWidth(10.0f);
	for (int j = 0; j < 3; j++) {
		if (j == 0) glColor4f(1.0f, 1.0f, 0.0f, 0.75);//point:yellow
		else if (j == 1)glColor4f(1.0f, 1.0f, 0.0f, 0.75);//Line: yellow
		else if (j == 2) glColor4f(0.0f, 1.0f, 1.0f, 0.75); //triangle: cyan
		glBegin(mode[j]);
		for (int i = 0; i < cnt_pos[j]; i++)glVertex2i(x_pos[j][i], y_pos[j][i]);
		glEnd();
	}
	glFlush();
	glColor3f(1.0f, 1.0f, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "12171841 Lim Jae Hyung", 10, 100);
	draw_string(GLUT_BITMAP_HELVETICA_18, "12171841 Lim Jae Hyung", 10, 150);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "12171841 Lim Jae Hyung", 10, 200);
	draw_string(GLUT_BITMAP_HELVETICA_10, "12171841 Lim Jae Hyung", 10, 250);
	glutSwapBuffers();
}

/*Ű���� �Է� �ݹ� �Լ�*/
void keyboard(unsigned char key, int x, int y) {
	if (key == 'a') {
		if (antialiasing_state == true) {
			printf("Antialiasing Off\n");
			antialiasing_state = false;
			glDisable(GL_POINT_SMOOTH);
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
		}
		else {
			printf("Antialiasing On\n");
			antialiasing_state = true;	//state ����
			glEnable(GL_BLEND);
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			// �ٸ� ���ڷ� �ٲپ� ��ȭ�� �ִ��� Ȯ���� �� ��
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	//ǰ�� �켱
			//glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);	//�ӵ� �켱
			//glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);//�ڵ� ����	
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		}
	}
	if (key == 'b') {
		if (blending_state == true) {
			printf("Alpha-blending Off\n");
			blending_state = false;
			glDisable(GL_BLEND);
		}
		else {
			printf("Alpha-blending On\n");
			blending_state = true;
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//��� ����
		}
	}
	glutPostRedisplay(); //������ ��� �ٲ�� ���ִ� ����
}

void shape_menu_function(int option) {
	if (option == 1) {
		printf("���� �׸��ϴ�.\n");
		draw_mode = 0;
	}
	else if (option == 2) {
		printf("���� �׸��ϴ�.\n");
		draw_mode = 1;
	}
	else if (option == 3) {
		printf("�ﰢ���� �׸��ϴ�.\n");
		draw_mode = 2;
	}
}

void main_menu_function(int option) {	//main menu call back
	if (option == 999) {				//999�Է� �� 
		printf("Quit!!\n");
		exit(0);						//����
	}
	else if (option == 888) {
		printf("Clear!!\n");
		glClear(GL_COLOR_BUFFER_BIT);
		cnt_pos[0] = 0; cnt_pos[1] = 0; cnt_pos[2] = 0; //���� ���� ���� �ʱ�ȭ
		glutPostRedisplay();
	}
}
int main(int argc, char** argv) {
	int submenu1;	//���� �޴�

	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);					//������ �ʱ�ȭ �Լ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//���÷��� ��� ����
	glutInitWindowSize(500, 500);			//500 * 500���� ������
	glutInitWindowPosition(300, 300);		//300, 300���� ��ġ ����
	glutCreateWindow("12171841 ������ ");	//������ �̸��� ���� -> �й��̶� �̸�����

	init();									//-> ����� �ʱ�ȭ �Լ�

	/*Pop up menu ���� �� �߰�*/
	submenu1 = glutCreateMenu(shape_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3); /* 3���� �׸��� �ִ� �޴� ���� */


	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddMenuEntry("Clear", 888);
	glutAddSubMenu("Shape", submenu1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					//draw() -> ���� �׸��� �Լ�
	glutKeyboardFunc(keyboard);				//Ű���� �Է½� ����ġ on/off
	glutMouseFunc(mouse);					//���콺 �ݹ� �Լ�

	/*Looping ����*/
	glutMainLoop();

	return 0;
}