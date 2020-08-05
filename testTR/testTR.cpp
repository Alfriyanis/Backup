#include <iostream>
#include <windows.h>
#include <GL/freeglut.h>
#include "imageloader.h";
#include "textureloader.h";

void display();
bool mouseDown = false;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
double rotate_y = 0, rotate_x = 0, zoom = 0.5;
int is_depth, a;


void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << "KLIK KIRI" << " = anda menekan LEFT_BUTTON" << std::endl;
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
	display();
}

void mouseMotion(int x, int y) {
	if (mouseDown) {
		yrot = x - xdiff;
		xrot = y + ydiff;

		glLoadIdentity();
		gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); //mengatur penglihatan objek
		glRotatef(xrot, 1.0, 0.0, 0.0);
		glRotatef(yrot, 0.0, 1.0, 0.0);
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'g':
	case 'G':
		glTranslatef(0.0, 0.0, -3.0);
		break;
	case 'h':
	case 'H':
		glTranslatef(0.0, 0.0, 3.0);
		break;

	case 'w':                                   ////zoom in
	case 'W':
		glScalef(0.75, 0.75, 0.75);
		break;
	case 'd':                                   ////geser kanan
	case 'D':
		glTranslatef(3.0, 0.0, 0.0);
		break;
	case 's':                                   ///zoom out
	case 'S':
		glScalef(1.75, 1.75, 1.75);
		break;
	case 'a':                                   ////geser kiri
	case 'A':
		glTranslatef(-3.0, 0.0, 0.0);
		break;
	case'q':                                    ////gser atas
	case'Q':
		glTranslatef(0.0, 3.0, 0.0);
		break;
	case 'e':
	case 'E':
		glTranslatef(0.0, -3.0, 0.0);
		break;
	case 'x':                                   ///putar kanan ke kiri
	case 'X':
		glRotatef(2.0, 0.0, 0.0, 1.0);
		break;
	case 'z':                                   ///putar kiri ke kanan 
	case 'Z':
		glRotatef(-2.0, 0.0, 0.0, 1.0);
		break;
	}
	display();
}

void specialKeyboard(int key, int x, int y)
{
	switch (key) {
	case 100:
		glRotatef(-2.0, 0.0, 1.0, 0.0);
		break;
	case 101:
		glRotatef(-2.0, 1.0, 0.0, 0.0);
		break;
	case 102:
		glRotatef(2.0, 0.0, 1.0, 0.0);
		break;
	case 103:
		glRotatef(2.0, 1.0, 0.0, 0.0);
		break;
	}
	glutPostRedisplay();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	glColor3ub(10, 10, 10);
	for (int i = 0; i < (int)jumTampilan / 3; i++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(_pos[_list[i].u1].x, _pos[_list[i].u1].y, _pos[_list[i].u1].z);
		glVertex3f(_pos[_list[i].u2].x, _pos[_list[i].u2].y, _pos[_list[i].u2].z);
		glVertex3f(_pos[_list[i].u3].x, _pos[_list[i].u3].y, _pos[_list[i].u3].z);
		glEnd();
	}

	glPopMatrix();
	glutSwapBuffers();
}


void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
}


void ukuran(int lebar, int tinggi) {
	if (tinggi == 0)
		tinggi = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0, lebar / tinggi, 50.0, 500.0);
	glTranslatef(-5.0, -5.0, -150.0);
	glMatrixMode(GL_MODELVIEW);
}

void idle() {
	if (!mouseDown) {
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 20);
	glPointSize(10);
	glLineWidth(10);
	glutCreateWindow("Grafkom TR Dosen");
	Load("Woman1.nfg");
	init();
	is_depth = 1;
	glLoadIdentity();


	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutReshapeFunc(ukuran);
	

	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}