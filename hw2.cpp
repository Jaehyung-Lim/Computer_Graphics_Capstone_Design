#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>

void init(void);
void draw();
void resize(int, int);


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12171841 임재형");
	init();
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(1, 1, 1, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	/*광원의 ambient, diffuse, specular 속성 지정*/
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };// Ia
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };// Id
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };// Is
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	/*물체의 표면에서 반사된 빛의 ambient, diffusem specular 속성 지정*/
	GLfloat mat_specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, 16);
	/*global ambient light 성분을 없앨 것*/
	GLfloat lmodel_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_POINT_SMOOTH);
}

void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 0, 0, 0, 0, 0, 1, 0); //시점, 점의 중심 설정
	
	GLfloat light_position[] = { -2.0, 1.0, 0.0, 1.0 }; //광원의 위치
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glColor4f(1.0f, 0.0f, 0.0f,1.0f);	//붉은 색 점
	glBegin(GL_POINTS);
	glNormal3f(0.0f, 1.0f, 0.0f); //법선 벡터
	glVertex3f(0.0f, 0.0f, 0.0f); //점의 위치
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void resize(int width, int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}