/* Demonstrates many concepts in the moving world such as actor, camera,
 * their transformations, etc.
 * This is 5th exercise in the 4th chapter of opengl superbible 4th edition
 * Sagar Gandhi | 15/05/2020
*/

#include <GL/glut.h>

#include "../shared/glframe.h"

#define NUM_SPHERES 50
GLFrame spheres[NUM_SPHERES];
GLFrame frameCamera;

void SetupRC(void) {
  int iSphere;

  glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
  
  // draw everything as wireframe
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  // randomly place spheres in space
  for (iSphere = 0; iSphere < NUM_SPHERES; ++iSphere) {
    // pick random location between -20.0 and 20.0 at .1 increments
	float x = ((float)((rand() % 400) - 200) * 0.1f);
	float z = ((float)((rand() % 400) - 200) * 0.1f);
	spheres[iSphere].SetOrigin(x, 0.0f, z);
  }
  
  glColor3f(0.4f, 0.5f, 0.5f);
  glFrontFace(GL_CCW);
}

void DrawGround(void) {
  GLfloat fExtent = 20.0f;
  GLfloat fStep = 1.0f;
  GLfloat y = -0.4f;
  GLint   iLine;
  
  glBegin(GL_LINES);
    for (iLine = -fExtent; iLine <= fExtent; iLine += fStep) {
	  glVertex3f(iLine, y, fExtent);     // z line's point
	  glVertex3f(iLine, y, -fExtent);    // z line's point
	  
	  glVertex3f(fExtent, y, iLine);
	  glVertex3f(-fExtent, y, iLine);
	}
  glEnd();
}


void RenderScene(void) {
  int i;
  static GLfloat yRot = 0.0f;
  yRot += 0.5f;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable(GL_DEPTH_TEST);

  
  glPushMatrix();
    frameCamera.ApplyCameraTransform();
  
    // draw ground
    DrawGround();
  
    // draw randomly located spheres
    for (i = 0; i < NUM_SPHERES; ++i) {
      glPushMatrix();
	  spheres[i].ApplyActorTransform();
	  glutSolidSphere(0.1f, 13, 26);
	  glPopMatrix();
    }
	
 	glPushMatrix();
	  glTranslatef(0.0f, 0.0f, -2.5f);
	  
	  glPushMatrix();
	    glRotatef(yRot*1.5f, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.0f, 0.0f, 0.0f);
		glutSolidSphere(0.1f, 13, 26);
	  glPopMatrix();
	  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	  glutSolidTorus(0.1, 0.35, 20, 40);
	glPopMatrix();
  glPopMatrix();
  
  glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_UP)
    frameCamera.MoveForward(0.1f);
	
  if (key == GLUT_KEY_DOWN)
    frameCamera.MoveForward(-0.1f);
	
  if (key == GLUT_KEY_LEFT)
    frameCamera.RotateLocalY(0.1f);
	
  if (key == GLUT_KEY_RIGHT)
    frameCamera.RotateLocalY(-0.1);
	
  glutPostRedisplay();
}

void TimerFunction(int value) {
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
  if (h == 0)
    h = 1;
	
  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(35.0f, w/h, 1.0f, 400.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Sphere World");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutTimerFunc(33, TimerFunction, 1);
  glutSpecialFunc(SpecialKeys);
  SetupRC();
  glutMainLoop();
  return 0;
}