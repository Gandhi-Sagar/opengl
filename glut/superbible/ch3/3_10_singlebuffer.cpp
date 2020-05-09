/* Demonstrates one of the ways of using rendering directly to front buffer.
 * The other way to achieve the same is to call glDrawBuffer(GL_FRONT).
 * This is the tenth exercise in the 3rd chapter of the suprbible 4th edition.
 * Sagar Gandhi | 09/05/2020
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glPointSize(2.0f);
}

void RenderScene(void) {
  static GLfloat radius = 1.1f;
  static GLfloat angle = 0.0f;
  if (angle == 0.0)
    glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
    glVertex2f(radius*cos(angle), radius*sin(angle));
  glEnd();
  
  radius *= 1.008;
  angle += 0.1;
  
  if (angle >= 60.0f) {
	radius = 1.1f;
	angle = 0.0f;
  }
  
  glFlush();
}

void TimerFunction(int value) {
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
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

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Single buffer");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}
