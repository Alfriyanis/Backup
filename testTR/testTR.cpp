#include <iostream>
#include <windows.h>
#include <GL/freeglut.h>
#include "imageloader.h";
#include "textureloader.h";
#define WIREFRAME 0

using namespace std;

void display();
bool mouseDown = false;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
double rotate_y = 0, rotate_x = 0, zoom = 0.5;
int is_depth;
float angle = 0.1f;

void imageloader() {
	//Tga info = Tga("C:/Users/Alfriyanis/source/repos/BackupTRDosen/BackupTRDosen/Woman1.tga");
	Tga info = Tga("Woman1.tga");

	glEnable(GL_TEXTURE_2D);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, info.HasAlphaChannel() ? GL_RGBA : GL_RGB, info.GetWidth(), info.GetWidth(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, info.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

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
	case 'w':                                   ////zoom in
	case 'W':
		glScalef(0.75, 0.75, 0.75);
		break;
	case 'd':                                   ////geser kanan
	case 'D':
		glTranslatef(0.05, 0.0, 0.0);
		break;
	case 's':                                   ///zoom out
	case 'S':
		glScalef(1.75, 1.75, 1.75);
		break;
	case 'a':                                   ////geser kiri
	case 'A':
		glTranslatef(-0.05, 0.0, 0.0);
		break;
	case'q':                                    ////gser atas
	case'Q':
		glTranslatef(0.0, -0.05, 0.0);
		break;
	case 'e':
	case 'E':
		glTranslatef(0.0, 0.05, 0.0);
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
	glTranslatef(0.0f, -.8f, 0.0f);
	glColor3ub(10, 10, 10);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	imageloader();
	for (int i = 0; i < (int)jumTampilan / 3; i++)
	{
		glBegin(GL_LINE_LOOP);
		glTexCoord2f(_uv[_list[i].u1].u, _uv[_list[i].u1].v);
		glVertex3f(_pos[_list[i].u1].x, _pos[_list[i].u1].y, _pos[_list[i].u1].z);
		glTexCoord2f(_uv[_list[i].u2].u, _uv[_list[i].u2].v);
		glVertex3f(_pos[_list[i].u2].x, _pos[_list[i].u2].y, _pos[_list[i].u2].z);
		glTexCoord2f(_uv[_list[i].u3].u, _uv[_list[i].u3].v);
		glVertex3f(_pos[_list[i].u3].x, _pos[_list[i].u3].y, _pos[_list[i].u3].z);
		glEnd();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 0);
	angle += 1.0f;
}

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
}

void Init() {
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();
	gluLookAt(0.2, 0.4, 5.0,
		3, 3, 3,
		4.5, 4.5, 100);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	is_depth = 1;
	glMatrixMode(GL_MODELVIEW);
}


void ukuran(int lebar, int tinggi) {
	if (tinggi == 0)
		tinggi = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, (float)lebar / tinggi, .1f, 100);
	glTranslated(0.0, -0.0, -7.2);
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
	glutTimerFunc(0, timer, 0);

	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}