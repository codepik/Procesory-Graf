#include "draw.h"

#include <GLTools.h>
#include <glu.h>
#define FREEGLUT_STATIC
#include "glut.h"

void drawPyramid()
{
	glBegin(GL_QUADS);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.3, 0.3, 0.3);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, 0.0f);
		glVertex3f( 1.0f,  1.0f, 0.0f);
		glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.0, 1.0, 0.0);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, 0.0f);
		glVertex3f( 0.0f,  0.0f, 2.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 1.0, 0.0, 0.0);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f,  1.0f, 0.0f);
		glVertex3f(0.0f,  0.0f, 2.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 1.0, 1.0, 0.0);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 2.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.0, 0.0, 1.0);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 2.0f);
    glEnd();
}

void drawSmallPyramid()
{
	glBegin(GL_QUADS);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.3, 0.3, 0.3);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f( 0.5f, -0.5f, 0.0f);
		glVertex3f( 0.5f,  0.5f, 0.0f);
		glVertex3f(-0.5f,  0.5f, 0.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.0, 1.0, 0.0);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f( 0.5f, -0.5f, 0.0f);
		glVertex3f( 0.0f,  0.0f, 1.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 1.0, 0.0, 0.0);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glVertex3f(0.5f,  0.5f, 0.0f);
		glVertex3f(0.0f,  0.0f, 1.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 1.0, 1.0, 0.0);
		glVertex3f( 0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 1.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.0, 0.0, 1.0);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f,-0.5f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 1.0f);
    glEnd();
}