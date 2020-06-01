/* Putting it all together: demonstrates smoother models, moving lights
 * This is 8th exercise in the 5th chapter of superbible 4th edition
 * Sagar Gandhi | 30/05/2020
 */
 
#include <GL/glut.h>

GLfloat xRot = 0.0f, yRot = 0.0f, xRotStep = 2.0f, yRotStep = 2.0f;

enum {
  MODE_FLAT = 1,
  MODE_SMOOTH
};

enum {
  MODE_VERYLOW = 1,
  MODE_MEDIUM,
  MODE_VERYHIGH
};

GLint iShade = MODE_FLAT, iTess = MODE_VERYLOW;
GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPos[] = {0.0f, 0.0f, 75.0f, 1.0f};
GLfloat spotDir[] = {0.0f, 0.0f, -1.0f};

void SetupLights(void) {
  glEnable(GL_LIGHTING);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  
  glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  
  // specific spot effects 
  // cut-off angle is 60 degrees
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
  glEnable(GL_LIGHT0);
  
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  
  // full specular reflectivity
  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
}

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  SetupLights();
}

void RenderScene(void) {
  if (iShade == MODE_FLAT)
    glShadeModel(GL_FLAT);
  else if (iShade == MODE_SMOOTH)
    glShadeModel(GL_SMOOTH);
    
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  
  glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.5f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    // specify new direction and position in the rotated coords
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    // translate the origin to move the cone out to where light is positioned
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glutSolidCone(4.0f, 6.0f, 15, 15);
    
    // draw smaller displaced sphere to denote a light bulb
    
    // save the lighting state variable
    glPushAttrib(GL_LIGHTING_BIT);
      // turn off lighting and specify bright yellow sphere
      glDisable(GL_LIGHTING);
      glColor3f(1.0f, 1.0f, 0.0f);
      glutSolidSphere(3.0f, 15, 15);
    // restore lighting state variable
    glPopAttrib();  
  glPopMatrix();
  
  // set material color and draw sphere in the middle
  glColor3f(0.0f, 0.0f, 1.0f);
  if (iTess == MODE_VERYLOW)
    glutSolidSphere(30.0f, 7, 7);
  else if (iTess == MODE_MEDIUM)
    glutSolidSphere(30.0f, 15, 15);
  else if (iTess == MODE_VERYHIGH)
    glutSolidSphere(30.0f, 50, 50);
    
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
  if (yRot >= 360.0f)
    yRot = 0.0f;
  if (xRot < 0.0f)
    xRot = 360.0f;
  if (yRot < 0.0f)
    yRot = 360.0f;
    
  glutPostRedisplay();
}

void ProcessMenu(int value) {
  switch(value) {
    case 1: 
      iShade = MODE_FLAT;
      break;
    case 2: 
      iShade = MODE_SMOOTH;
      break;
    case 3:
      iTess = MODE_VERYLOW;
      break;
    case 4:
      iTess = MODE_MEDIUM;
      break;
    case 5:
      iTess = MODE_VERYHIGH;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat nRange = 100.0f;
  if (h == 0)
    h = 1;
    
  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(35.0f, w/h, 1.0f, 500.0f);  
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -250.0f);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("SpotLight");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutTimerFunc(33, TimerFunction, 1);
  glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("Flat Shading", 1);
  glutAddMenuEntry("Smooth Shading", 2);
  glutAddMenuEntry("VL Tess", 3);
  glutAddMenuEntry("MD Tess", 4);
  glutAddMenuEntry("VH Tess", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  SetupRC();
  glutMainLoop();
  
  return(0);
}