/*
 * Seminário 2 - Grupo MMA
 * Cauê Montrose Bianchim, RA 11109715
 * Ismael Trinca Junior, RA 11131611
 * Rafael Branco Totino, RA 11201922308
 * Victor Luiz Gluz Romano, RA 11109915
 * Compilar o programa com gcc -o mma mma.c -lglut -lGL -lGLU -lm -lSOIL e executar com ./mma
 *
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <complex.h>
#include <sys/stat.h>
#include <time.h>
#include "SOIL/SOIL.h"

double posicao = 0, tempo = 0;
double massa = 0, mola = 0, amortecedor = 0, F = 0, x0 = 0, v0 = 0;
int bool_iluminacao = 0, bool_textura = 0;
double red_iluminacao = 0, green_iluminacao = 0, blue_iluminacao = 0, alpha_iluminacao = 0;
long int tempo_arquivo = 0, tempo_ultimo_arquivo = 0;

GLuint textura_parede;
GLuint textura_grama;
GLuint textura_massa;
GLuint textura_fundo;

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);

   textura_parede = SOIL_load_OGL_texture("parede.tga", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB);
   textura_grama = SOIL_load_OGL_texture("grama.tga", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB);
   textura_massa = SOIL_load_OGL_texture("massa.tga", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB);
   textura_fundo = SOIL_load_OGL_texture("fundo.tga", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB);
}

void iluminacao()
{
   if (bool_iluminacao == 1)
   {
      GLfloat light_position[] = {40.0, 20.0, 20.0, 0.0};
      GLfloat light_ambient[] = {red_iluminacao, green_iluminacao, blue_iluminacao, alpha_iluminacao};

      glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);

      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      glEnable(GL_COLOR_MATERIAL);
   }
}

double funcao_x_t(double t, double m, double k, double b, double F, double x0, double v0)
{
   double potencia = pow(b, 2);
   double complex raiz = csqrt(potencia - 4 * k * m);
   double complex C = ((k * raiz - b * k) * x0 - 2 * k * m * v0 - F * raiz + b * F) / (2 * k * raiz);
   double complex C1 = ((k * raiz + b * k) * x0 + 2 * k * m * v0 - F * raiz - b * F) / (2 * k * raiz);
   double x = C1 * (cexp(((raiz - b) / 2 * m) * t)) + C * (cexp(((-raiz - b) / 2 * m) * t)) + F / k;
   return x;
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
   glVertex2f(-4, -25);
   glVertex2f(-3, -25);
   glVertex2f(-3, -6);
   glVertex2f(4, -6);
   glVertex2f(4, -25);
   glVertex2f(5, -25);
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

void draw_parede_textura(void)
{
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textura_parede);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0);
   glVertex2f(-5.0, 80.0);
   glTexCoord2f(1, 0);
   glVertex2f(0.0, 80.0);
   glTexCoord2f(1, 1);
   glVertex2f(0.0, 0.0);
   glTexCoord2f(0, 1);
   glVertex2f(-5.0, 0.0);
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

void draw_chao_textura(void)
{
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textura_grama);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0);
   glVertex2f(-5.0, 0.0);
   glTexCoord2f(1, 0);
   glVertex2f(80.0, 0.0);
   glTexCoord2f(1, 1);
   glVertex2f(80., -5.0);
   glTexCoord2f(0, 1);
   glVertex2f(-5.0, -5.0);
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

void draw_fundo_textura(void)
{
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textura_fundo);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0);
   glVertex2f(0.0, 80.0);
   glTexCoord2f(1, 0);
   glVertex2f(80.0, 80.0);
   glTexCoord2f(1, 1);
   glVertex2f(80.0, 0.0);
   glTexCoord2f(0, 1);
   glVertex2f(0.0, 0.0);
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

void draw_massa_textura(void)
{
   // Massa
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textura_massa);
   glBegin(GL_POLYGON);
   glTexCoord2f(0, 0);
   glVertex2f(0.0, 0.0);
   glTexCoord2f(1, 0);
   glVertex2f(0.0, 25.0);
   glTexCoord2f(1, 1);
   glVertex2f(25.0, 25.0);
   glTexCoord2f(0, 1);
   glVertex2f(25.0, 0.0);
   glEnd();
   glDisable(GL_TEXTURE_2D);

   glColor3f(0, 0, 0);
   // Roda
   glTranslatef(5, -2, 0);
   draw_roda();
   glTranslatef(15, 0, 0);
   draw_roda();
}

void draw_com_textura()
{
   glLoadIdentity();
   glTranslatef(-40, -40, 0);
   draw_parede_textura();
   draw_chao_textura();
   draw_fundo_textura();

   glLoadIdentity();
   glTranslatef(posicao, -36, 0);
   draw_massa_textura();

   glLoadIdentity();
   glTranslatef(-40, -15, 0);
   draw_mola(20, 2.0 + posicao / 20);

   glLoadIdentity();
   glTranslatef(-30, -30, 0);
   draw_amortecedor(-posicao);
   glColor3f(1, 1, 1);
}

void draw_sem_textura()
{
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
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   if(bool_textura == 1)
      draw_com_textura();
   else
      draw_sem_textura();

   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-50.0, 50.0, -50.0 * (GLfloat)h / (GLfloat)w,
              50.0 * (GLfloat)h / (GLfloat)w, -50.0, 50.0);
   else
      glOrtho(-50.0 * (GLfloat)w / (GLfloat)h,
              50.0 * (GLfloat)w / (GLfloat)h, -50.0, 50.0, -50.0, 50.0);
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

long int checa_arquivo()
{
   struct stat attr;
   stat("dados.csv", &attr);
   return attr.st_mtime;
}

void ler_arquivo()
{
   FILE *fp;
   fp = fopen("dados.csv", "r");
   fscanf(fp, "%*[^\n]\n%lf;%lf;%lf;%lf;%lf;%lf;%d;%lf;%lf;%lf;%lf;%d", &massa, &mola, &amortecedor, &F, &x0, &v0, &bool_iluminacao, &red_iluminacao, &green_iluminacao, &blue_iluminacao, &alpha_iluminacao, &bool_textura);
   fclose(fp);
}

void timer(int placeholder)
{
   glutPostRedisplay();
   glutTimerFunc(1000 / 60, timer, 1);
   tempo_ultimo_arquivo = checa_arquivo();
   if (tempo_ultimo_arquivo > tempo_arquivo)
   {
      tempo_arquivo = checa_arquivo();
      tempo = 0;
      posicao = 0;
      ler_arquivo();
      iluminacao();
   }
   tempo++;
   double x_t = funcao_x_t(tempo, massa, mola, amortecedor, F, x0, v0);
   posicao = x_t;
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("mma.c");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(1000, timer, 0);
   glutMainLoop();
   return 0;
}