/*
 *  model.c
 *  This program demonstrates modeling transformations
 *  Modificado em 10/11/2008 - UFABC
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);

   glBegin(GL_POLYGON);
   glVertex2d(0,6);
   glVertex2d(-1,2);
   glVertex2d(1,2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-2,1);
   glVertex2d(-6,0);
   glVertex2d(-2,-1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1,-2);
   glVertex2d(0,-6);
   glVertex2d(1,-2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(2,-1);
   glVertex2d(6,0);
   glVertex2d(2,1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-2,1);
   glVertex2d(-1,0);
   glVertex2d(0,1);
   glVertex2d(-1,2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(0,1);
   glVertex2d(1,0);
   glVertex2d(2,1);
   glVertex2d(1,2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1,0);
   glVertex2d(-2,-1);
   glVertex2d(-1,-2);
   glVertex2d(0,-1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(0,-1);
   glVertex2d(1,-2);
   glVertex2d(2,-1);
   glVertex2d(1,0);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1,2);
   glVertex2d(0,1);
   glVertex2d(1,2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1,0);
   glVertex2d(-2,-1);
   glVertex2d(-2,1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(0,-1);
   glVertex2d(-1,-2);
   glVertex2d(1,-2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(1,0);
   glVertex2d(2,-1);
   glVertex2d(2,1);
   glEnd();

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-20.0, 20.0, -20.0 * (GLfloat)h / (GLfloat)w,
              20.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
   else
      glOrtho(-20.0 * (GLfloat)w / (GLfloat)h,
              20.0 * (GLfloat)w / (GLfloat)h, -20.0, 20.0, -1.0, 1.0);
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

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Ex2");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
