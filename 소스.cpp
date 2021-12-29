#include <gl/glut.h>
#include <stdio.h.>
#include <Windows.h>
void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
/*Display �ݹ� �Լ� �����*/
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);	//�� ����

	glViewport(0, 0, 800, 600);				//viewport transformation

	glMatrixMode(GL_PROJECTION);		 //GL_PROJECTION ���
	glLoadIdentity();
	gluPerspective(45, 4.0 / 3.0, 1, 50);		//perspective projection

	glMatrixMode(GL_MODELVIEW);		//GL_MODELVIEW ���
	glLoadIdentity();
	gluLookAt(7, 5, 8, 0, 0, 0, 0, 1, 0);	//viewing transform

	glTranslatef(0, 1, 0);					//modeling transform

	glColor3f(1.0f, 0.0f, 0.0f);	//���������� ����
	glBegin(GL_TRIANGLES);				
		glVertex3f(3, -2, 1);		//p1
		glVertex3f(-5, 3, -1);		//p2
		glVertex3f(0, 3, -1);		//p3
	glEnd();						//��ǥ ��� ����
	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
		glVertex3f(3, -2, 1);		//p1
		glVertex3f(-5, 3, -1);		//p2
		glVertex3f(0, 3, -1);		//p3
	glEnd();						//��ǥ ��� ����

	glFlush();						
}

void mouse(int button, int state, int x, int y) { //
	printf("Mouse button is clicked! (button: %d, state: %d, x: %d, y: %d)\n",
		button, state, x, 600-y);
}
int main(int argc, char** argv) {
	/*Window �ʱ�ȭ*/
	glutInit(&argc, argv);				
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	
	glutInitWindowSize(800, 600);			
	glutInitWindowPosition(300, 300);		
	glutCreateWindow("12171841 ������ ");	
	init();									

	/* call back �Լ� ����*/
	glutDisplayFunc(draw);					
	glutMouseFunc(mouse);
	/*Looping ����*/
	glutMainLoop();

	return 0;
}