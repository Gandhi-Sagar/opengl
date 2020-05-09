/* Demonstrates how to draw concave polygons using triangles
 * and how to selectively choose which edges gets shown as a border.
 * This is a ninth exercise in the third chapter of the superbible 4th edition
 * Sagar Gandhi | 08/05/2020
*/

#include <GL/glut.h>

GLboolean bEdgeFlag;

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glPolygonMode(GL_FRONT, GL_LINE);
}

void ProcessMenu(int value) {
  switch(value) {
	case 1:
	  bEdgeFlag = !bEdgeFlag;
  }
  glutPostRedisplay();
}

void RenderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glBegin(GL_TRIANGLES);
    glEdgeFlag(bEdgeFlag);
	glVertex2f(-20.0f, 0.0f);
	glEdgeFlag(true);
	glVertex2f(20.0f, 0.0f);
	glVertex2f(0.0f, 40.0f);
	
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(-60.0f, -20.0f);
	glEdgeFlag(bEdgeFlag);
	glVertex2f(-20.0f, -40.0f);
	glEdgeFlag(true);
	
	glVertex2f(-20.0f, -40.0f);
	glVertex2f(0.0f, -80.0f);
	glEdgeFlag(bEdgeFlag);
	glVertex2f(20.0f, -40.0f);
	glEdgeFlag(true);
	
	glVertex2f(20.0f, -40.0f);
	glVertex2f(60.0f, -20.0f);
	glEdgeFlag(bEdgeFlag);
	glVertex2f(20.0f, 0.0f);
	glEdgeFlag(true);
	
	// center of the square as two triangles
	glEdgeFlag(bEdgeFlag);
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(-20.0f, -40.0f);
	glVertex2f(20.0f, 0.0f);
	
	glVertex2f(-20.0f, -40.0f);
	glVertex2f(20.0f, -40.0f);
	glVertex2f(20.0f, 0.0f);
	glEdgeFlag(true);
	
  glEnd();
  glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat nRange = 100.0f;
  
  if (h == 0)
    h = 1;
	
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
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("star");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("Toggle Edges", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  SetupRC();
  glutMainLoop();
  return 0;
}