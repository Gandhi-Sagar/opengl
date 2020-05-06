/* Draws animation of square bouncing off the walls.
 * Code 2.3 in superbible 4th edition
 * Sagar Gandhi | 06/05/2020
*/

#include <GL/glut.h>

// initial square position and size
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;

// step size in x and y directions
// i.e. number of steps to move in each direction
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// keep track of width and height to accomodate change in size
GLfloat windowWidth;
GLfloat windowHeight;

// Callback function called by glut framework to draw a frame
void RenderScene(void) {
  // Clear the window with current clearing color
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Set the drawing color
  glColor3f(1.0f, 0.0f, 0.0f);
  
  // draw filled rectangle with current color
  glRectf(x1, y1, x1 + rsize, y1 - rsize);
  
  // flush drawing commands and swap buffers
  glutSwapBuffers();
}

// Callback function called by glut framework whenever window size changes
void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat aspectRatio;
  
  // prevent divide by zero
  if (h == 0)
	h = 1;

  // set the viewport to window dimensions
  glViewport(0, 0, w, h);
  
  // reset the coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // establish a clipping volume (left, right, bottom, top, near, far)
  aspectRatio = (GLfloat)w / (GLfloat)h;
  if (w <= h) {
	windowWidth = 100.0;
	windowHeight = 100.0 / aspectRatio;
	glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100 / aspectRatio, -1.0, 1.0);
  }
  else {
	windowWidth = 100.0 * aspectRatio;
	windowHeight = 100.0;
	glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, -1.0, 1.0);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Callback function called by glut framework when window is idle,
// every n milliseconds.
void TimerFunction(int value) {
  // reverse a direction when left or right edge is reached
  if (x1 > windowWidth-rsize || x1 < -windowWidth)
	xstep = -xstep;
  // reverse a direction when bottom or top edge is reached
  if (y1 > windowHeight || y1 < -windowHeight + rsize)
	ystep = -ystep;

  // actually move the square
  x1 += xstep;
  y1 += ystep;
  
  // need to check bounds when window is resized and made smaller while
  // rectangle is bouncing and the rectangle suddenly finds itself outside
  // of the new clipping volume.
  if (x1 > (windowWidth-rsize + xstep))
	x1 = windowWidth-rsize-1;
  else if (x1 < -(windowWidth + xstep))
	x1 = -windowWidth - 1;

  if (y1 > (windowHeight + ystep))
	y1 = windowHeight - 1;
  else if (y1 < -(windowHeight-rsize + ystep))
	y1 = -windowHeight + rsize - 1;


  // redraw the scene with new coordinates
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

// setup rendering state
void SetupRC(void) {
  glClearColor(0.125f, 0.5f, 0.625f, 1.0f);
}

// entry point
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Bouncing square");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 10);
  SetupRC();
  glutMainLoop();
  return 0;
}
