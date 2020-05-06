/* Blank window using glut
 * Code 2.1 in the Superbible 4th edition
 * Sagar Gandhi | 05/05/2020
*/

#include <GL/glut.h>

// Called to draw scene
void RenderScene(void) {
  // clear the window with the current clearing color
  glClear(GL_COLOR_BUFFER_BIT);
  
  // flush drawing commands
  glFlush();
}

// Setup rendering state
void SetupRC(void) {
  glClearColor(0.98f, 0.625f, 0.12f, 1.0f);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow("BlankWindow");
  glutDisplayFunc(RenderScene);
  
  SetupRC();
  glutMainLoop();
  
  return 0;
}