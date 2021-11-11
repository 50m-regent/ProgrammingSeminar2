#include <GLUT/glut.h>
#include <math.h>

void init() {
    glClearColor(0, 0, 0, 1);
    gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
}

void renderAxis() {
    glBegin(GL_LINES);

    glColor3d(1, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(1, 0, 0);

    glColor3d(0, 1, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 1, 0);

    glColor3d(0, 0, 1);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 1);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    renderAxis();

    glFlush();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 200.0, w / 200.0, -h / 200, -h / 200, -2, 2);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    init();
    glutMainLoop();
    return 0;
}