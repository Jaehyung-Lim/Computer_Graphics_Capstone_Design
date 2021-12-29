#include <gl/glut.h>
#include <gl/freeglut.h>
#include <stdio.h.>
#include <math.h>
#include <Windows.h>

double angle[5];
bool spin_state = false;

bool light_sun = false; 
bool light_earth = false;
bool light_moon = false;
bool light_random = false;
bool light_camera = true;

#define PI 3.141592653589

double radius = 13 * sqrt(3);
double theta = 45, pi = 45;
double cam[3] = { radius * sin(theta * PI / 180) * sin(pi * PI / 180),radius * cos(theta * PI / 180),
radius * sin(theta * PI / 180) * cos(pi * PI / 180) };//카메라의 좌표
double up[3] = { 0,1,0 };	 //카메라의 방향

void setup() {
	// 0번 조명 관련 설정 ->각각의 광원의 color & 속성 지정
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//감쇄 속성 지정

	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

	//spotlight 속성
	//해당 방향에 가야 조명의 효과를 받을 수 있음

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	//GLfloat spot_direction[] = { 1.0, 1.0, 0.0, 0.0 };
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.5);


	//GLfloat lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}
void init(void) {
	printf("init func called\n");
	glClearColor(0, 0, 0.50, 1.0f);
	// 재질의 반사 특성 설정 – init()에 추가
	GLfloat ambient_Sun[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Sun);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	setup();
	
	// 조명 스위치와 0번 조명 스위치 켜기
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//back face culling
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		printf("type s\n");
		if (spin_state)spin_state = false;
		else spin_state = true;
	}
	if (key=='0') {
		printf("0번. 카메라 위치 조명 ON\n");
		light_sun = false; 
		light_earth = false;
		light_moon = false;
		light_random = false;
		light_camera = true; //on
	}
	else if (key== '1') {
		printf("1번. 태양 조명 ON\n");
		light_sun = true; //on
		light_earth = false;
		light_moon = false;
		light_random = false;
		light_camera = true;
	}
	else if (key == '2') {
		printf("2번. 지구 조명 ON\n");
		light_sun = false;
		light_earth = true; //on
		light_moon = false;
		light_random = false;
		light_camera = false;
	}
	else if (key=='3') {
		printf("3번. 달 조명 ON\n");
		light_sun = false;
		light_earth = false;
		light_moon = true; //on
		light_random = false;
		light_camera = false;
	}
	else if (key == '4') {
		printf("4번. World 좌표계 상 임의의 위치 조명 ON\n");
		light_sun = false;
		light_earth = false;
		light_moon = false;
		light_random = true; //on
		light_camera = false;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //먼저 model view 활성화
	//->좌표계에서 물체의 변환, 시점의 이동등 반영
	glLoadIdentity();//단위 행렬로 초기화

	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat emission[] = { 1.0f, 0.0f, 0.0f, 1.0f };

	if (theta > 0 && theta <= 180)up[1] = 1;
	if (theta > 180 && theta <= 360)up[1] = -1;

	cam[0] = radius * sin(theta * PI / 180) * sin(pi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	cam[2] = radius * sin(theta * PI / 180) * cos(pi * PI / 180);
	gluLookAt(cam[0], cam[1], cam[2], 0,0,0, up[0], up[1], up[2]);

	if (light_random) {
		light_position[0] = -15; light_position[1] = -15; light_position[2] = 15; 
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	if (light_camera) {
		light_position[0] = cam[0]; light_position[1] = cam[1]; light_position[2] = cam[2]; 
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	light_position[0] = 0; light_position[1] = 0; light_position[2] = 0;

	if (light_sun) {
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	//태양
	draw_axis();//축이 먼저 그려집니다.
	glRotatef(angle[0], 0, 1, 0);//태양의 자전 
	glColor3f(1, 0, 0);
	
	if (light_sun) {
		emission[0] = 1.0f; emission[1] = 0.0f; emission[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}

	glutSolidSphere(3, 30, 30);

	if (light_sun) {
		emission[0] = 0.0f; emission[1] = 0.0f; emission[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}
	//태양의 행렬 정보 저장

	glPushMatrix();

	//지구 
	glRotatef(angle[1], 0, 1, 0);//지구 공전 -> 회전된 좌표계에서
	glTranslatef(5, 0, 0);		//x좌표가 5 떨어진 곳에 
	glRotatef(angle[2], 0, 1, 0);//지구 자전 ->스스로 회전한 좌표계에서
	glColor3f(0, 0, 1);

	if (light_earth) {
		emission[0] = 0.0f; emission[1] = 0.0f; emission[2] = 1.0f;
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}

	glutSolidSphere(1, 30, 30);

	if (light_earth) {
		emission[0] = 0.0f; emission[1] = 0.0f; emission[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}

	//지구를 중심으로 조명을 설정
	if (light_earth) {
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	//달
	glRotatef(angle[3], 0, 1, 0);//달 공전
	glTranslatef(2, 0, 0);
	glRotatef(angle[4], 0, 1, 0);//달 자전
	glColor3f(1, 1, 0);

	if (light_moon) {
		emission[0] = 1.0f; emission[1] = 1.0f; emission[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}

	glutSolidSphere(0.5, 30, 30);

	if (light_moon) {
		emission[0] = 0.0f; emission[1] = 0.0f; emission[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	}

	//달을 중심으로 조명을 설정
	if (light_moon) {
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}

	glFlush();
	glutSwapBuffers();
}
void special_keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		pi -= 5;
		if (pi < 0)pi = 355;
	}
	else if (key == GLUT_KEY_RIGHT) {
		pi += 5;
		if (pi >= 360)pi = 0;
	}
	else if (key == GLUT_KEY_UP) {
		theta -= 5;
		if (theta <= 0)theta = 360;

	}
	else if (key == GLUT_KEY_DOWN) {
		theta += 5;
		if (theta > 360)theta = 5;
	}
	glutPostRedisplay();
}
void mouseWheel(int buotton, int dir, int x, int y) {

	if (dir > 0) { //가까워 지는 것
		printf("Zoom in\n");
		radius *= 0.9;
	}
	else {
		printf("Zoon out\n");
		radius = radius * 10 / 9;
	}
	cam[2] = radius * sin(theta * PI / 180) * cos(pi * PI / 180);
	cam[0] = radius * sin(theta * PI / 180) * sin(pi * PI / 180);
	cam[1] = radius * cos(theta * PI / 180);
	glutPostRedisplay();
}
void idle() {
	if (spin_state) {
		angle[0] += 0.01;//태양 자전
		if (angle[0] > 360)angle[0] -= 360;
		angle[1] += 0.05;//지구 공전
		if (angle[1] > 360)angle[1] -= 360;
		angle[2] += 0.2;//지구 자전 
		if (angle[2] > 360)angle[2] -= 360;
		angle[3] += 0.0001;//달 공전
		if (angle[3] > 360)angle[3] -= 360;
		angle[4] += 0.005;//달자전
		if (angle[4] > 360)angle[3] -= 360;
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
		for (int i = 0; i < 5; i++) angle[i] = 0;
		theta = 45, pi = 45;
		radius = 13 * sqrt(3);
		cam[0] = radius * sin(theta * PI / 180) * sin(pi * PI / 180),
			cam[1] = radius * cos(theta * PI / 180), cam[2] = radius * sin(theta * PI / 180) * cos(pi * PI / 180);
		up[0] = 0, up[1] = 1, up[2] = 0;
	}
	glutPostRedisplay();
}
void light_menu(int option) {
	if (option == 1) {
		printf("태양 조명 ON\n");
		light_sun = true;
		light_earth = false;
		light_moon = false;
	}
	else if (option == 2) {
		printf("지구 조명 ON\n");
		light_sun = false;
		light_earth = true;
		light_moon = false;
	}
	else if (option == 3) {
		printf("달 조명 ON\n");
		light_sun = false;
		light_earth = false;
		light_moon = true;
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


	menu = glutCreateMenu(light_menu);
	glutAddMenuEntry("Sun", 1);
	glutAddMenuEntry("Earth", 2);
	glutAddMenuEntry("Moon", 3);

	/*Poup menu 생성 및 추가*/
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Spin", 2);
	glutAddMenuEntry("Init", 3);
	glutAddSubMenu("Light", menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	/* call back 함수 정의*/
	glutDisplayFunc(draw);					//draw() -> 실제 그리기 함수
	glutReshapeFunc(resize);				//resize 함수
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);		//방향키 입력
	glutMouseWheelFunc(mouseWheel);			//mouseWheel
	/*Looping 시작*/
	glutMainLoop();

	return 0;
}