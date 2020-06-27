/* Demonstrates "jet" with only colors. Later on, lights will be added to
 * make it look fancy.
 * This is a third exercise in the fifth chapter of superbible 4th edition
 * Sagar Gandhi | 19/05/2020
*/

#include <GL/glut.h>

GLfloat xRot = 20.0f, yRot = 30.0f, xRotStep = 2.0f, yRotStep = 3.0f;
GLfloat zTrlt = -5.0f, zTrltStep = 0.2f;

void SetupRC(void) {
  glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glPolygonMode(GL_FRONT, GL_LINES);
  glPolygonMode(GL_BACK, GL_LINES);
  glFrontFace(GL_CCW);
}

void RenderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, zTrlt);
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  glBegin(GL_TRIANGLES);
  //nose
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.6f);
	glVertex3f(-0.15f, 0.0f, 0.3f);
	glVertex3f(0.15f, 0.0f, 0.3f);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.15f, 0.0f, 0.3f);
	glVertex3f(0.0f, 0.15f, 0.3f);
	glVertex3f(0.0f, 0.0f, 0.6f);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.6f);
	glVertex3f(0.0f, 0.15f, 0.3f);
	glVertex3f(-0.15f, 0.0f, 0.3f);
	
	// body
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.15f, 0.0f, 0.3f);
	glVertex3f(0.0f, 0.15f, 0.3f);
	glVertex3f(0.0f, 0.0f, -0.56f);
	
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -0.56f);
	glVertex3f(0.0f, 0.15f, 0.3f);
	glVertex3f(0.15f, 0.0f, 0.3f);
	
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.15f, 0.0f, 0.3f);
	glVertex3f(-0.15f, 0.0f, 0.3f);
	glVertex3f(0.0f, 0.0f, -0.56f);
	
	// left wing
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.0f, 0.02f, 0.27f);
	glVertex3f(0.6f, 0.02f, -0.08f);
	glVertex3f(-0.6f, 0.02f, -0.08f);
	
 	glColor3f(0.25f, 0.25f, 0.25f);
	glVertex3f(0.6f, 0.02f, -0.08f);
	glVertex3f(0.0f, 0.07f, -0.08f);
	glVertex3f(0.0f, 0.02f, 0.27f);
	
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex3f(0.6f, 0.02f, -0.08f);
	glVertex3f(0.0f, 0.07f, -0.08f);
	glVertex3f(0.0f, 0.02f, -0.08f);
	
	// right wing top
	glColor3f(0.25f, 0.25f, 0.25f);
	glVertex3f(0.0f, 0.02f, 0.27f);
	glVertex3f(0.0f, 0.07f, -0.08f);
	glVertex3f(-0.6f, 0.02f, -0.08f);
	
	// right wing bottom
	glColor3f(0.25f, 0.25f, 0.25f);
	glVertex3f(-0.6f, 0.02f, -0.08f);
	glVertex3f(0.0f, 0.02f, -0.08f);
	glVertex3f(0.0f, 0.07f, -0.08f);
	
	// bottom
	glColor3f(1.0f, 0.5f, 1.0f);
	glVertex3f(-0.3f, -0.005f, -0.57f);
	glVertex3f(0.3f, -0.005f, -0.57f);
	glVertex3f(0.0f, -0.005f, -0.4f);
	
	// bottom left
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, -0.005f, -0.4f);
	glVertex3f(0.3f, -0.005f, -0.57f);
	glVertex3f(0.0f, 0.04f, -0.57f);
	
	// bottom right
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, 0.04f, -0.57f);
	glVertex3f(-0.3f, -0.005f, -0.57f);
	glVertex3f(0.0f, -0.005f, -0.4f);
	
	// bottom back
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.3f, -0.005f, -0.57f);
	glVertex3f(-0.3f, -0.005f, -0.57f);
	glVertex3f(0.0f, 0.04f, -0.57f);
	
	// top of the tail
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.005f, -0.4f);
	glVertex3f(0.03f, 0.005f, -0.57f);
	glVertex3f(0.0f, 0.25f, -0.65f);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.25f, -0.65f);
	glVertex3f(-0.03f, 0.005f, -0.57f);
	glVertex3f(0.0f, 0.005f, -0.4f);
	
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.03f, 0.005f, -0.57f);
	glVertex3f(-0.03f, 0.005f, -0.57f);
	glVertex3f(0.0f, 0.25f, -0.65f);
	
  glEnd();
  glPopMatrix();
  glutSwapBuffers();
}

void TimerFunction(int value) {
  xRot += xRotStep;
  yRot += yRotStep;
  
  if (xRot >= 360.0f)
    xRot = 0.0f;
  if (yRot >= 360.0f)
    yRot = 0.0f;
  
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

void SpecialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_UP)
    zTrlt += zTrltStep;
	
  if (key == GLUT_KEY_DOWN)
    zTrlt -= zTrltStep;

  if (key == GLUT_KEY_LEFT)
    if (xRotStep == 0.0f)
	  xRotStep = 2.0f;
    else
	  xRotStep = 0.0f;
  
  if (key == GLUT_KEY_RIGHT)
	if (yRotStep == 0.0f)
	  yRotStep = 3.0f;
    else
	  yRotStep = 0.0f;
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
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Jet without lights");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}