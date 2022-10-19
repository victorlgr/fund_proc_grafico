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
 * Compilar com "gcc -o ex2 ex2.cpp -lglut -lGL -lGLU -lm" e executar com ./ex2
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

static GLfloat spin = 0.0;

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   glRotatef(spin, 0.0, 0.0, 1.0);

   glBegin(GL_POLYGON);
   glVertex2d(0, 6);
   glVertex2d(-1, 2);
   glVertex2d(1, 2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-2, 1);
   glVertex2d(-6, 0);
   glVertex2d(-2, -1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1, -2);
   glVertex2d(0, -6);
   glVertex2d(1, -2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(2, -1);
   glVertex2d(6, 0);
   glVertex2d(2, 1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-2, 1);
   glVertex2d(-1, 0);
   glVertex2d(0, 1);
   glVertex2d(-1, 2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(0, 1);
   glVertex2d(1, 0);
   glVertex2d(2, 1);
   glVertex2d(1, 2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1, 0);
   glVertex2d(-2, -1);
   glVertex2d(-1, -2);
   glVertex2d(0, -1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(0, -1);
   glVertex2d(1, -2);
   glVertex2d(2, -1);
   glVertex2d(1, 0);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1, 2);
   glVertex2d(0, 1);
   glVertex2d(1, 2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(-1, 0);
   glVertex2d(-2, -1);
   glVertex2d(-2, 1);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(0, -1);
   glVertex2d(-1, -2);
   glVertex2d(1, -2);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2d(1, 0);
   glVertex2d(2, -1);
   glVertex2d(2, 1);
   glEnd();

   glFlush();
}

void spinDisplay(void)
{
   spin = spin + 2.0;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

void animate_callback(void){
    glutPostRedisplay(); /* Manda o redesenhar o ecr� em cada frame */
    return;
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

void keyboard_callback_special(int key, int x, int y)
{
   switch (key)
   {
   case 1:
      glColor3f(0.0, 0.0, 1.0); /* F1: muda a cor para azul */
      break;

   case 2:
      glColor3f(0.0, 1.0, 0.0); /* F2: muda a cor para verde */
      break;

   case 3:
      glColor3f(1.0, 0.0, 0.0); /* F3: muda a cor para vermelho */
      break;
   case 4:
      glColor3f(1.0, 1.0, 1.0); /* F4: muda a cor para branco */
      break;

   default: /* isto aqui n�o faz nada, mas evita warnings :P */
      break;
   }

   return;
}

void mouse(int button, int state, int x, int y)
{
   switch (button)
   {
   case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
         glutIdleFunc(spinDisplay);
      break;
   case GLUT_MIDDLE_BUTTON:
   case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN)
         glutIdleFunc(NULL);
      break;
   default:
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
   glutSpecialFunc(keyboard_callback_special);
   glutMouseFunc(mouse);
   glutIdleFunc(animate_callback);
   glutMainLoop();
   return 0;
}
