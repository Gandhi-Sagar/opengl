/* Redoing spotlight exercise since many days have passed the last iteration
 * Sagar Gandhi | 26/06/2020
 */
 
#include <GL/glut.h>

enum {
  MODE_FLAT = 1,
  MODE_SMOOTH
};

enum {
  MODE_VERY_LOW = 1,
  MODE_MEDIUM,
  MODE_VERY_HIGH
};

GLfloat xRot = 0.0f, yRot = 0.0f, xRotStep = 2.0f, yRotStep = 2.0f;
GLint iShade = MODE_FLAT, iTess = MODE_VERY_LOW;
GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPos[] = {0.0f, 0.0f, 75.0f, 1.0f};
GLfloat spotDirection[] = {0.0f, 0.0f, -1.0f};

// function declarations
void SetupRC(void);
void SetupLights(void);
void RenderScene(void);
void ChangeSize(GLsizei, GLsizei);
void TimerFunction(int);
void SpecialKeys(int, int, int);
void ProcessMenu(int);

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
  glutAddMenuEntry("Low Tesselation", 3);
  glutAddMenuEntry("Medium Tesselation", 4);
  glutAddMenuEntry("High Tesselation", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  SetupRC();
  glutMainLoop();
  
  return(0);
}

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  SetupLights();
}

void SetupLights(void) {
  glEnable(GL_LIGHTING);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  
  glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0f);
  glEnable(GL_LIGHT0);
  
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
}

void ChangeSize(GLsizei w, GLsizei h) {
  if (h == 0)
    h = 1;
    
  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(35.0f, w/h, 1.0, 500.0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -250.0f);
}

void TimerFunction(int value) {
  glutPostRedisplay();
  glutTimerFunc(33, TimerFunction, 1);
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
      iTess = MODE_VERY_LOW;
      break;
    case 4:
      iTess = MODE_MEDIUM;
      break;
    case 5:
      iTess = MODE_VERY_HIGH;
      break;
  }
  glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_UP:
      xRot += xRotStep;
      if (xRot >= 360.0f)
        xRot = 0.0f;
      break;
    case GLUT_KEY_DOWN:
      xRot -= xRotStep;
      if (xRot < 0.0f)
        xRot = 360.0f;
      break;
    case GLUT_KEY_LEFT:
      yRot -= yRotStep;
      if (yRot < 0.0f)
        yRot = 360.0f;
      break;
    case GLUT_KEY_RIGHT:
      yRot += yRotStep;
      if (yRot >= 360.0f)
        yRot = 0.0f;
      break;
    default:
      break;
  }
  glutPostRedisplay();
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
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glutSolidCone(4.0f, 6.0f, 15, 15);
    
    glPushAttrib(GL_LIGHTING_BIT);
      glDisable(GL_LIGHTING);
      glColor3f(1.0f, 1.0f, 0.03f);
      glutSolidSphere(3.0f, 15, 15);
    glPopAttrib();
  glPopMatrix();
  
  glColor3f(0.4f, 0.4f, 0.4f);
  if (iTess == MODE_VERY_LOW)
    glutSolidSphere(30.0f, 7, 7);
  else if (iTess == MODE_MEDIUM)
    glutSolidSphere(30.0f, 15, 15);
  else if (iTess == MODE_VERY_HIGH)
    glutSolidSphere(30.0f, 50, 50);
  
  glutSwapBuffers();
}
