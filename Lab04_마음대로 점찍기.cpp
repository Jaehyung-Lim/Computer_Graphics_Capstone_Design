#include <stdio.h>
#include <Windows.h>
#include <gl/glut.h>


int x_pos[3][500], y_pos[3][500];		//점의 위치
int cnt_pos[3];							//점의 개수
int mode[3] = { GL_POINTS,GL_LINES,GL_TRIANGLES };	
int draw_mode = 0;						//defaut: 점
bool blending_state = false;
bool antialiasing_state = false;

void init(void) {
	/*화면의 기본색으로 dark blue 설정*/
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);//R,G,B, 알파
	//알파: 투명도 결정

	/* 화면 좌표 정보 설정 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 500, 0);
}
void draw_string(void* font, const char* str, int x, int y) {
	unsigned int i;
	glRasterPos2i(x, y);				   //최초 출력 위치 설정
	for (i = 0; i < strlen(str); i++) {	   //문자열의 길이만큼 루프
		glutBitmapCharacter(font, str[i]); //출력
	}
}
/*마우스 콜백 함수*/
void mouse(int button, int state, int x, int y) { //
	if (button == 0 && state == 0) { //왼쪽 버튼, 떼진것
		printf("x는 %d, y는 %d 눌렸음\n", x, y);
		x_pos[draw_mode][cnt_pos[draw_mode]] = x; //x좌표 저장
		y_pos[draw_mode][cnt_pos[draw_mode]] = y; //y좌표 저장
		cnt_pos[draw_mode]++;					  //좌표 개수 증가
	}
}
/*Display 콜백 함수 만들기*/
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

/*키보드 입력 콜백 함수*/
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
			antialiasing_state = true;	//state 변경
			glEnable(GL_BLEND);
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			// 다른 인자로 바꾸어 변화가 있는지 확인해 볼 것
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	//품질 우선
			//glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);	//속도 우선
			//glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);//자동 선택	
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
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//방식 설정
		}
	}
	glutPostRedisplay(); //누르는 즉시 바뀌게 해주는 역할
}

void shape_menu_function(int option) {
	if (option == 1) {
		printf("점을 그립니다.\n");
		draw_mode = 0;
	}
	else if (option == 2) {
		printf("선을 그립니다.\n");
		draw_mode = 1;
	}
	else if (option == 3) {
		printf("삼각형을 그립니다.\n");
		draw_mode = 2;
	}
}

void main_menu_function(int option) {	//main menu call back
	if (option == 999) {				//999입력 시 
		printf("Quit!!\n");
		exit(0);						//종료
	}
	else if (option == 888) {
		printf("Clear!!\n");
		glClear(GL_COLOR_BUFFER_BIT);
		cnt_pos[0] = 0; cnt_pos[1] = 0; cnt_pos[2] = 0; //점에 대한 정보 초기화
		glutPostRedisplay();
	}
}
int main(int argc, char** argv) {
	int submenu1;	//서브 메뉴

	/*Window 초기화*/
	glutInit(&argc, argv);					//윈도우 초기화 함수
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//디스플레이 모드 설정
	glutInitWindowSize(500, 500);			//500 * 500으로 사이즈
	glutInitWindowPosition(300, 300);		//300, 300으로 위치 설정
	glutCreateWindow("12171841 임재형 ");	//윈도우 이름을 설정 -> 학번이랑 이름으로

	init();									//-> 사용자 초기화 함수

	/*Pop up menu 생성 및 추가*/
	submenu1 = glutCreateMenu(shape_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3); /* 3개의 항목이 있는 메뉴 생성 */


	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddMenuEntry("Clear", 888);
	glutAddSubMenu("Shape", submenu1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수
	glutKeyboardFunc(keyboard);				//키보드 입력시 스위치 on/off
	glutMouseFunc(mouse);					//마우스 콜백 함수

	/*Looping 시작*/
	glutMainLoop();

	return 0;
}