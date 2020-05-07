/* Draws line strips to approximate curves using GL_LINE_STRIPES
 * This is fourth example in the 3rd chapter of superbible 4th edition.
 * Sagar Gandhi | 07/05/2020
*/

#include <GL/glut.h>
#include <math.h>

#define GL_PI 3.1415

GLfloat xRot = 0.0, yRot = 0.0, xRotStep = 2.0, yRotStep = 3.0;

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
}

void RenderScene(void) {
  GLfloat x, y, z, angle;
  
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  
  glBegin(GL_LINE_STRIP);
    z = -50.0f;
    for (angle = 0.0f; angle <= (GL_PI * 2.0f)*3.0f; angle += 0.1f) {
	  x = 50.0f * sin(angle);
	  y = 50.0f * cos(angle);
	  glVertex3f(x, y, z);
	  
	  z += 0.5f;
	}
  glEnd();
  glPopMatrix();
  
  glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat nRange = 100.0f;
  
  if (h == 0)
	h = 1;

  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  if (w <= h)
	glOrtho(-nRange, nRange, -nRange*h/w, -nRange*h/w, -nRange, nRange);
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

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("line strip");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}