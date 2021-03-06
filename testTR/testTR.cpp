#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "imageloader.h"
#include "textureloader.h"

bool movement = false;
float xrot = 0.0f, yrot = 0.0f;
float xmov = 0.0f, ymov = 0.0f, zmov = 0.0f;
float sizes = 1.0f;

void LoadTexture() {
	Model file = Model("C:/Users/Alfriyanis/Desktop/Github/GRAFKOM_TR_H_672016125/GRAFKOM_TR_H_672016125/Woman1.tga");

	glEnable(GL_TEXTURE_2D);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, file.HasAlphaChannel() ? GL_RGBA : GL_RGB, file.GetWidth(), file.GetWidth(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, file.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
		sizes += 0.2f;
		break;
	case 'e':
	case 'E':
		sizes -= 0.2f;
		break;
	case 'a':
	case 'A':
		yrot -= 5.0f;
		break;
	case 'd':
	case 'D':
		yrot += 5.0f;
		break;
	case 's':
	case 'S':
		xrot += 5.0f;
		break;
	case 'w':
	case 'W':
		xrot -= 5.0f;
		break;
	case 'r':
	case 'R':
		if (movement) {
			movement = false;
			printf("Stop\n");
		}
		else {
			printf("Play\n");
			movement = true;
		}
		break;
	}

	glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y) {

	switch (key) {
	case 100:
		xmov -= 0.025f;
		break;
	case 101:
		ymov += 0.025f;
		break;
	case 102:
		xmov += 0.025f;
		break;
	case 103:
		ymov -= 0.025f;
		break;
	}

	glutPostRedisplay();
}

void timer(int) {
	glutTimerFunc(1000 / 30, timer, 0);

	if (movement)
		yrot -= 3.0f;
	else
		yrot = yrot;
	glutPostRedisplay();
}

void transform() {
	glRotatef(xrot, 1.0f, 0.0f, 0.0f); // Putar horizontal
	glRotatef(yrot, 0.0f, 1.0f, 0.0f); // Putar vertical
	glScalef(sizes, sizes, sizes); // Perskalaan
	glTranslatef(xmov, ymov, zmov); // Translasi
}

void display() {

	Nfg model;
	model.process();

	int NTriangle = model.totalNrIndices / 3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();

	LoadTexture();

	gluLookAt(0.0, 2.0, 8.0, 0.0, 1.5, 5.0, 0, 1, 0);

	transform();


	for (int i = 0; i < NTriangle; i++) {


		glBegin(GL_POLYGON);
		glTexCoord2f(model.myVertex[model.myPattern[i].pos.x].uv.x, model.myVertex[model.myPattern[i].pos.x].uv.y);
		glVertex3f(model.myVertex[model.myPattern[i].pos.x].pos.x, model.myVertex[model.myPattern[i].pos.x].pos.y, model.myVertex[model.myPattern[i].pos.x].pos.z);
		glTexCoord2f(model.myVertex[model.myPattern[i].pos.y].uv.x, model.myVertex[model.myPattern[i].pos.y].uv.y);
		glVertex3f(model.myVertex[model.myPattern[i].pos.y].pos.x, model.myVertex[model.myPattern[i].pos.y].pos.y, model.myVertex[model.myPattern[i].pos.y].pos.z);
		glTexCoord2f(model.myVertex[model.myPattern[i].pos.z].uv.x, model.myVertex[model.myPattern[i].pos.z].uv.y);
		glVertex3f(model.myVertex[model.myPattern[i].pos.z].pos.x, model.myVertex[model.myPattern[i].pos.z].pos.y, model.myVertex[model.myPattern[i].pos.z].pos.z);
		glEnd();



	}

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void ukuran(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w > h) {
		glViewport(0, 0, w, w);
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glScalef(-0.5, 0.5, -0.5);
	}
	else {
		glViewport(0, 0, w, h);
	}

	gluPerspective(20.0, w / h, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}

int main(int argc, char** argv) {

	Conf config;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(config.winWidth, config.winHeight);
	glutInitWindowPosition(config.winPosX, config.winPosY);
	glutCreateWindow("TR GRAFKOM");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(display);
	glutReshapeFunc(ukuran);

	myinit();
	glutMainLoop();

	return 0;
}