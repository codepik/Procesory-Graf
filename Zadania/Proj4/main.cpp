#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>

#include "imageloader.h"

using namespace std;

// współczynnik skalowania
GLfloat scale = 0.5;

// kąty obrotu piramidy
GLfloat rotatex = -30.0;
GLfloat rotatey = 0.0;

//tekstura
GLuint texture;

GLuint getTexture(Image *image) {
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	//Mapujemy obraz na teksture
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		image->width, image->height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image->pixels
	);

	return texture;
}

//Ustawia renderowanie sceny
void initRendering() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	//Wlaczamy oswietlenie
	glEnable(GL_LIGHTING);

	//Wlaczamy dwa zrodla swiatla
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_NORMALIZE);

	Image* image = loadBMP("assets/brick.bmp");
	texture = getTexture(image);
	delete image;
}

//Obsluga zmiany rozmiaru okna
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);

	//Przechodzimy do ustawiania kamery
	glMatrixMode(GL_PROJECTION);

	//Ustawienie kamery
	glLoadIdentity();
	gluPerspective(
		0.0, 					
		(double)w / (double)h,		
		1.0,							
		200.0
	);					
}

//Rysowanie sceny
void drawScene() {
	//Czyszczenie sceny
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, -0.4f, 0.0f);

	//Dodajemy swiatlo
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Dodajemy swiatlo pozycyjne
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos0[] = {0.0f, 0.0f, 2.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Dodajemy swiatlo kierunkowe
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};
	GLfloat lightPos1[] = {-2.0f, 0.0f, 0.5f, 2.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	//Wlaczamay teksturowanie
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	glScalef(scale, scale, scale);

	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	glBegin(GL_QUADS);
		glVertex3f(-1.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, -1.0);
		glVertex3f(-1.0, 0.0, -1.0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0, 0.0, 1.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0, 0.0, 1.0);
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0, 0.0, 1.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0, 0.0, -1.0);
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0, 0.0, -1.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0, 0.0, -1.0);
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0, 0.0, -1.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0, 0.0, 1.0);
		glTexCoord2f(0.5f, 1.0f);
		glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	//Wyswietlenie sceny na ekranie
	glutSwapBuffers();
}

void update(int value) {
	rotatey -= 0.5;

	if (rotatey <= -360) {
		rotatey = 0;
	}

	//Wyswietl ponownie scene
	glutPostRedisplay();

	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Uruchamiamy GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 400); //Wielkosc okna

	//Tworzymy okno
	glutCreateWindow("PPG - Piramida - Projekt zaliczeniowy");
	initRendering();

	//Podlaczamy handlery
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}
