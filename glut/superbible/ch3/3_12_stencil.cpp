/* Demonstrates how to use a stencil buffer. This is another buffer similar
 * to color and depth, and generally acts as a "rangolicha chaap" (marathi).
 * This is 12th excercise in the 3rd chapter of the superbible, 4th edition
 * Sagar Gandhi | 09/05/2020
*/

#include <GL/glut.h>
#include <math.h>

GLfloat x = 0.0f, y = 0.0f, rsize = 25;
GLfloat xstep = 1.0f, ystep = 1.0f;
GLfloat windowWidth, windowHeight;

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
}

void RenderScene(void) {
  GLdouble dRadius = 0.1; // initial redius of the spiral
  GLdouble dAngle;        // looping variable
  
  // clear blue window
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  
  // use zero for clear stencil and enable stencil test
  glClearStencil(0.0f);
  glEnable(GL_STENCIL_TEST);
  
  // clear the color and stencil buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
  // all drawing commands fail the stencil buffer, and are not drawn,
  // but increment the value in the stencil buffer
  glStencilFunc(GL_NEVER, 0x0, 0x10);
  glStencilOp(GL_INCR, GL_INCR, GL_INCR);
  
  // spiral pattern will creat stencil pattern
  // draw the spiral pattern with white lines. We make the lines white
  // to demonstrate that the stencil function prevents them from being drawn
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINE_STRIP);
    for (dAngle = 0.0; dAngle < 400.0; dAngle += 0.1) {
	  glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
	  dRadius *= 1.002;
	}
  glEnd();
  
  // now, allow drawing, except where stencil pattern is 0x1
  // and do not make any further changes to the stencil buffer
  glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  
  // now, draw the red bouncing square
  // x and y are being modified by the timer function
  glColor3f(1.0f, 0.0f, 0.0f);
  glRectf(x, y, x+rsize, y-rsize);
  
  // all done, swap the buffers
  glutSwapBuffers();
}

void TimerFunction(int value) {
  // reverse the direction when left or right edge is reached
  if (x > windowWidth-rsize || x < -windowWidth)
	xstep = -xstep;
  // reverse the direction when bottom or top is reached
  if (y > windowHeight || y < -windowHeight+rsize)
	ystep = -ystep;

  // actually move the square
  x += xstep;
  y += ystep;
  
  // need to check the bounds when window is resized and made smaller
  // while rectangle is bouncing and rectangle suddenly is out of the
  // clipping volume
  if (x > (windowWidth-rsize + xstep))
	x = windowWidth - rsize - 1;
  else if (x < -(windowWidth + xstep))
	x = -windowWidth - 1;

  if (y > (windowHeight + ystep))
	y = windowHeight - 1;
  else if (y < -(windowHeight-rsize + ystep))
	y = -windowHeight + rsize - 1;
	
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
  if (w <= h) {
	windowWidth = nRange;
	windowHeight = nRange*h/w;
	glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
  }
  else {
	windowWidth = nRange*w/h;
	windowHeight = nRange;
	glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_STENCIL);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Stencil buffer demo");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}