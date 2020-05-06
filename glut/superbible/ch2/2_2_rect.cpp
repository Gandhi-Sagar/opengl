/* Draw rectangle using glut
 * Code 2.2 in superbible 4th edition
 * Sagar Gandhi | 05/05/2020
*/

#include <GL/glut.h>

// called to draw the scene
void RenderScene(void) {
  // clear the window with current clearing window
  glClear(GL_COLOR_BUFFER_BIT);
  
  // set current drawing color
  //        R     G     B
  glColor3f(1.0f, 0.0f, 0.0f);
  
  // draw filled rectangle with current color
  glRectf(-25.f, 25.f, 25.f, -25.f);
  
  // flush drawing commands
  glFlush();
}

// setup the rendering state
void SetupRC(void) {
  // set clear color to blue
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// called by glut library when window's size has changed
void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat aspectRatio;
  
  // prevent divide-by zero
  if (h == 0)
    h = 1;
  
  // set viewport to display dimention
  glViewport(w/3, h/3, w/2, h/2);
  
  // reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // establish clipping volume (left, right, bottom, top, near, far)
  aspectRatio = (GLfloat)w / (GLfloat)h;
  if (w <= h)
    glOrtho(-100.0, 100.0, -100.0/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);
  else
	glOrtho(-100.0 * aspectRatio, 100 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Rectangle");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  
  SetupRC();
  glutMainLoop();
  
  return 0;
}