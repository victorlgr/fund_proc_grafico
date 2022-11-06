/*
	Test of interpenetrating planes with alpha-channel colors, no lighting.

	Source file to be used with
	Cunningham, Computer Graphics: Programming in OpenGL for Visual Communication, Prentice-Hall, 2007

	Intended for class use only
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

static GLfloat angle = 0.0;

void myinit(void);
void display( void );
void reshape(int w,int h);
void keyboard(unsigned char key, int x, int y);
//void animate(void);

void myinit(void)
{
//        glEnable(GL_DEPTH_TEST);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display( void )
{
    typedef GLfloat point3[3];

//  The four parts of the X-Z plane
    point3 plane0pp[4]={{ 0.0, 0.0,  0.0},   // X-Z plane +X +Z
                        { 0.0, 0.0,  1.0},
                        { 1.0, 0.0,  1.0},
                        { 1.0, 0.0,  0.0} };
    point3 plane0pm[4]={{ 0.0, 0.0,  0.0},   // X-Z plane +X -Z
                        { 1.0, 0.0,  0.0},
                        { 1.0, 0.0, -1.0},
                        { 0.0, 0.0, -1.0} };
    point3 plane0mp[4]={{ 0.0, 0.0,  0.0},   // X-Z plane -X +Z
                        {-1.0, 0.0,  0.0},
                        {-1.0, 0.0,  1.0},
                        { 0.0, 0.0,  1.0} };
    point3 plane0mm[4]={{ 0.0, 0.0,  0.0},   // X-Z plane -X -Z
                        {-1.0, 0.0,  0.0},
                        {-1.0, 0.0, -1.0},
                        { 0.0, 0.0, -1.0} };

//  The four parts of the Y-Z plane
    point3 plane1pp[4]={{ 0.0,  0.0,  0.0},  // Y-Z plane +Y +Z *
                        { 0.0,  0.0,  1.0},
                        { 0.0,  1.0,  1.0},
                        { 0.0,  1.0,  0.0} };
    point3 plane1pm[4]={{ 0.0,  0.0,  0.0},  // Y-Z plane +Y -Z *
                        { 0.0,  1.0,  0.0},
                        { 0.0,  1.0, -1.0},
                        { 0.0,  0.0, -1.0} };
    point3 plane1mp[4]={{ 0.0,  0.0,  0.0},  // Y-Z plane -Y +Z *
                        { 0.0, -1.0,  0.0},
                        { 0.0, -1.0,  1.0},
                        { 0.0,  0.0,  1.0} };
    point3 plane1mm[4]={{ 0.0,  0.0,  0.0},  // Y-Z plane -Y -Z *
                        { 0.0,  0.0, -1.0},
                        { 0.0, -1.0, -1.0},
                        { 0.0, -1.0,  0.0} };

//  The four parts of the X-Y plane
    point3 plane2pp[4]={{ 0.0,  0.0, 0.0},   // X-Y plane +X +Y
                        { 1.0,  0.0, 0.0},
                        { 1.0,  1.0, 0.0},
                        { 0.0,  1.0, 0.0} };
    point3 plane2pm[4]={{ 0.0,  0.0, 0.0},   // X-Y plane +X -Y
                        { 1.0,  0.0, 0.0},
                        { 1.0, -1.0, 0.0},
                        { 0.0, -1.0, 0.0} };
    point3 plane2mp[4]={{ 0.0,  0.0, 0.0},   // X-Y plane -X +Y
                        {-1.0,  0.0, 0.0},
                        {-1.0,  1.0, 0.0},
                        { 0.0,  1.0, 0.0} };
    point3 plane2mm[4]={{ 0.0,  0.0, 0.0},   // X-Y plane -X -Y
                        {-1.0,  0.0, 0.0},
                        {-1.0, -1.0, 0.0},
                        { 0.0, -1.0, 0.0} };

    GLfloat color0[]={1.0, 0.0, 0.0, 0.5},
    		color1[]={0.0, 1.0, 0.0, 0.5},
            color2[]={0.0, 0.0, 1.0, 0.5};  // R=0, G=1, B=2

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angle, 1.0, 1.0, -1.0); /* rotate model */

//  draw our planes ...
//  negative octant first
    glColor4fv(color2);		// blue
    glBegin(GL_QUADS);		// X-Y plane --
      glVertex3fv(plane2mm[0]);
      glVertex3fv(plane2mm[1]);
      glVertex3fv(plane2mm[2]);
      glVertex3fv(plane2mm[3]);
    glEnd();

    glColor4fv(color1);		// green
    glBegin(GL_QUADS);		// Y-Z plane --
      glVertex3fv(plane1mm[0]);
      glVertex3fv(plane1mm[1]);
      glVertex3fv(plane1mm[2]);
      glVertex3fv(plane1mm[3]);
    glEnd();

    glColor4fv(color0);		// red
    glBegin(GL_QUADS);		// X-Z plane --
      glVertex3fv(plane0mm[0]);
      glVertex3fv(plane0mm[1]);
      glVertex3fv(plane0mm[2]);
      glVertex3fv(plane0mm[3]);
    glEnd();

//  positive-negative parts second
    glColor4fv(color2);		// blue
    glBegin(GL_QUADS);		// X-Y plane --
      glVertex3fv(plane2pm[0]);
      glVertex3fv(plane2pm[1]);
      glVertex3fv(plane2pm[2]);
      glVertex3fv(plane2pm[3]);
    glEnd();

    glColor4fv(color1);		// green
    glBegin(GL_QUADS);		// Y-Z plane --
      glVertex3fv(plane1pm[0]);
      glVertex3fv(plane1pm[1]);
      glVertex3fv(plane1pm[2]);
      glVertex3fv(plane1pm[3]);
    glEnd();

    glColor4fv(color0);		// red
    glBegin(GL_QUADS);		// X-Z plane --
      glVertex3fv(plane0pm[0]);
      glVertex3fv(plane0pm[1]);
      glVertex3fv(plane0pm[2]);
      glVertex3fv(plane0pm[3]);
    glEnd();

//  negative-poxitive parts third
    glColor4fv(color2);		// blue
    glBegin(GL_QUADS);		// X-Y plane --
      glVertex3fv(plane2mp[0]);
      glVertex3fv(plane2mp[1]);
      glVertex3fv(plane2mp[2]);
      glVertex3fv(plane2mp[3]);
    glEnd();

    glColor4fv(color1);		// green
    glBegin(GL_QUADS);		// Y-Z plane --
      glVertex3fv(plane1mp[0]);
      glVertex3fv(plane1mp[1]);
      glVertex3fv(plane1mp[2]);
      glVertex3fv(plane1mp[3]);
    glEnd();

    glColor4fv(color0);		// red
    glBegin(GL_QUADS);		// X-Z plane --
      glVertex3fv(plane0mp[0]);
      glVertex3fv(plane0mp[1]);
      glVertex3fv(plane0mp[2]);
      glVertex3fv(plane0mp[3]);
    glEnd();

//  positive octant last
    glColor4fv(color2);		// blue
    glBegin(GL_QUADS);		// X-Y plane ++
      glVertex3fv(plane2pp[0]);
      glVertex3fv(plane2pp[1]);
      glVertex3fv(plane2pp[2]);
      glVertex3fv(plane2pp[3]);
    glEnd();

    glColor4fv(color1);		// green
    glBegin(GL_QUADS);		// Y-Z plane ++
      glVertex3fv(plane1pp[0]);
      glVertex3fv(plane1pp[1]);
      glVertex3fv(plane1pp[2]);
      glVertex3fv(plane1pp[3]);
    glEnd();

    glColor4fv(color0);		// red
    glBegin(GL_QUADS);		// X-Z plane ++
      glVertex3fv(plane0pp[0]);
      glVertex3fv(plane0pp[1]);
      glVertex3fv(plane0pp[2]);
      glVertex3fv(plane0pp[3]);
    glEnd();

glPopMatrix();  /* undo last rotation you set */
    glutSwapBuffers();
 }

void reshape(int w,int h)
{
        glViewport(0,0,(GLsizei)w,(GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0,1.0,1.0,30.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // View is from first octant, which affects the sequence of our quads above
        //           eye point   center of view       up
        gluLookAt(1.8, 1.8, 1.8, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
        if (key)
        {
           angle += 10.0; /* update angle for rotation in display */
           glutPostRedisplay(); /* perform display again */
}}

int main(int argc, char** argv)
{

/* Standard GLUT initialization */

        glutInit(&argc,argv);
//      initialize for double buffering, RGB color, and depth tests
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("partially transparent planes");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard); // enable keyboard callback

        myinit();
        glutMainLoop();
}