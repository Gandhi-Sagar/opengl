/* Program draws points in 3d while changing the size of the points.
 * This is second code in the 3rd chapter of the 4th edition of the superbible.
 * Sagar Gandhi | 07/05/2020
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define GL_PI 3.1415

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat xRotStep = 2.0f;
GLfloat yRotStep = 3.0f;

GLfloat pointSizes[2];
GLfloat pointStep;

void RenderScene(void) {
  GLfloat angle, x, y, z;
  GLfloat ptsz = pointSizes[0];
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  
  z = -100.0f;
  for (angle = 0.0f; angle <= (2.0f*GL_PI)*3; angle += 0.1f) {
    x = 50.0f * sin(angle);
	y = 50.0f * cos(angle);
	glPointSize(ptsz);
	glBegin(GL_POINTS);
	  glVertex3f(x, y, z);
	glEnd();
	
	z += 1.0f;
	ptsz += pointStep;
  }
  glPopMatrix();
  glutSwapBuffers();
}


// initialize opengl state
void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background
  glColor3f(0.0f, 1.0f, 0.0f);
  
  glGetFloatv(GL_POINT_SIZE_RANGE, pointSizes);
  glGetFloatv(GL_POINT_SIZE_GRANULARITY, &pointStep);
}

void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat nRange = 100.0f;
  if (h == 0)
	h = 1;

  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
	glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
  else
	glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void TimerFunction(int value) {
  xRot += xRotStep;
  yRot += yRotStep;
  
  if (xRot > 359.0f)
	xRot = 0.0f;
  if (yRot > 359.0f)
	yRot = 0.0f;

  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

// entrypoint
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Points with size changes");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}