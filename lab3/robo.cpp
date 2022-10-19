/*
 * Programa adaptado de robot.c
 *
 * data 13/10/2022
 * Cauê Montrose Bianchim, RA 11109715
 * Ismael Trinca Junior, RA 11131611
 * Rafael Branco Totino, RA 11201922308
 * Victor Luiz Gluz Romano, RA 11109915
 * 
 * Compilar com "gcc -o robo robo.cpp -lglut -lGL -lGLU -lm" e executar com ./robo
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0;
static int falange1 = 0, falange2 = 0;

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

void braco(void)
{
   glPushMatrix();
   // glRotatef(15, 1.0, 0.0, 0.0);
   // glRotatef(-45, 0.0, 1.0, 0.0);
   // glRotatef(-15, 0.0, 0.0, 1.0);
   glTranslatef(-1.0, 0.0, 0.0);

   // Shoulder
   glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
   glTranslatef(1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef(2.0, 0.4, 1.0);
   glutWireCube(1.0);
   glPopMatrix();
   glTranslatef(1.0, 0.0, 0.0);

   // Elbow
   glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
   glTranslatef(1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef(2.0, 0.4, 1.0);
   glutWireCube(1.0);
   glPopMatrix();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   // Draw shoulder
   glPushMatrix();
   glRotatef(15, 1.0, 0.0, 0.0);
   glRotatef(-75, 0.0, 1.0, 0.0);
   glTranslatef(-1.0, 0.0, 0.0);
   glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
   glTranslatef(1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef(2.0, 0.6, 0.65);
   glutWireCube(1.0);
   glPopMatrix();

   // Draw elbow
   glTranslatef(1.0, 0.0, 0.0);
   glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
   glTranslatef(1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef(2.0, 0.6, 0.65);
   glutWireCube(1.0);
   glPopMatrix();

   // Draw fingerBase 1
   glPushMatrix();
   glTranslatef(1.0, 0.25, 0.0);
   glRotatef(-(GLfloat)falange1, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, -0.25);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   // Draw fingerUp 1
   glTranslatef(0.15, 0.0, 0.0);
   glRotatef(-(GLfloat)falange2, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   glPopMatrix();

   // Draw fingerBase 2
   glPushMatrix();
   glTranslatef(1.0, 0.25, 0.0);
   glRotatef(-(GLfloat)falange1, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   // Draw fingerUp 2
   glTranslatef(0.15, 0.0, 0.0);
   glRotatef(-(GLfloat)falange2, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   glPopMatrix();

   // Draw fingerBase 3
   glPushMatrix();
   glTranslatef(1.0, 0.25, 0.0);
   glRotatef(-(GLfloat)falange1, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, 0.25);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   // Draw fingerUp 3
   glTranslatef(0.15, 0.0, 0.0);
   glRotatef(-(GLfloat)falange2, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   glPopMatrix();

   // Draw fingerBase 4 (Thumb)
   glPushMatrix();
   glTranslatef(1.0, -0.25, 0.0);
   glRotatef((GLfloat)falange1, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   // Draw fingerUp 4
   glTranslatef(0.15, 0.0, 0.0);
   glRotatef((GLfloat)falange2, 0.0, 0.0, 1.0);
   glTranslatef(0.15, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.3, 0.1, 0.15);
   glutWireCube(1);
   glPopMatrix();

   glPopMatrix();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 's':
      shoulder = (shoulder + 5) % 360;
      glutPostRedisplay();
      break;
   case 'S':
      shoulder = (shoulder - 5) % 360;
      glutPostRedisplay();
      break;
   case 'e':
      elbow = (elbow + 5) % 360;
      glutPostRedisplay();
      break;
   case 'E':
      elbow = (elbow - 5) % 360;
      glutPostRedisplay();
      break;

   case 'n':
      falange1 = (falange1 + 5) % 360;
      glutPostRedisplay();
      break;
   case 'N':
      falange1 = (falange1 - 5) % 360;
      glutPostRedisplay();
      break;
   case 'm':
      falange2 = (falange2 + 5) % 360;
      glutPostRedisplay();
      break;
   case 'M':
      falange2 = (falange2 - 5) % 360;
      glutPostRedisplay();
      break;
   case 27:
      exit(0);
      break;
   default:
      break;
   }
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
