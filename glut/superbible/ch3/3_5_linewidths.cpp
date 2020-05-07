/* Demonstrates line width demo by drawing lines of different sizes.
 * This is the fifth example in the 3rd chapter of opengl superbible
 * Sagar Gandhi | 07/05/2020
*/

#include <GL/glut.h>
#include <stdio.h>
GLfloat lineSizes[2];
GLfloat lineStep;

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glGetFloatv(GL_LINE_WIDTH_RANGE, lineSizes);
  glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &lineStep);
}

void RenderScene(void) {
  // linestep is too small. In my environment it is 0.0078; hence multiplying with 100
  GLfloat nDifferentWidths = (lineSizes[1]-lineSizes[0]) / (lineStep*100);
  GLfloat curWidth = lineSizes[0];
  GLfloat x = 90, y;
  int counter;
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  for (counter = 0, y = -90;
      counter < nDifferentWidths; 
	  curWidth += lineStep*100, y += curWidth/2, ++counter) {
	glLineWidth(curWidth);
    glBegin(GL_LINES);
      glVertex2f(-x, y);
      glVertex2f(x, y);
	glEnd();
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
  glutCreateWindow("line sizes");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}
