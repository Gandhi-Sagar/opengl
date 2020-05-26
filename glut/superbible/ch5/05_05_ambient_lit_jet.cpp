/* Demonstrates use of Ambient light and material. Material is shown using 
 * one of the two, and preffered ways
 * First way: 
 *   1. in SetupRC(): glLightModelfv(light_model, RGBA vector)
 *   2. in RenderScene(): glMaterialfv(front/back,diffuse_and/or_ambient,RGBA)
 * Second way is in the code.
 * This is the fifth exercise in the 5th chapter of superbible 4th edition
 * Sagar Gandhi | 21/05/2020
*/

#include <GL/glut.h>

GLfloat xRot = 0.0f, yRot = 0.0f, xRotStep = 2.0f, yRotStep = 3.0f;
GLfloat zTrans = -5.0f, zTransStep = 0.1f;

void SetupRC(void) {
  GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};

  glFrontFace(GL_CCW);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINES);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  
  glLightModelfv(GL_LIGHT_MODEL_COLOR_CONTROL, ambientLight);
  glEnable(GL_COLOR_MATERIAL);
  
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  
  glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void RenderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
    glTranslatef(0.0f, 0.0f, zTrans);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    glBegin(GL_TRIANGLES);
      //nose
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 0.6f);
      glVertex3f(-0.15f, 0.0f, 0.3f);
      glVertex3f(0.15f, 0.0f, 0.3f);
      
      glVertex3f(0.15f, 0.0f, 0.3f);
      glVertex3f(0.0f, 0.15f, 0.3f);
      glVertex3f(0.0f, 0.0f, 0.6f);
      
      glVertex3f(0.0f, 0.0f, 0.6f);
      glVertex3f(0.0f, 0.15f, 0.3f);
      glVertex3f(-0.15f, 0.0f, 0.3f);
      
      // body
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(-0.15f, 0.0f, 0.3f);
      glVertex3f(0.0f, 0.15f, 0.3f);
      glVertex3f(0.0f, 0.0f, -0.56f);
      
      glVertex3f(0.0f, 0.0f, -0.56f);
      glVertex3f(0.0f, 0.15f, 0.3f);
      glVertex3f(0.15f, 0.0f, 0.3f);
      
      glVertex3f(0.15f, 0.0f, 0.3f);
      glVertex3f(-0.15f, 0.0f, 0.3f);
      glVertex3f(0.0f, 0.0f, -0.56f);
      
      // left wing
      glColor3f(0.5f, 0.5f, 0.5f);
      glVertex3f(0.0f, 0.02f, 0.27f);
      glVertex3f(0.6f, 0.02f, -0.08f);
      glVertex3f(-0.6f, 0.02f, -0.08f);
      
      glVertex3f(0.6f, 0.02f, -0.08f);
      glVertex3f(0.0f, 0.07f, -0.08f);
      glVertex3f(0.0f, 0.02f, 0.27f);
      
      glVertex3f(0.6f, 0.02f, -0.08f);
      glVertex3f(0.0f, 0.02f, -0.08f);
      glVertex3f(0.0f, 0.07f, -0.08f);
      
      // right wing top
      glVertex3f(0.0f, 0.02f, 0.27f);
      glVertex3f(0.0f, 0.07f, -0.08f);
      glVertex3f(-0.6f, 0.02f, -0.08f);
      
      // right wing bottom
      glVertex3f(0.0f, 0.07f, -0.08f);
      glVertex3f(0.0f, 0.02f, -0.08f);
      glVertex3f(-0.6f, 0.02f, -0.08f);
      
      // bottom
      glColor3f(1.0f, 0.5f, 1.0f);
      glVertex3f(-0.3f, -0.005f, -0.57f);
      glVertex3f(0.3f, -0.005f, -0.57f);
      glVertex3f(0.0f, -0.005f, -0.4f);
      
      // bottom left
      glVertex3f(0.0f, -0.005f, -0.4f);
      glVertex3f(0.3f, -0.005f, -0.57f);
      glVertex3f(0.0f, 0.04f, -0.57f);
      
      // bottom right
      glVertex3f(0.0f, 0.04f, -0.57f);
      glVertex3f(-0.3f, -0.005f, -0.57f);
      glVertex3f(0.0f, -0.005f, -0.4f);
      
      // bottom back
      glVertex3f(0.3f, -0.005f, -0.57f);
      glVertex3f(-0.3f, -0.005f, -0.57f);
      glVertex3f(0.0f, 0.04f, -0.57f);
      
      // top of the tail
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 0.005f, -0.4f);
      glVertex3f(0.03f, 0.005f, -0.57f);
      glVertex3f(0.0f, 0.25f, -0.65f);
      
      glVertex3f(0.0f, 0.25f, -0.65f);
      glVertex3f(-0.03f, 0.005f, -0.57f);
      glVertex3f(0.0f, 0.005f, -0.4f);
      
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
    zTrans += zTransStep;
	
  if (key == GLUT_KEY_DOWN)
    zTrans -= zTransStep;
	
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
  glutCreateWindow("Ambient-lit Jet");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  return 0;
}
