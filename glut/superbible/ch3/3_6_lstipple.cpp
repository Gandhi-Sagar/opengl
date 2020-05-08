/* Demonstrates effect of factor in stippling the line.
 * This is a sixth exercise in the third chapter of the superbile 4th edition.
 * Sagar Gandhi | 08/05/2020
*/

#include <GL/glut.h>

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
}

void RenderScene(void) {
  GLfloat x = 80.0f, y;
  GLint factor = 1;
  GLushort pattern = 0x5555;
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  glEnable(GL_LINE_STIPPLE);
  for (y = -90.0f; y <= 90.0f; y += 10.0f) {
    glLineStipple(factor, pattern);
	glBegin(GL_LINES);
	  glVertex2f(-x, y);
	  glVertex2f(x, y);
	glEnd();
	factor++;
  }
  glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat nRange = 100.0f;
  
  if (h == 0)
    h = 1;
	
  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(w <= h)
    glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
  else
    glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void TimerFunction(int value) {
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("line stipple factor effect");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}