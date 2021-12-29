#include <gl/glut.h>
#include <stdio.h.>
#include <Windows.h>
void draw_point();
void draw_line();
void draw_triangle();
void draw_quad();

void init(void) {
	/*화면의 기본색으로 dark blue 설정*/
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);//R,G,B, 알파
	//알파: 투명도 결정

	/* 화면 좌표 정보 설정 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}
/*Display 콜백 함수 만들기*/
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);	//색 설정
	draw_point();					//점을 그린다.
	//draw_line();					//선을 그린다.
	//draw_triangle();				//삼각형을 그린다.
	//draw_quad();					//사각형을 그린다.
}

/*점을 찍는 함수*/
void draw_point(void) {
	/*점의 색상을 붉은 색으로*/
	glColor3f(1.0f, 0.0f, 0.0f);	//빨간색으로 설정
	
	glPointSize(4.0f);				/*점의 크기 -> 초기값은 1.0*/
	glBegin(GL_POINTS);				//점을 그릴 것이라는 것을 표시
		glVertex2i(80, 80);
		glVertex2i(200, 80);
		glVertex2i(200, 300);
	glEnd();						//좌표 찍기 종료
	glFlush();						//명령어 밀어 넣어 주는 것.-> 실행
}
/*선을 그리는 함수*/
void draw_line(void){
	//glLineWidth(4.0f);
	//glEnable(GL_LINE_STIPPLE);	//선의 그리기 패턴을 ON
	//glLineStipple(3, 0xAAAA);	//3번 factor, 0xAAAA패턴 설정
	/* 선의 색상을 노란색으로 */
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2i(30, 40);
		glVertex2i(280, 350);
		glVertex2i(400, 250);
		glVertex2i(300, 200);
	glEnd();
	glFlush();						//명령어 밀어 넣어 주는 것.-> 실행
}
/*
-선 두께 바꾸기
	glLineWidth (float Width)를 이용하여 두께 조절
-선 그리기 모드 변경
	glBegin의 인자를 변경
		GL_LINES
		GL_LINE_STRIP
		GL_LINE_LOOP
*/
/*면 그리기*/
void draw_triangle(void){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//선으로 그림
	/* 면의 색상을 노란색으로 */
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);			//삼각형 그리기 함수
		glVertex2i(80, 80);
		glVertex2i(200, 80);
		glVertex2i(200, 300);
	glEnd();
	glFlush();						//명령어 밀어 넣어 주는 것.-> 실행
}
void draw_quad() {
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	/* 면의 색상을 노란색으로 */
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);				//사각형 그리기 함수
		glVertex2i(150, 160);
		glVertex2i(150, 360);
		glVertex2i(300, 320);
		glVertex2i(360, 180);
	glEnd();
	glFlush();
}
//Menu 처리 함수 - 메뉴 선택시 수행됨
void point_menu_function(int option) {
	glClear(GL_COLOR_BUFFER_BIT);
	if (option == 1) {
		printf("점 3개를 찍습니다.\n");
		draw_point();
	}
	else if (option == 2) {
		printf("점 5개를 찍습니다.\n");
		glColor3f(1.0f, 1.0f, 0.0f);
		/*점의 크기 -> 초기값은 1.0*/
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
    if (option == 1) { //삼각형
		printf("삼각형을 그립니다.\n");
		draw_triangle();
	}
	else if (option == 2) {
		printf("이어진 삼각형(Triangle Strip)들을 그립니다.\n");
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
		printf("삼각형들을 부채형태(Triangle Fan)로 그립니다.\n");
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
		printf("사각형 1개를 그립니다.\n");
		draw_quad();
	}
	else if (option == 5) {
		printf("사각형들을 그립니다.\n");
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
		printf("이어진 사각형(Quads Strip)들을 그립니다.\n");
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
		printf("임의의 다각형을 그립니다.\n");
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
	if (option == 1) {	//선
		printf("2개의 선을 그립니다.\n");
		draw_line();
	}
	else if (option == 2) { //점 선
		printf("패턴이 있는 선을 그립니다.\n");
		glLineWidth(2.0f);			//선의 두께 설정
		glEnable(GL_LINE_STIPPLE);	//선의 그리기 패턴을 설정
		glLineStipple(3, 0xAAAA);	//3번 factor, 0xAAAA패턴 설정
		draw_line();
	}
	else if (option == 3) { //루프 선
		printf("루프 선을 그립니다.\n");
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
	else if (option == 4) { //이어진 선
		printf("시점과 종점을 제외한 연결된 선을 그립니다.\n");
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
	if (option == 999) {				//999입력 시 
		exit(0);						//종료
	}
}

int main(int argc, char** argv) {
	int submenu1, submenu2, submenu3;	//서브 메뉴

	/*Window 초기화*/
	glutInit(&argc, argv);					//윈도우 초기화 함수
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//디스플레이 모드 설정
	glutInitWindowSize(500, 500);			//500 * 500으로 사이즈
	glutInitWindowPosition(300, 300);		//300, 300으로 위치 설정
	glutCreateWindow("12171841 임재형 ");	//윈도우 이름을 설정 -> 학번이랑 이름으로
	init();									//-> 사용자 초기화 함수

	/*Poup menu 생성 및 추가*/
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

	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수

	/*Looping 시작*/
	glutMainLoop();

	return 0;
}