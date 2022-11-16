/*
 * data 08/11/2022
 *
 * Cauê Montrose Bianchim, RA 11109715
 * Ismael Trinca Junior, RA 11131611
 * Rafael Branco Totino, RA 11201922308
 * Victor Luiz Gluz Romano, RA 11109915
 * 
 * Compilar com "gcc -o light2 light2.c -lglut -lGL -lGLU -lm" e executar com ./light2
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
   GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = {50.0};
   GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
   
   GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
   glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutSolidSphere(1.0, 20, 16);
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
              1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
   else
      glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
              1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
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
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
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
