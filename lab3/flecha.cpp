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
 * Compilar com "gcc -o flecha flecha.cpp -lglut -lGL -lGLU -lm" e executar com ./flecha
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

void draw_bola(void)
{
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
   for (GLfloat i = 0; i < 360; i++)
   {
      float x = cos(i * M_PI / 180.f) * 10; // keep the axes radius same
      float y = sin(i * M_PI / 180.f) * 20;
      glVertex2f(x, y);
   }

   glEnd();
}

void draw_cilindro(void)
{
   glBegin(GL_POLYGON);

   glVertex2d(75, 125);
   glVertex2d(75, 0);
   glVertex2d(0, 0);
   glVertex2d(0, 125);

   glVertex2d(10, 126);
   glVertex2d(20, 127);
   glVertex2d(30, 128);
   glVertex2d(40, 128);
   glVertex2d(50, 127);
   glVertex2d(60, 126);
   glVertex2d(70, 125);

   glEnd();
}

void draw_triangulo(void){
   glBegin(GL_POLYGON);
   glVertex2d(0, 0);
   glVertex2d(50, -75);
   glVertex2d(100, 0);
   glEnd();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 0.0);
   glLoadIdentity();
   draw_cilindro();

   glColor3f(1.0, 0.0, 0.0);
   glLoadIdentity();
   glTranslated(-13, 0, 0);
   draw_triangulo();


   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-250.0, 250.0, -250.0 * (GLfloat)h / (GLfloat)w,
              250.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
   else
      glOrtho(-250.0 * (GLfloat)w / (GLfloat)h,
              250.0 * (GLfloat)w / (GLfloat)h, -250.0, 250.0, -1.0, 1.0);
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
   glutCreateWindow("Flecha");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
