/*
 *  rotacao.cpp
 *  Este programa originalmente denominado exemplo1.c foi obtido 
 *  na pùgina Web do Prof. Samuel Nunes, por ser bastante didatico:
 *  http://w3.ualg.pt/~srnunes/CG/index.html
 *  e foi adaptado por Celso Kurashima para a disciplina BC1515
 *  Modificado em 22/03/2009 - UFABC
 */


/* Inclui os headers do OpenGL, GLU, e GLUT */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


/**********************************************************************/
/*                        Declaraùùo de funùùes                       */
/**********************************************************************/
void init_glut(const char *window_name, int *argcp, char **argv);
void display_callback(void);
void reshape_callback(int w, int h);
void animate_callback(void);
void keyboard_callback(unsigned char key, int x, int y);
void keyboard_callback_special(int key, int x, int y);
void menu_callback(int value);


/**********************************************************************/
/*                                                                    */
/*                       Funùùo principal (main)                      */
/*                                                                    */
/**********************************************************************/

int main(int argc, char **argv){

   /* inicia o GLUT e alguns parùmetros do OpenGL */
   init_glut("BC1515 - rotacao.cpp", &argc, argv);

   /* funùùo de controlo do GLUT */
   glutMainLoop();

   return 0;
}


/**********************************************************************/
/*                                                                    */
/*                         Definiùùo de funùùes                       */
/*                                                                    */
/**********************************************************************/

/*
 * inicia o GLUT e alguns parùmetros do OpenGL
 */
void init_glut(const char *nome_janela, int *argcp, char **argv){

    /* inicia o GLUT */
    glutInit(argcp,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);

    /* define as funcùes de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(keyboard_callback_special);
    glutIdleFunc(animate_callback);

    /* define a cùr com a qual a tela serù apagado */
    glClearColor(0.0,0.0,0.0,0.0);

    /* define a cor de desenho inicial (azul) */
    glColor3f(0.0, 0.0, 1.0);

    return;
}


/*
 * funùùo para controlar o display (desenhar na tela em cada frame)
 */
void display_callback(void){
    static GLfloat angulo = 0.0f; /* por ter sido declarada como "static" dentro *
                                   * de uma funùùo, esta variùvel tem "memùria"  */

    /* Apaga o ecrù e reinicia a matriz */
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    /* faz variar o ùngulo entre 0 e 360 graus */
    angulo++;
    if (angulo> 360.0) angulo -= 360.0;

    /* desenha um triùngulo rodado de acordo com "angulo" */
    glRotatef(angulo, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.289);
        glVertex2f( 0.5, -0.289);
        glVertex2f( 0.0,  0.577);
    glEnd();

    /* troca os buffers, mostrando o que acabou de ser desenhado */
    glutSwapBuffers();
    return;
}


/*
 * Processa o reshape da janela
 */
void reshape_callback(int w, int h){

   /* define a zona da janela onde se vai desenhar */
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   /* muda para o modo GL_PROJECTION e reinicia a projecùùo */
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();

   /* adapta a projecùùo ortogonal de acordo com as dimensùes da janela */
   if (h > w){
      gluOrtho2D(-1.0, 1.0, (GLfloat)-h/(GLfloat)w, (GLfloat)h/(GLfloat)w);
   }else{
      gluOrtho2D((GLfloat)-w/(GLfloat)h, (GLfloat)w/(GLfloat)h, -1.0, 1.0);
   }

   /* muda para o modo GL_MODELVIEW (nùo pretendemos alterar a projecùùo *
    * quando estivermos a desenhar na tela)                              */
   glMatrixMode (GL_MODELVIEW);
   return;
}


/*
 * Funùùo necessùria para a animaùùo
 */
void animate_callback(void){
    glutPostRedisplay(); /* Manda o redesenhar o ecrù em cada frame */
    return;
}


/*
 * Controlo das teclas normais
 */
void keyboard_callback(unsigned char key, int x, int y){
    if (key==27) exit(0); /* Esc: sai do programa */
    return;
}


/*
 * Controlo das teclas especiais (Cursores, F1 a F12, etc...)
 */
void keyboard_callback_special(int key, int x, int y){
    switch(key){
        case 1:
            glColor3f(0.0, 0.0, 1.0);      /* F1: muda a cor para azul */
            break;

        case 2:
            glColor3f(0.0, 1.0, 0.0);      /* F2: muda a cor para verde */
            break;

        case 3:
            glColor3f(1.0, 0.0, 0.0);      /* F2: muda a cor para vermelho */
            break;

        default: /* isto aqui nùo faz nada, mas evita warnings :P */
            break;
    }

    return;
}

