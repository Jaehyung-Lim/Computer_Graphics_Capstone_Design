#include <gl/glut.h>
#include <stdio.h.>
#include <Windows.h>

void init(void) {
	/*화면의 기본색으로 dark blue 설정*/
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);//R,G,B, 알파
	//알파: 투명도 결정
}
/*Display 콜백 함수 만들기*/
void draw(void) {
	//티팟 임시 루틴
	glClear(GL_COLOR_BUFFER_BIT);	//색 설정
	glColor3f(1.0f, 1.0f, 1.0f);	//인자를 바꾸면 색이 변화
	glutWireTeapot(0.5f);			//wire로 속이 빈 주전자를 그림
	glFlush();						//명령어 밀어 넣어 주는 것.-> 실행
}
/*마우스 움직임 콜백 함수*/
void mouse(int button, int state, int x, int y) { //
	//button: 왼쪽, 오른쪽, 휠   state:눌렀는지, 뗐는지,   x,y: 좌표
	printf("Mouse button is clicked! (button: %d, state: %d, x: %d, y: %d)\n",
		button, state, x, y);
	//button: GLUT_LEFT_BUTTON (=0), GLUT_MIDDLE_BUTTON(=1),
	//		GLUT_RIGHT_BUTTON(=2)
	//state: GLUT_UP(=0), GLUT_DOWN(=1) UP: 떼진것, DOWN: 누른것

}
/*키보드 입력 콜백 함수*/
void keyboard(unsigned char key, int x, int y) {
	/*인자들을 해석해서 원하는 기능을 구현*/
	//키보드에서 어떤 자판이 눌렸는지 출력
	printf("You pressed %c\n", key);

	//key: 마우스 문자 번호 
}
void idle(void) {
	/*추후 물체의 움직임(animation) 구현에 이용될 것임*/
	printf("%d second has elapsed since the system was started\n",
		GetTickCount() / 1000);
}
//Menu 처리 함수 - 메뉴 선택시 수행됨
void sub_menu_function(int option) {	//sub menu call back
	printf("Sub menu %d has been selected \n", option);
}
void main_menu_function(int option) {	//main menu call back
	printf("Main menu %d has been elected\n", option);
	if (option == 999) {				//999입력 시 
		exit(0);						//종료
	}
}
//배경색 바꿈 함수
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
	int submenu1,submenu2;					//서브 메뉴

	/*Window 초기화*/
	glutInit(&argc, argv);					//윈도우 초기화 함수
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//디스플레이 모드 설정
	glutInitWindowSize(500, 500);			//500 * 500으로 사이즈
	glutInitWindowPosition(300, 300);		//300, 300으로 위치 설정
	glutCreateWindow("12171841 임재형 ");	//윈도우 이름을 설정 -> 학번이랑 이름으로
	init();									//-> 사용자 초기화 함수

	/*Poup menu 생성 및 추가*/
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Sub1", 1);
	glutAddMenuEntry("Sub2", 2);
	glutAddMenuEntry("Sub3", 3); /* 3개의 항목이 있는 메뉴 생성 */

	submenu2 = glutCreateMenu(sub_menu_function_change_color);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3); 
	glutAddMenuEntry("White", 4);/* 4개의 항목이 있는 메뉴 생성 */

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddMenuEntry("Go!", 11);
	glutAddSubMenu("Sub Menu", submenu1);
	glutAddSubMenu("Change Color", submenu2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);




	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수
	glutMouseFunc(mouse);					//마우스 움직임, 클릭을 표시
	glutKeyboardFunc(keyboard);				//키보드 입력시 해당 입력을 표시
	//glutIdleFunc(idle);						//추후 사용시 까지 off 시키도록 함
											//유휴시간에 할 일 등록 함수


	/*Looping 시작*/
	glutMainLoop();

	return 0;
}