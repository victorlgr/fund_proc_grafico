/*
 * Seminário 1 - Grupo MMA
 * Cauê Montrose Bianchim, RA 11109715
 * Ismael Trinca Junior, RA 11131611
 * Rafael Branco Totino, RA 11201922308
 * Victor Luiz Gluz Romano, RA 11109915
 * Compilar o programa com gcc -o mma mma.cpp -lglut -lGL -lGLU -lm e executar com ./mma X, sendo X a opção desejada (1, 2, 3)
 * 
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <unistd.h>
#include <stdio.h>

double posicao = 0, tempo = 0;
int estado = 1, escolha = 0;

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

double funcao_x_t(double tempo)
{
   if (escolha == 1)
      return 1 * exp(-2 * tempo) * cos(10 * tempo) + 3 * exp(-2 * tempo) * sin(10 * tempo);
   else if (escolha == 2)
      return 17 * exp(-2 * tempo) - 12 * exp(-3 * tempo);
   else if (escolha == 3)
      return exp(-2 * tempo) * (5 * cos(7 * tempo) - 1.1429 * sin(7 * tempo));
   else
      return 0;
}

void draw_parede(void)
{
   glBegin(GL_LINE_STRIP);
   glVertex2f(0.0, 80.0);
   glVertex2f(0.0, 0.0);
   glVertex2f(100.0, 0.0);
   glEnd();
}

void draw_roda(void)
{
   GLdouble PI = 3.1415926535897;
   GLint circle_points = 100;
   GLfloat angle;
   glBegin(GL_LINE_LOOP);
   for (GLint i = 0; i < circle_points; i++)
   {
      angle = 2 * PI * i / circle_points;
      glVertex2f(1.8 * cos(angle), 1.8 * sin(angle));
   }
   glEnd();
}

void draw_massa(void)
{
   // Massa
   glBegin(GL_POLYGON);
   glVertex2f(0.0, 0.0);
   glVertex2f(0.0, 25.0);
   glVertex2f(25.0, 25.0);
   glVertex2f(25.0, 0.0);
   glEnd();

   // Roda
   glTranslatef(5, -2, 0);
   draw_roda();
   glTranslatef(15, 0, 0);
   draw_roda();
}

void draw_mola(int comprimento, double x)
{
   int y = 3;
   glBegin(GL_LINE_STRIP);
   glVertex2f(0.0, 0.0);
   for (int i = 1; i < comprimento; i++)
   {
      if (i % 2 == 0)
         y = -3;
      else
         y = 3;
      glVertex2f(x * i, y);
   }
   glVertex2f(x * comprimento, 0);
   glEnd();
}

void draw_amortecedor(double x)
{
   // Suporte
   glRotatef(90, 0, 0, 1);
   glBegin(GL_LINE_STRIP);
   glVertex2f(0, 10);
   glVertex2f(0, -5);
   glVertex2f(-4, -5);
   glVertex2f(-4, -19);
   glVertex2f(-3, -19);
   glVertex2f(-3, -6);
   glVertex2f(4, -6);
   glVertex2f(4, -19);
   glVertex2f(5, -19);
   glVertex2f(5, -5);
   glVertex2f(1, -5);
   glVertex2f(1, 10);
   glEnd();

   // Pistão
   glTranslatef(1, -19, 0);
   glTranslatef(0, x, 0);
   glRotatef(-180, 0, 0, 1);
   glBegin(GL_LINE_STRIP);
   glVertex2f(0, 11);
   glVertex2f(0, -5);
   glVertex2f(-3, -5);
   glVertex2f(-3, -6);
   glVertex2f(4, -6);
   glVertex2f(4, -5);
   glVertex2f(1, -5);
   glVertex2f(1, 11);
   glEnd();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(1.0, 1.0, 1.0);

   glLoadIdentity();
   glTranslatef(-40, -40, 0);
   draw_parede();

   glLoadIdentity();
   glTranslatef(posicao, -36, 0);
   draw_massa();

   glLoadIdentity();
   glTranslatef(-40, -15, 0);
   draw_mola(20, 2.0 + posicao / 20);

   glLoadIdentity();
   glTranslatef(-30, -30, 0);
   draw_amortecedor(-posicao);

   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-50.0, 50.0, -50.0 * (GLfloat)h / (GLfloat)w,
              50.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
   else
      glOrtho(-50.0 * (GLfloat)w / (GLfloat)h,
              50.0 * (GLfloat)w / (GLfloat)h, -50.0, 50.0, -1.0, 1.0);
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

void timer(int)
{
   glutPostRedisplay();
   glutTimerFunc(1000 / 60, timer, 1);
   tempo += 1000 / 60;
   double x_t = funcao_x_t(tempo / 1000);
   posicao = x_t;
}

int main(int argc, char **argv)
{
   escolha = atoi(argv[1]);
   if (escolha != 1 && escolha != 2 && escolha != 3)
   {
      printf("Opção inválida! Escolha entre as opções 1, 2 ou 3.\n");
      exit(0);
   }
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("mma.cpp");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(1000, timer, 0);
   glutMainLoop();
   return 0;
}
