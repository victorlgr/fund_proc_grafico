/*
 *  model.c
 *  This program demonstrates modeling transformations
 *  Modificado em 10/11/2008 - UFABC
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void draw_massa(void)
{
   glBegin (GL_POLYGON);
   glVertex2f(0.0, 0.0);
   glVertex2f(0.0, 25.0);
   glVertex2f(25.0, 25.0);
   glVertex2f(25.0, 0.0);
   glEnd();
}

void draw_mola(int comprimento, double x)
{
   int y = 5;
   glBegin (GL_LINE_STRIP);
   glVertex2f(0.0, 0.0);
   for(int i = 1; i < comprimento; i++){
      if(i % 2 == 0)
         y = -5;
      else
         y = 5;
      glVertex2f(x*i,y);
   }
   glVertex2f(x*comprimento, 0);
   glEnd();
}

void draw_amortecedor(double x)
{
   glRotatef(90, 0, 0, 1);
   glBegin (GL_LINE_STRIP);
   glVertex2f(0,0);
   glVertex2f(0, -5);
   glVertex2f(-7, -5);
   glVertex2f(-7, -19);
   glVertex2f(-6, -19);
   glVertex2f(-6, -6);
   glVertex2f(7, -6);
   glVertex2f(7, -19);
   glVertex2f(8, -19);
   glVertex2f(8, -5);
   glVertex2f(1, -5);
   glVertex2f(1, 0);
   glEnd();

   glLoadIdentity();
   glTranslatef(0, -30, 0);
   glTranslatef(x, -9, 0);
   glRotatef(-90, 0, 0, 1);
   glBegin (GL_LINE_STRIP);
   glVertex2f(0,0);
   glVertex2f(0, -5);
   glVertex2f(-6, -5);
   glVertex2f(-6, -6);
   glVertex2f(7, -6);
   glVertex2f(7,-5);
   glVertex2f(1,-5);
   glVertex2f(1,0);
   glEnd();


}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

   glLoadIdentity ();
   glTranslatef(-10, -10, 0);
   glColor3f (1.0, 1.0, 1.0);
   draw_massa ();
   glLoadIdentity ();
   glTranslatef(-10, -25, 0);
   draw_mola(10,5);
   glLoadIdentity ();
   glTranslatef(-10, -40, 0);
   draw_amortecedor(10);

   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (w <= h)
      glOrtho (-50.0, 50.0, -50.0*(GLfloat)h/(GLfloat)w,
         50.0*(GLfloat)h/(GLfloat)w, -1.0, 1.0);
   else
      glOrtho (-50.0*(GLfloat)w/(GLfloat)h,
         50.0*(GLfloat)w/(GLfloat)h, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("model.c");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
