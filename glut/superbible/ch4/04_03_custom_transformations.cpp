/* Demonstrates custom transformations using glLoadMatrix.
 * Ideally, it should be studied first how to perform rotation, and write own
 * code for transformation. But, it is also important to finish the book.
 * I promise myself, that in next 3 months, I will know how to perform
 * transformations myself.
 * This is combination of 3rd and 4th exercise in the 4th chapter of opengl
 * superbible 4th edition.
 * Sagar Gandhi | 15/05/2020
*/

#include <GL/glut.h>

#include "../shared/math3d.h"

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
}

void RenderScene(void) {
  M3DMatrix44f transformationMatrix;        // storage for tranformation matrix
  static GLfloat yRot = 0.0f;
  yRot += 0.5f;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // build a rotation matrix
  m3dRotationMatrix44(transformationMatrix, m3dDegToRad(yRot),
                      0.0f, 1.0f, 0.0f);
  transformationMatrix[12] = 0.0f;
  transformationMatrix[13] = 0.0f;
  transformationMatrix[14] = -100.0f;
  
  glLoadMatrixf(transformationMatrix);
  glutWireTorus(2.0f, 8.0f, 40, 20);
  
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
  gluPerspective(45.0f, w/h, 1.0f, 425.0f);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Custom Transformations using math3d library");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}