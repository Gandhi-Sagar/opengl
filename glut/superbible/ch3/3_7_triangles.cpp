/* Demonstrates how to draw solid polygons by drawing cones.
 * This is the seventh example in the 3rd chapter of the superbible 4th edition
 * Saga Gandhi | 08/05/2020
*/

#include <GL/glut.h>
#include <math.h>

# define GL_PI 3.1415

GLfloat xRot = 0.0f, yRot = 0.0f, xRotStep = 2.0f, yRotStep = 3.0f;
GLboolean bCull, bDepth, bOutline;

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  
  // set the color shading model to flat
  glShadeModel(GL_FLAT);
  
  // Clockwise-wound polygons are front facing; this is reversed because we
  // are using traingle fans
  glFrontFace(GL_CW);
}

void ProcessMenu(int value) {
  switch(value) {
	case 1:
	  bDepth = !bDepth;
	  break;
	case 2:
	  bCull = !bCull;
	  break;
	case 3:
	  bOutline = !bOutline;
	  break;
  }
  glutPostRedisplay();
}

void RenderScene(void) {
  GLfloat x, y, angle;
  int iPivot = 1; // used to flag alternative colors
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // turn culling on if flag is set
  if (bCull)
	glEnable(GL_CULL_FACE);
  else
	glDisable(GL_CULL_FACE);

  // enable depth testing if flag is set
  if (bDepth)
	glEnable(GL_DEPTH_TEST);
  else
	glDisable(GL_DEPTH_TEST);

  // draw the backside as wireframe only, if flat is set
  if (bOutline)
	glPolygonMode(GL_BACK, GL_LINE);
  else
    glPolygonMode(GL_BACK, GL_FILL);
  
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  
  glBegin(GL_TRIANGLE_FAN);
    // pinnacle of the cone is a shared vertex for a fan, move up the z axis
	// to produce a cone instead of cone
	glVertex3f(0.0f, 0.0f, 75.0f);
	
	// Loop around in a circle and specify even points along the circle as
	// the vertices of the triangle fan
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) {
	  //calculate x and y coordinates of the next vertex
	  x = 50.0f * sin(angle);
	  y = 50.0f * cos(angle);
	  
	  // alternate the color between red and green
	  if ((iPivot % 2) == 0)
		glColor3f(0.0f, 1.0f, 0.0f);
	  else
		glColor3f(1.0f, 0.0f, 0.0f);
	  // increment the pivot to change the color next time
	  iPivot++;
	  
	  // specify next vertex for the triangle fan
	  glVertex2f(x, y);
	}
  glEnd();
  
  // begin new triangle fan to cover the base
  glBegin(GL_TRIANGLE_FAN);
    // center of the fan is at the origin
	glVertex2f(0.0f, 0.0f);
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) {
	  // calculate x and y position of the next vertex
	  x = 50.0f * sin(angle);
	  y = 50.0f * cos(angle);
	  
	  // alternate color between red and green
	  if ((iPivot % 2) == 0)
		glColor3f(1.0f, 0.0f, 0.0f);
	  else
		glColor3f(0.0f, 1.0f, 0.0f);
	
	  // increment the pivot to change the color next time
	  iPivot++;
	  
	  glVertex2f(x, y);
	}
  glEnd();
  
  glPopMatrix();
  glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat nRange = 100;
  
  if (h ==0)
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
  xRot += xRotStep;
  yRot += yRotStep;
  
  if (xRot > 359.0f)
    xRot = 0.0f;
  if (yRot > 359.0f)
    yRot = 0.0f;
	
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Triangle Fans");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  // create the menu
  glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("Toggle depth test", 1);
  glutAddMenuEntry("Toggle backface culling", 2);
  glutAddMenuEntry("Toggle outline", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  
  SetupRC();
  glutMainLoop();
  return 0;
}