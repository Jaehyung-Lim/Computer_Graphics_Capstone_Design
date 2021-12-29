#include <gl/glut.h>
#include <stdio.h.>
#include <Windows.h>
double spin;
int spin_state=1;
int draw_mode=3; //default를 삼각형으로 
int dx=250, dy=250;

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
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(dx%500, dy%500, 0);		//3번 순서: 250, 250 평행이동 -> 다시 좌표 원상복귀
	glRotatef(spin, 0, 0, 1);				//2번 순서: z축을 축으로 60도 회전
	glTranslatef((-dx)%500, (-dy)%500, 0);	//1번 순서: -250,-250으로 평행이동						

	switch (draw_mode) {
		case 1: {//점
			glColor3f(1.0f, 0.0f, 0.0f);
			/*점의 크기 -> 초기값은 1.0*/
			glPointSize(4.0f);
				glBegin(GL_POINTS);
				glVertex2i(80, 80);
				glVertex2i(200, 80);
				glVertex2i(200, 300);
			glEnd();
			glFlush();
			break;
		}
		case 2: {//선
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
		case 3: {//삼각형
			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);
				glVertex2i(80, 80);
				glVertex2i(200, 80);
				glVertex2i(200, 300);
				glEnd();
			glFlush();
			break;
		}
		case 4: {//사각형
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

/*키보드 입력 콜백 함수*/
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
		printf("점을 그립니다.\n");
		draw_mode = 1;
	}
	else if (option == 2) {
		printf("선을 그립니다.\n");
		draw_mode = 2;
	}
	else if (option == 3) {	
		printf("삼각형을 그립니다.\n");
		draw_mode = 3;
	}
	else if (option == 4) {
		printf("사각형을 그립니다.\n");
		draw_mode = 4;
	}
	else if (option == 5) {
		printf("다각형을 그립니다.\n");
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
		printf("왼쪽으로 이동\n");
		dx -= 10; 
	}
	else { //right
		printf("오른쪽으로 이동\n");
		dx += 10; 
	}	
}
void y_menu(int option) {
	if (option == 1) { 
		printf("위쪽으로 이동\n");
		dy += 10; 
	}
	else {
		printf("아래쪽으로 이동\n");
		dy -= 10; 
	}
}
void main_menu_function(int option) {	//main menu call back
	printf("Main menu %d has been elected\n", option);
	if (option == 999) {				//999입력 시 
		exit(0);						//종료
	}
}
int main(int argc, char** argv) {
	int submenu1, submenu2, submenu3, submenu4;	//서브 메뉴

	/*Window 초기화*/
	glutInit(&argc, argv);					//윈도우 초기화 함수
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//디스플레이 모드 설정
	glutInitWindowSize(500, 500);			//500 * 500으로 사이즈
	glutInitWindowPosition(300, 300);		//300, 300으로 위치 설정
	glutCreateWindow("12171841 임재형 ");	//윈도우 이름을 설정 -> 학번이랑 이름으로
	
	init();									//-> 사용자 초기화 함수

	/*Poup menu 생성 및 추가*/
	submenu1 = glutCreateMenu(shape_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3); /* 5개의 항목이 있는 메뉴 생성 */
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


	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수
	glutKeyboardFunc(keyboard);				//키보드 입력시 해당 입력을 표시
	glutSpecialFunc(keyboard_special);
	glutIdleFunc(idle);					//애니메이션
											
	/*Looping 시작*/
	glutMainLoop();

	return 0;
}