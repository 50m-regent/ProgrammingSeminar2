#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define ID_B 1
#define ID_L 2
#define ID_U 3
#define RADIUS_B 0.5
#define HEIGHT_B 0.3
#define SLICES_B 10
#define STACKS_B 4
#define WIDTH_L  0.2
#define HEIGHT_L 0.8
#define WIDTH_U  0.2
#define HEIGHT_U 0.5
#define BASE_SPEED 4
#define LOWER_SPEED 2
#define UPPER_SPEED 3
#define AMP 100

GLfloat rotAng[3] = {0, 30, 60};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1,1,1, 0,0,0, 0,1,0);

    glRotated(rotAng[0], 0, 1, 0);
    glCallList(ID_B);
    glTranslated(HEIGHT_B * sin(rotAng[1]), HEIGHT_B, 0);
    glRotated(rotAng[1], 0, 0, 1);
    glCallList(ID_L);
    glTranslated(0, HEIGHT_L, 0);
    glRotated(rotAng[2], 0, 0, 1);
    glCallList(ID_U);

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -4, 4);
}

void base() {
    glNewList(ID_B, GL_COMPILE);
    glColor3d(0, 0, 0);
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    GLUquadric *quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluCylinder(quad, RADIUS_B, RADIUS_B, HEIGHT_B, SLICES_B, STACKS_B);
    glPopMatrix();
    glEndList();
}

void lower_arm() {
    glNewList(ID_L, GL_COMPILE);
    glColor3d(0, 0, 0);
    glPushMatrix();
    glScalef(WIDTH_L, HEIGHT_L, WIDTH_L);
    glutSolidCube(1);
    glPopMatrix();
    glEndList();
}

void upper_arm() {
    glNewList(ID_U, GL_COMPILE);
    glColor3d(0, 0, 0);
    glPushMatrix();
    glTranslatef(-0.5 * HEIGHT_U, 0, 0);
    glScalef(WIDTH_U, HEIGHT_U, WIDTH_U);
    glutSolidCube(1);
    glPopMatrix();
    glEndList();
}

void init() {
    base();
    lower_arm();
    upper_arm();

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);

    init();

    glutMainLoop();
    return 0;
}