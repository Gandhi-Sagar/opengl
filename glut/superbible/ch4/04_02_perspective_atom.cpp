/* Demonstrates transformations in the perspective projection
 * This is second exercise in the fourth chapter of OpenGL Superbible, 4th ed
 * Sagar Gandhi | 14/05/2020
*/

#include <GL/glut.h>

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
}

void RenderScene(void) {
  static GLfloat fMoonRot = 0.0f;
  static GLfloat fEarthRot = 0.0f;
  
  // clear the window and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // save the matrix state and do the roatations
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  
  // translate the whole scene out and into
  glTranslatef(0.0f, 0.0f, -300.0f);
  
  // set the material color to yellow
  // sun
  glColor3ub(255, 255, 0);
  
  //// glDisable(GL_LIGHTING);
  glutSolidSphere(15.0f, 25, 25);
  //// glEnable(GL_LIGHTING);
  
  // position the light after we draw the sun
  //// glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  
  // rotate the coordinate system
  glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
  
  // draw the earth
  glColor3ub(0, 0, 255);
  glTranslatef(105.0f, 0.0f, 0.0f);
  glutSolidSphere(15.0f, 25, 25);
  
  //rotate from earth based coordinates and draw moon
  glColor3ub(200, 200, 200);
  glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
  glTranslatef(30.0f, 0.0f, 0.0f);
  fMoonRot += 5.0f;
  if (fMoonRot > 360.0f)
	fMoonRot = 0.0f;
  
  glutSolidSphere(6.0f, 15, 15);
  
  // restore the matrix state
  glPopMatrix();
  
  fEarthRot += 2.0f;
  if (fEarthRot > 360.0)
	fEarthRot = 0.0f;
  
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
  gluPerspective(45.0, w/h, 1.0, 425.0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Atom Perspective");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  
  return 0;
}