/* Demonstrates transformations by rendering crude animated model of an atom.
 * This is first exercise in the 4th chapter of opengl superbible 4th edition.
 * Sagar Gandhi | 12/05/2020
*/

#include <GL/glut.h>

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
}

void RenderScene(void) {
  // angle of revolution around the nucleus
  static GLfloat fElect1 = 0.0f;
  
  // clear the window with current clearing color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // reset the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // translate the whole scene out and into view
  // this is the initial viewing transformation
  glTranslatef(0.0f, 0.0f, -100.0f);
  
  // red nucleus
  
  glColor3ub(255, 0, 0);
  glutSolidSphere(10.0, 15, 15);
  
  // yellow electrons
  glColor3ub(255, 255, 0);
  
  // first electron orbit
  // save viewing transformations
  glPushMatrix();
  
  // rotate by angle of revolution
  glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
  
  // translate out from origin to orbit distance
  glTranslatef(90.0f, 0.0f, 0.0f);
  
  // draw the electron
  glutSolidSphere(6.0, 15, 15);
  
  // restore the viewing transformations
  glPopMatrix();
  
  // second electron orbit
  glPushMatrix();
  glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
  glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
  glTranslatef(-70.0f, 0.0f, 0.0f);
  glutSolidSphere(6.0, 15, 15);
  glPopMatrix();
  
  // third electron orbit
  glPushMatrix();
  glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
  glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 60.0f);
  glutSolidSphere(6.0, 15.0, 15.0);
  glPopMatrix();
  
  // increment the angle of revolution
  fElect1 += 10.0f;
  if (fElect1 > 360.0)
    fElect1 = 0.0f;

  // show the image
  glutSwapBuffers();
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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Atom transformations");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}