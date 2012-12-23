

#include <GLTools.h>            // OpenGL toolkit

#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <glu.h>

#define FREEGLUT_STATIC
#include "glut.h"            // Windows FreeGlut equivalent



//------------------------------------------------------------------------------------------------------------

GLuint shader;
M3DMatrix44f mtxModelView;
GLint modelViewMtxLoc;
GLFrame cameraFrame;
GLFrustum viewFrustum;
M3DMatrix44f mtxCamera;
float fAngle;

void SetUpFrame(GLFrame &frame,
				const M3DVector3f origin,
				const M3DVector3f forward,
				const M3DVector3f up)
{
	frame.SetOrigin(origin);
	frame.SetForwardVector(forward);
	M3DVector3f side,oUp;
	m3dCrossProduct3(side,forward,up);
	m3dCrossProduct3(oUp,side,forward);
	frame.SetUpVector(oUp);
	frame.Normalize();
}

void LookAt(GLFrame &frame,
			const M3DVector3f eye,
			const M3DVector3f at,
			const M3DVector3f up)
{
	M3DVector3f forward;
	m3dSubtractVectors3(forward, at, eye);
	SetUpFrame(frame, eye, forward, up);
}

void ChangeSize(int w, int h) {
	glViewport(0, 0, w, h);
	viewFrustum.SetPerspective(60.0f,(float)w/h,0.1f,10.f);
}

void SetupRC() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	shader = gltLoadShaderPairWithAttributes("shaders\\shader.vp", "shaders\\shader.fp",
			2, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_COLOR, "vColor");
	fprintf(stdout, "GLT_ATTRIBUTE_VERTEX : %d\nGLT_ATTRIBUTE_COLOR : %d \n",
			GLT_ATTRIBUTE_VERTEX, GLT_ATTRIBUTE_COLOR);

	modelViewMtxLoc = glGetUniformLocation(shader, "MVMatrix");
	if(modelViewMtxLoc==-1)
	{
		fprintf(stderr,"uniform MVMatrix could not be found\n");
	}

	M3DVector3f forward = {-5.0f, -5.0f, -5.0f};
	M3DVector3f origin = {5.0f, 5.0f, 5.0f};
	M3DVector3f up = {0.0f, 0.0f, 1.0f};
 
	SetUpFrame(cameraFrame, origin, forward, up);

	fAngle = 0;

	glEnable(GL_DEPTH_TEST);
}


void makePyramid()
{
	glBegin(GL_QUADS);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.3, 0.3, 0.3);
		glVertex3f(-1.5f, -1.5f, 0.0f);
		glVertex3f( 1.5f, -1.5f, 0.0f);
		glVertex3f( 1.5f,  1.5f, 0.0f);
		glVertex3f(-1.5f,  1.5f, 0.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 1.0, 0.0, 0.0);
		glVertex3f(-1.5f, -1.5f, 0.0f);
		glVertex3f( 1.5f, -1.5f, 0.0f);
		glVertex3f( 0.0f,  0.0f, 1.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.0, 1.0, 0.0);
		glVertex3f(1.5f, -1.5f, 0.0f);
		glVertex3f(1.5f,  1.5f, 0.0f);
		glVertex3f(0.0f,  0.0f, 1.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 1.0, 1.0, 0.0);
		glVertex3f( 1.5f, 1.5f, 0.0f);
		glVertex3f(-1.5f, 1.5f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 1.0f);
    glEnd();

	glBegin(GL_TRIANGLES);
		glVertexAttrib3f(GLT_ATTRIBUTE_COLOR, 0.0, 0.0, 1.0);
		glVertex3f(-1.5f, 1.5f, 0.0f);
		glVertex3f(-1.5f,-1.5f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 1.0f);
    glEnd();
}

void RenderScene(void) {
	// Clear the window 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   
	glUseProgram(shader);

	float eye[3];
	float at[]={0,0,0},up[]={0,0,5};

	eye[0]=5.8f*cos(fAngle);
	eye[1]=4.8f*sin(fAngle);
	eye[2]=5.0f;

	fAngle+= -0.01;
	if(fAngle<1)
	{
		fAngle=360;
	}
	
	LookAt(cameraFrame,eye,at,up);

	cameraFrame.GetCameraMatrix(mtxCamera);

	M3DMatrix44f ViewProjectionMatrix;

	m3dMatrixMultiply44(ViewProjectionMatrix,viewFrustum.GetProjectionMatrix(),mtxCamera);
	
	glUniformMatrix4fv(modelViewMtxLoc,1,GL_FALSE,ViewProjectionMatrix);

	makePyramid();

	// Make buffer swap to display back buffer
	glutSwapBuffers();
}

void timerFunction(int param) {
	glutPostRedisplay();
    glutTimerFunc(16, timerFunction, 0);
}

int main(int argc, char* argv[]) {
  

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("proj2");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	glutTimerFunc(0, timerFunction, 0);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();

	glutMainLoop();
	return 0;
}
