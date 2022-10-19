/*
 *  model.c
 *  This program demonstrates modeling transformations
 *  Modificado em 10/11/2008 - UFABC
 * 
 * data 13/10/2022
 * Cauê Montrose Bianchim, RA 11109715
 * Ismael Trinca Junior, RA 11131611
 * Rafael Branco Totino, RA 11201922308
 * Victor Luiz Gluz Romano, RA 11109915
 * 
 * Compilar com "gcc -o animal animal.cpp -lglut -lGL -lGLU -lm" e executar com ./animal
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

void init(void)
{
   glClearColor(0.0, 0.0, 1.0, 0.0);
   glShadeModel(GL_FLAT);
}

void draw_cabeca(void)
{
   glBegin(GL_POLYGON);
   for (GLfloat i = 0; i < 360; i++)
   {
      float x = cos(i * M_PI / 180.f) * 10; // keep the axes radius same
      float y = sin(i * M_PI / 180.f) * 20;
      glVertex2f(x, y);
   }

   glEnd();
}

void draw_olho(void)
{
   glBegin(GL_POLYGON);
   for (GLfloat i = 0; i < 360; i++)
   {
      float x = cos(i * M_PI / 180.f) * 2; // keep the axes radius same
      float y = sin(i * M_PI / 180.f) * 2;
      glVertex2f(x, y);
   }

   glEnd();
}

void draw_orelha(void)
{
   glBegin(GL_POLYGON);
   for (GLfloat i = 0; i < 180; i++)
   {
      float x = cos(i * M_PI / 180.f) * 3.5; // keep the axes radius same
      float y = sin(i * M_PI / 180.f) * 20;
      glVertex2f(x, y);
   }

   glEnd();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.5, 0.5, 0.5);

   glLoadIdentity();
   glRotated(-10, 0, 0, 1);
   draw_cabeca();

   glColor3f(0, 0, 0);
   glLoadIdentity();
   glTranslated(-8, 7, 0);
   draw_olho();

   glColor3f(0, 0, 0);
   glLoadIdentity();
   glTranslated(9, 6, 0);
   draw_olho();

   glColor3f(1.000, 0.6, 0.8);
   glLoadIdentity();
   glTranslated(-2, 15, 0);
   glRotated(50, 0, 0, 1);
   draw_orelha();

   glColor3f(1.000, 0.6, 0.8);
   glLoadIdentity();
   glTranslated(6, 14, 0);
   glRotated(-50, 0, 0, 1);
   draw_orelha();

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-60.0, 60.0, -60.0 * (GLfloat)h / (GLfloat)w,
              60.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
   else
      glOrtho(-60.0 * (GLfloat)w / (GLfloat)h,
              60.0 * (GLfloat)w / (GLfloat)h, -60.0, 60.0, -1.0, 1.0);
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
   glutCreateWindow("Animal");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
