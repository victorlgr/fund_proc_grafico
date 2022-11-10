/*
 * smooth.c
 * This program demonstrates smooth shading.
 * A smooth shaded polygon is drawn in a 2-D projection.
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

double rotate_y = 0;
double rotate_x = 0;

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();

   glRotatef(rotate_x, 1.0, 0.0, 0.0);
   glRotatef(rotate_y, 0.0, 1.0, 0.0);

   // Frente
   glBegin(GL_POLYGON);

   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(0.5, -0.5, -0.5);

   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(0.5, 0.5, -0.5);

   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(-0.5, 0.5, -0.5);

   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(-0.5, -0.5, -0.5);

   glEnd();

   // Verso
   glBegin(GL_POLYGON);

   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(0.5, -0.5, 0.5);

   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(0.5, 0.5, 0.5);

   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(-0.5, 0.5, 0.5);

   glColor3f(0.0, 0.0, 0.0);
   glVertex3f(-0.5, -0.5, 0.5);

   glEnd();

   // Direita
   glBegin(GL_POLYGON);

   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(0.5, -0.5, -0.5);

   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(0.5, 0.5, -0.5);

   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(0.5, 0.5, 0.5);

   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(0.5, -0.5, 0.5);

   glEnd();

   // Esquerda
   glBegin(GL_POLYGON);

   glColor3f(0.0, 0.0, 0.0);
   glVertex3f(-0.5, -0.5, 0.5);

   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(-0.5, 0.5, 0.5);

   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(-0.5, 0.5, -0.5);

   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(-0.5, -0.5, -0.5);

   glEnd();

   // Cima
   glBegin(GL_POLYGON);

   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(0.5, 0.5, 0.5);

   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(0.5, 0.5, -0.5);

   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(-0.5, 0.5, -0.5);

   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(-0.5, 0.5, 0.5);

   glEnd();

   // Baixo
   glBegin(GL_POLYGON);

   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(0.5, -0.5, -0.5);

   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(0.5, -0.5, 0.5);

   glColor3f(0.0, 0.0, 0.0);
   glVertex3f(-0.5, -0.5, 0.5);

   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(-0.5, -0.5, -0.5);

   glEnd();

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      gluOrtho2D(0.0, 2.0, 0.0, 2.0 * (GLfloat)h / (GLfloat)w);
   else
      gluOrtho2D(0.0, 2.0 * (GLfloat)w / (GLfloat)h, 0.0, 2.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 27:
      exit(0);
      break;
   }
}

void specialKeys(int key, int x, int y)
{

   //  Right arrow - increase rotation by 5 degree
   if (key == GLUT_KEY_RIGHT)
      rotate_y += 5;

   //  Left arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_LEFT)
      rotate_y -= 5;

   else if (key == GLUT_KEY_UP)
      rotate_x += 5;

   else if (key == GLUT_KEY_DOWN)
      rotate_x -= 5;

   //  Request display update
   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(900, 900);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   // glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeys);
   glutMainLoop();
   return 0;
}
