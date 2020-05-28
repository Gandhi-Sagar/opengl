/* Demonstrates use of directional light by computing surface normals for the
 * polygon.
 * This is 6th exercise in the 5th chapter of superbible 4th edition.
 * Sagar Gandhi | 26/05/2020
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLfloat xRot = 0.0f, yRot = 0.0f, xRotStep = 2.0f, yRotStep = 2.0f;
GLfloat zTrans = -1.5f, zTransStep = 0.1f;

void FindUnitNormal(const GLfloat p1[],
                    const GLfloat p2[],
                    const GLfloat p3[],
                    GLfloat result[]) {
  GLfloat v1[3], v2[3], vLen;

  // v1 = p3 - p1
  v1[0] = p3[0] - p1[0];
  v1[1] = p3[1] - p1[1];
  v1[2] = p3[2] - p1[2];
  
  // v2 = p2 - p1
  v2[0] = p2[0] - p1[0];
  v2[1] = p2[1] - p1[0];
  v2[2] = p2[2] - p1[0];
  
  // cross product of v1 and v2 is our unnormalized normal
  result[0] = v1[1]*v2[2] - v2[1]*v1[2];
  result[1] = -v1[0]*v2[2] + v2[0]*v1[2];
  result[2] = v1[0]*v2[1] - v2[0]*v1[1];
  
  vLen = (float)sqrt(result[0]*result[0] + result[1]*result[1] +
      result[2]*result[2]);
  if (vLen == 0.0f)
    vLen = 0.000001f;
  result[0] /= vLen;
  result[1] /= vLen;
  result[2] /= vLen;
}

void SetupRC(void) {
  GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
  GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat specularLight[] = {1.0f, 1.0f, 0.0f, 1.0f};
  GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
  
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  // all materials hereafter have a full specular reflectivity with high shine
  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
  glEnable(GL_NORMALIZE);
  
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.8f, 1.0f);
}

void RenderSurfaceNormaledTriangle(GLfloat p11, GLfloat p12, GLfloat p13,
                                   GLfloat p21, GLfloat p22, GLfloat p23,
                                   GLfloat p31, GLfloat p32, GLfloat p33) {
  GLfloat p1[3], p2[3], p3[3], normal[3];
  p1[0] = p11, p1[1] = p12, p1[2] = p13;
  p2[0] = p21, p2[1] = p22, p2[2] = p23;
  p3[0] = p31, p3[1] = p32, p3[2] = p33;
  FindUnitNormal(p1, p2, p3, normal);
  glNormal3fv(normal);
  glVertex3fv(p1);
  glVertex3fv(p2);
  glVertex3fv(p3);
}

void DrawJet(void) {
  glBegin(GL_TRIANGLES);
    // nose
                                  // v1              v2
	  RenderSurfaceNormaledTriangle(0.0f, 0.0f, 0.6f, -0.15f, 0.0f, 0.3f,
                                  0.15f, 0.0f, 0.3f); // v3
    RenderSurfaceNormaledTriangle(0.15f, 0.0f, 0.3f, 0.0f, 0.15f, 0.3f,
                                  0.0f, 0.0f, 0.6f);
    RenderSurfaceNormaledTriangle(0.0f, 0.0f, 0.6f, 0.0f, 0.15f, 0.3f,
                                  -0.15f, 0.0f, 0.3f);
                                  
    // body
    RenderSurfaceNormaledTriangle(-0.15f, 0.0f, 0.3f, 0.0f, 0.15f, 0.3f,
                                  0.0f, 0.0f, -0.56f);
    RenderSurfaceNormaledTriangle(0.0f, 0.0f, -0.56f, 0.0f, 0.15f, 0.3f,
                                  0.15f, 0.0f, 0.3f);
    RenderSurfaceNormaledTriangle(0.15f, 0.0f, 0.3f, -0.15f, 0.0f, 0.3f,
                                  0.0f, 0.0f, -0.56f);
                                  
    // left wing base
    RenderSurfaceNormaledTriangle(0.0f, 0.02f, 0.27f, 0.6f, 0.02f, -0.08f,
                                  -0.6f, 0.02f, -0.08f);
    // left wing top
    RenderSurfaceNormaledTriangle(0.6f, 0.02f, -0.08f, 0.0f, 0.07f, -0.08f,
                                  0.0f, 0.02f, 0.27f);
    // left wing bottom
    RenderSurfaceNormaledTriangle(0.6f, 0.02f, -0.08f, 0.0f, 0.02f, -0.08f,
                                  0.0f, 0.07f, -0.08f);
    // right wing top
    RenderSurfaceNormaledTriangle(0.0f, 0.02f, 0.27f, 0.0f, 0.07f, -0.08f,
                                  -0.6f, 0.02f, -0.08f);
    // right wing bottom
    RenderSurfaceNormaledTriangle(0.0f, 0.07f, -0.08f, 0.0f, 0.02f, -0.08f,
                                  -0.6f, 0.02f, -0.08f);
                                  
    // bottom
    RenderSurfaceNormaledTriangle(-0.3f, -0.005f, -0.57f, 0.3f, -0.005f, -0.57f,
                                  0.0f, -0.005f, -0.4f);
    // bottom left
    RenderSurfaceNormaledTriangle(0.0f, -0.005f, -0.4f, 0.3f, -0.005f, -0.57f,
                                  0.0f, 0.04f, -0.57f);
    // bottom right
    RenderSurfaceNormaledTriangle(0.0f, 0.04f, -0.57f, -0.3f, -0.005f, -0.57f,
                                  0.0f, -0.005f, -0.4f);
    // bottom back
    RenderSurfaceNormaledTriangle(0.3f, -0.005f, -0.57f, -0.3f, -0.005f, -0.57f,
                                  0.0f, 0.04f, -0.57f);
    // top of the tail
    RenderSurfaceNormaledTriangle(0.0f, 0.005f, -0.4f, 0.03f, 0.005f, -0.57f,
                                  0.0f, 0.25f, -0.65f);
    RenderSurfaceNormaledTriangle(0.0f, 0.25f, -0.65f, -0.03f, 0.005f, -0.57f,
                                  0.0f, 0.005f, -0.4f);
    RenderSurfaceNormaledTriangle(0.03f, 0.005f, -0.57f, -0.03f, 0.005f, -0.57f,
                                  0.0f, 0.25f, -0.65f);
    
	glEnd();
}

void RenderScene(void) {
  GLfloat p1[3], p2[3], p3[3], normal[3];  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, zTrans);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawJet();
  glPopMatrix();
  
  glutSwapBuffers();
}

void TimerFunction(int value) {
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
}

void SpecialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_UP)
    xRot += xRotStep;
  if (key == GLUT_KEY_DOWN)
    xRot -= xRotStep;
  if (key == GLUT_KEY_LEFT)
    yRot += yRotStep;
  if (key == GLUT_KEY_RIGHT)
    yRot -= yRotStep;
    
  if (xRot >= 360.0f)
    xRot = 0.0f;
  if (xRot < 0.0f)
    xRot = 360.0f;
  if (yRot >= 360.0f)
    yRot = 0.0f;
  if (yRot < 0.0f)
    yRot = 360.0f;
    
  glutPostRedisplay();
}


void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat lightPos[] = {1.0f, 0.3f, -1.4f, 1.0f};
  
  if (h == 0)
    h = 1;
	
  glViewport(0, 0, w, h);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, w/h, 0.1f, 100.0f);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Specular Jet");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutTimerFunc(33, TimerFunction, 1);
  SetupRC();
  glutMainLoop();
  
  return(0);
}