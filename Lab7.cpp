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
/*Display 콜백 함수 만들기*/
void draw_axis() {
	glLineWidth(3); // 좌표축의 두께
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X축은 red
	glVertex3f(0, 0, 0); glVertex3f(8, 0, 0);

	glColor3f(0, 1, 0); // Y축은 green
	glVertex3f(0, 0, 0); glVertex3f(0, 8, 0);

	glColor3f(0, 0, 1); // Z축은 blue
	glVertex3f(0, 0, 0); glVertex3f(0, 0, 8);
	glEnd();
	glLineWidth(1); // 두께 다시 환원
}
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //먼저 model view 활성화
	//->좌표계에서 물체의 변환, 시점의 이동등 반영
	glLoadIdentity();//단위 행렬로 초기화
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	//태양
	draw_axis();//축이 먼저 그려집니다.
	glRotatef(angle[0], 0, 1, 0);//태양의 자전 
	glColor3f(1, 0, 0);
	glutWireSphere(3,50,50); //태양을 그린다.
	
	//태양의 행렬 정보 저장
	glPushMatrix(); 

	//지구 
	glRotatef(angle[1], 0, 1, 0);//지구 공전 -> 회전된 좌표계에서
	glTranslatef(5, 0, 0);		//x좌표가 5 떨어진 곳에 
	glRotatef(angle[2], 0, 1, 0);//지구 자전 ->스스로 회전한 좌표계에서
	glColor3f(0, 0, 1);
	glutWireSphere(1, 50, 50);//그린다.

	//달
	glRotatef(angle[9], 0, 1, 0);//달 공전
	glTranslatef(2, 0, 0);
	glRotatef(angle[10], 0, 1, 0);//달 자전
	glColor3f(1, 1, 0);
	glutWireSphere(0.5, 50, 50);

	//다시 태양 행렬로
	glPopMatrix();
	glPushMatrix();//다시 태양 행렬 저장

	//화성 그림
	glRotatef(angle[3], 0, 1, 0);//화성의 공전 구현
	glTranslatef(6.5, 0, 0);//중심으로부터 이동
	glRotatef(angle[4], 0, 1, 0);//화성 자전
	glColor3f(1,0.65,0 );
	glutWireSphere(1, 50, 50);

	glPopMatrix();
	glPushMatrix();

	//금성 그림
	glRotatef(angle[5], 0, 1, 0);//금성의 공전 구현
	glTranslatef(3.5, 0, 0);//중심으로부터 이동
	glRotatef(angle[6], 0, 1, 0);//금성 자전
	glColor3f(0.59, 0.29, 0);
	glutWireSphere(0.6, 50, 50);
	
	glPopMatrix();
	glPushMatrix();
	//목성
	glRotatef(angle[7], 0, 1, 0);//목성의 공전 구현
	glTranslatef(8, 0, 0);//중심으로부터 이동
	glRotatef(angle[8], 0, 1, 0);//목성 자전
	glColor3f(0, 1, 1);
	glutWireSphere(1.5, 50, 50);

	glPopMatrix();
	glPushMatrix();
	//토성
	glRotatef(angle[11], 0, 1, 0);//토성의 공전 구현
	glTranslatef(10, 0, 0);//중심으로부터 이동
	glRotatef(angle[12], 0, 1, 0);//토성 자전
	glColor3f(0.5, 0.2, 0);
	glutWireSphere(1, 50, 50);

	glFlush();
	glutSwapBuffers();
}
void idle() {
	if (spin_state) {
		angle[0] += 0.01;//태양 자전
		if (angle[0] > 360)angle[0] -= 360;
		angle[1] += 0.1;//지구 공전
		if (angle[1] > 360)angle[1] -= 360;
		angle[2] += 1.3;//지구 자전 
		if (angle[2] > 360)angle[2] -= 360;
		angle[3] += 0.12;//화성 공전
		if (angle[3] > 360)angle[3] -= 360;
		angle[4] += 1.3;//화성 자전
		if (angle[4] > 360)angle[4] -= 360;
		angle[5] += 0.08;//금성 공전
		if (angle[5] > 360)angle[5] -= 360;
		angle[6] += 0.9;//금성 자전
		if (angle[6] > 360)angle[6] -= 360;
		angle[7] += 0.05;//목성 공전
		if (angle[7] > 360)angle[7] -= 360;
		angle[8] += 0.9;//목성 자전
		if (angle[8] > 360)angle[8] -= 360;
		angle[9] += 0.001;//달 공전
		if (angle[9] > 360)angle[9] -= 360;
		angle[10] += 0.005;//달자전
		if (angle[10] > 360)angle[10] -= 360;
		angle[11] += 0.08;//토성 공전
		if (angle[11] > 360)angle[11] -= 360;
		angle[12] += 0.005;//토성 자전
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
	int menu;							//서브 메뉴

	/*Window 초기화*/
	glutInit(&argc, argv);					//윈도우 초기화 함수
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//디스플레이 모드 설정
	glutInitWindowSize(700, 700);			//500 * 500으로 사이즈
	glutInitWindowPosition(300, 300);		//300, 300으로 위치 설정
	glutCreateWindow("12171841 임재형 ");	//윈도우 이름을 설정 -> 학번이랑 이름으로
	init();									//-> 사용자 초기화 함수

	/*Poup menu 생성 및 추가*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Spin", 2);
	glutAddMenuEntry("Init", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	

	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수
	glutReshapeFunc(resize);				//resize 함수
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	
	/*Looping 시작*/
	glutMainLoop();

	return 0;
}