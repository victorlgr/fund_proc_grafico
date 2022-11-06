/*
Nome dos Integrantes:

03/11/2022


Para execução do programa basta inserir o seguinte comando:
gcc -o alphadois alphadois.c -lglut -lGL -lGLU && ./alphadois
*/

/*
 *  alpha.c
 *  This program draws several overlapping filled polygons
 *  to demonstrate the effect order has on alpha blending results.
 *  Use the 't' key to toggle the order of drawing polygons.
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static int leftFirst = GL_TRUE;

/*  Initialize alpha blending function.
 */
static void init(void)
{
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glShadeModel (GL_FLAT);
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

static void drawLeftTriangle(void)
{
   /* draw yellow triangle on LHS of screen */

   glBegin (GL_TRIANGLES);
      glColor4f(1.0, 1.0, 0.0, 0.75);
      glVertex3f(0.1, 0.9, 0.0); 
      glVertex3f(0.1, 0.1, 0.0); 
      glVertex3f(0.7, 0.5, 0.0); 
   glEnd();
}

static void drawRightTriangle(void)
{
   /* draw cyan triangle on RHS of screen */

   glBegin (GL_TRIANGLES);
      glColor4f(0.0, 1.0, 1.0, 0.75);
      glVertex3f(0.9, 0.9, 0.0); 
      glVertex3f(0.3, 0.5, 0.0); 
      glVertex3f(0.9, 0.1, 0.0); 
   glEnd();
}

static void drawUpTriangle(void)
{
   /* draw blue triangle on RHS of screen */

   glBegin (GL_TRIANGLES);
      glColor4f(0.0, 0.0, 1.0, 1.0);
      glVertex3f(0.5, 0.25, 0.0); 
      glVertex3f(0.1, 0.95, 0.0); 
      glVertex3f(0.9, 0.95, 0.0); 
   glEnd();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   if (leftFirst) {
      drawUpTriangle();
      drawLeftTriangle();
      drawRightTriangle();
   }
   else {
      drawUpTriangle();
      drawRightTriangle();
      drawLeftTriangle();
   }

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h) 
      gluOrtho2D (0.0, 1.0, 0.0, 1.0*(GLfloat)h/(GLfloat)w);
   else 
      gluOrtho2D (0.0, 1.0*(GLfloat)w/(GLfloat)h, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 't':
      case 'T':
         leftFirst = !leftFirst;
         glutPostRedisplay();	
         break;
      case 27:  /*  Escape key  */
         exit(0);
         break;
      default:
         break;
   }
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (200, 200);
   glutCreateWindow (argv[0]);
   init();
   glutReshapeFunc (reshape);
   glutKeyboardFunc (keyboard);
   glutDisplayFunc (display);
   glutMainLoop();
   return 0;
}
