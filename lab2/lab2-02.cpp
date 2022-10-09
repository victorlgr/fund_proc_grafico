/*
 * Meu Primeiro Programa: lab2-02.cpp
 * data 04/10/2022
 * Barbara Souza, RA 11009412
 * Cauê Montrose Bianchim, RA 11109715
 * Victor Luiz Gluz Romano, RA 11109915
 *
 * Compilar com "gcc -o lab2-02 lab2-02.cpp -lglut -lGL -lGLU -lm" e executar com ./lab2-02
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
// Função callback chamada para fazer o desenho
void Desenha(void)
{
    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);
    // Executa os comandos OpenGL

    glColor3f(0.0, 0.0, 0.0);
    GLdouble PI = 3.1415926535897;
    GLint circle_points = 100;
    GLfloat angle;
    glBegin(GL_LINE_LOOP);
    for (GLint i = 0; i < circle_points; i++)
    {
        angle = 2 * PI * i / circle_points;
        glVertex2f(0.8*cos(angle), 0.8*sin(angle));
    }
    glEnd();

    // Hexágono
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(10);
    glBegin(GL_POLYGON);
    glVertex3f(-0.8f, 0, 0);
    glVertex3f(-0.4f, -0.69f, 0);
    glVertex3f(0.4f, -0.69f, 0);
    glVertex3f(0.8f, 0, 0);
    glVertex3f(0.4f, 0.69f, 0);
    glVertex3f(-0.4f, 0.69f, 0);
    glEnd();

    // Quadrado
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.505f, 0.505f, 0);
    glVertex3f(-0.505f, -0.505f, 0);
    glVertex3f(0.505f, -0.505f, 0);
    glVertex3f(0.505f, 0.505f, 0);
    glEnd();

    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (GLint i = 0; i < circle_points; i++)
    {
        angle = 2 * PI * i / circle_points;
        glVertex2f(0.505*cos(angle), 0.505*sin(angle));
    }
    glEnd();

    // Linha horizontal
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();

    // Linha vertical
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0);
    glEnd();

    // Triângulo
    glColor3f(1.000, 0.6, 0.8);
    glPointSize(10);
    glBegin(GL_POLYGON);
    glVertex3f(-0.385f, -0.33f, 0);
    glVertex3f(0.385f, -0.33f, 0);
    glVertex3f(-0.385f, 0.33f, 0);
    glEnd();

    glFlush();
}
// Inicializa parâmetros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}
// Programa Principal
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Lab2-02");
    glutDisplayFunc(Desenha);
    Inicializa();
    glutMainLoop();
    return 0;
}