/*
 * Meu Primeiro Programa: lab2-01.cpp
 * data 04/10/2022
 * Barbara Souza, RA 11009412
 * Cauê Montrose Bianchim, RA 11109715
 * Victor Luiz Gluz Romano, RA 11109915
 * 
 * Compilar com "gcc -o lab2-01 lab2-01.cpp -lglut -lGL -lGLU" e executar com ./lab2-01
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
// Função callback chamada para fazer o desenho
void Desenha(void)
{
    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);
    // Executa os comandos OpenGL

    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.8f, 0.0f);
    glVertex3f(0.2f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.075f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.5f, 0.075f, 0.0f);
    glVertex3f(1.0f, 0.2f, 0.0f);
    glVertex3f(0.8f, 1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    glEnd();

    glFlush();
}
// Inicializa parâmetros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}
// Programa Principal
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Lab2-01");
    glutDisplayFunc(Desenha);
    Inicializa();
    glutMainLoop();
    return 0;
}