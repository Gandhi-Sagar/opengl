/* Draws points in 3d space.
 * This is the first code in chapter 3 of superbible 4th edition
 * Sagar Gandhi | 06/05/2020
*/

#include <GL/glut.h>
#include <math.h>
// define constant for value of PI
#define GL_PI 3.1415f

// vars for rotation around x and y axis
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat xRotStep = 2.0f;
GLfloat yRotStep = 3.0f;	

// thid function does any needed initialization on the rendering context
void SetupRC(void) {
  // set background color
  glClearColor(0.f, 0.f, 0.f, 1.0f);
 
  // set drawing color to screen
  glColor3f(0.f, 1.f, 0.f);
}

void RenderScene(void) {
  GLfloat x, y, z, angle;    // stored for coordinates and angles
  
  // clear the window with the current color
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Save the matrix state and do the rotation
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  
  // call only once for rendering all remaining points
  glBegin(GL_POINTS);
    z = -50.0f;
	
	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3; angle += 0.1) {
	  x = 50.f*sin(angle);
	  y = 50.f*cos(angle);
	  
	  // specify a point and move the z-value up a little
	  glVertex3f(x, y, z);
	  z += 0.5f;
	}
	
  // done drawing the points
  glEnd();
  
  // restore transformations
  glPopMatrix();
  
  // Flush drawing commands
  glutSwapBuffers();
}

// callback function called every n milliseconds, by glut framework when
// window is idle
void TimerFunction(int value) {  
  xRot += xRotStep;
  yRot += yRotStep;
  
  if (xRot > 359)
    xRot = 0.0f;
  if (yRot > 359)
	yRot = 0.0f;

  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

// callback function called by a glut framework whenever window is resized
void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat nrange = 100.0f;
  
  // prevent divide-by zero
  if (h == 0)
	h = 1;

  // set viewport to window dimension
  glViewport(0, 0, w, h);
  
  // Reset the projection matrix stack
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // establish a clipping volume (left, right, bottom, top, near, far)
  if (w <= h)
	glOrtho(-nrange, nrange, -nrange*h/w, nrange*h/w, -nrange, nrange);
  else
	glOrtho(-nrange*w/h, nrange*w/h, -nrange, nrange, -nrange, nrange);

  // reset model view matrix stack
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Points");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  
  return 0;
}