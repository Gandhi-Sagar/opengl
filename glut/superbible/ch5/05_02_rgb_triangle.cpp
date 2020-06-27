/* Demonstrates smoothly shaded colored triangle 
 * (This is usually called "hello, world" program in the arena of rendering
 * and is a second exercise in the 5th chapter of opengl superbible 4th ed.
 * Sagar Gandhi | 19/05/2020
 */
 
#include <GL/glut.h>

void SetupRC(void) {
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glFrontFace(GL_CCW);
  glPolygonMode(GL_FRONT, GL_FILL);
}

void RenderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, -2.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -2.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, -2.0f);
  glEnd();
  
  glutSwapBuffers();
}

void TimerFunction(int value) {
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
  if (h == 0)
    h = 1;

  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, w/h, 0.1f, 100.0f);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Shaded Triangle");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  
  return 0;
}