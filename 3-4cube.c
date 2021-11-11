#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

GLdouble vP[8][3] = {
    {-0.577, -0.577, 0.577},
    {0.577, -0.577, 0.577},
    {0.577, -0.577, -0.577},
    {-0.577, -0.577, -0.577},
    {-0.577, 0.577, 0.577},
    {0.577, 0.577, 0.577},
    {0.577, 0.577, -0.577},
    {-0.577, 0.577, -0.577}
};
int tP[6][4] = {
    {3, 2, 1, 0},
    {0, 1, 5, 4},
    {1, 2, 6, 5},
    {4, 5, 6, 7},
    {3, 7, 6, 2},
    {0, 4, 7, 3}
};

void display() {
    int i,j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_QUADS);
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            glColor3d(0, 0, 0);
            glNormal3dv(vP[tP[i][j]]);
            glVertex3dv(vP[tP[i][j]]);
        }
    }
    glEnd();

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 400.0, w / 400.0, -h / 400.0, h / 400.0, -3, 3);
}

void init() {
    glClearColor(1, 1, 1, 0);
    // gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
}

void keyin(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a': glRotated(1, 1, 0, 0);glutPostRedisplay();break;
		case 's': glRotated(1, -1, 0, 0);glutPostRedisplay();break;
		case 'd': glRotated(1, 0, 1, 0);glutPostRedisplay();break;
		case 'f': glRotated(1, 0, -1, 0);glutPostRedisplay();break;
		case 'h': glRotated(1, 0, 0, 1);glutPostRedisplay();break;
		case 'j': glRotated(1, 0, 0, -1);glutPostRedisplay();break;
		case '\033':
		default: break;
	}
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyin);

    init();

    glutMainLoop();
    return 0;
}