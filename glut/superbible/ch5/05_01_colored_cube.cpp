/* Demonstrates the range of colors on a cube from 0-255, with step size of 1
 * This is a first exercise in the fifth chapter of superbible 4th edition
 * Sagar Gandhi | 16/05/2020
*/

#include <GL/glut.h>

GLfloat xRot = 0.0f, yRot = 0.0f, zTrv = -5.0f;

void SetupRC(void) {
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RenderScene(void) {
  GLfloat x, y, z;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glTranslatef(0.0f, 0.0f, zTrv);
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  
  x = 0.5f, y = 0.5f, z = 0.5f;
  glBegin(GL_QUADS);
    // front
    glColor3ub(255, 255, 255);
	glVertex3f(x, y, z);
	glColor3ub(255, 0, 255);
	glVertex3f(x, -y, z);
	glColor3ub(0, 0, 255);
	glVertex3f(-x, -y, z);
	glColor3ub(0, 255, 255);
	glVertex3f(-x, y, z);
	
	// back
	glColor3ub(255, 255, 0);
	glVertex3f(x, y, -z);
	glColor3ub(255, 0, 0);
	glVertex3f(x, -y, -z);
	glColor3ub(0, 0, 0);
	glVertex3f(-x, -y, -z);
	glColor3f(0, 255, 0);
	glVertex3f(-x, y, -z);
	
	// left
	glColor3ub(0, 255, 0);
	glVertex3f(-x, y, -z);
	glColor3ub(0, 0, 0);
	glVertex3f(-x, -y, -z);
	glColor3ub(0, 0, 255);
	glVertex3f(-x, -y, z);
	glColor3ub(0, 255, 255);
	glVertex3f(-x, y, z);
	
	// right
	glColor3ub(255, 255, 255);
	glVertex3f(x, y, z);
	glColor3ub(255, 0, 255);
	glVertex3f(x, -y, z);
	glColor3ub(255, 0, 0);
	glVertex3f(x, -y, -z);
	glColor3ub(255, 255, 0);
	glVertex3f(x, y, -z);
	
	// top
	glColor3ub(255, 255, 255);
	glVertex3f(x, y, z);
	glColor3ub(0, 255, 255);
	glVertex3f(-x, y, z);
	glColor3ub(0, 255, 0);
	glVertex3f(-x, y, -z);
	glColor3ub(255, 255, 0);
	glVertex3f(x, y, -z);
	
	// bottom
	glColor3ub(255, 0, 255);
	glVertex3f(x, -y, z);
	glColor3ub(0, 0, 255);
	glVertex3f(-x, -y, z);
	glColor3ub(0, 0, 0);
	glVertex3f(-x, -y, -z);
	glColor3ub(255, 0, 0);
	glVertex3f(x, -y, -z);
  glEnd();
    
  glutSwapBuffers();
  
  xRot += 0.2f;
  yRot += 0.3f;
  if (xRot > 360.0f)
	xRot = 0.0f;
  if (yRot > 360.0f)
	yRot = 0.0f;
}

void TimerFunction(int value) {
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

void SpecialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
	zTrv += 0.1f;
	if (zTrv > 2.0)
	  zTrv = 2.0f;
  }

  if (key == GLUT_KEY_DOWN) {
	zTrv -= 1.0f;
	if (zTrv < -100.0f)
	  zTrv = -100.0f;
  }
  
  if (key == GLUT_KEY_LEFT) {
	yRot -= 1.0f;
	if (yRot < 0.0f)
	  yRot = 360.0f;
  }
  
  if (key == GLUT_KEY_RIGHT) {
	yRot += 1.0f;
	if (yRot > 360.0f)
	  yRot = 0.0f;
  }
  glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h) {
  if (h == 0)
    h = 1;
	
  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(35.0f, w/h, 1.0f, 400.0f);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Color Cube");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  glutSpecialFunc(SpecialKeys);
  SetupRC();
  glutMainLoop();
  
  return(0);
}