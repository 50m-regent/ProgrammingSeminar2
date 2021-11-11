#include <GLUT/glut.h>
#include <math.h>

void drawAxis() {
    double x, y;

    glBegin(GL_LINES);
    glVertex2d(-0.5, 0);
    glVertex2d(2 * M_PI + 0.5, 0);
    glVertex2d(0, -0.5);
    glVertex2d(0, 2.5);
    for (x = 0; x < 2.5; x += 0.5) {
        glVertex2d(x * M_PI, -0.05);
        glVertex2d(x * M_PI, 0.05);
    }
    for (y = 0; y < 3; y ++) {
        glVertex2d(-0.05, y);
        glVertex2d(0.05, y);
    }
    glEnd();
}

void drawCycloid() {
    double x, y, theta;

    glBegin(GL_LINE_STRIP);
    for (theta = 0; theta < 2 * M_PI; theta += 0.01) {
        x = theta - sin(theta);
        y = 1 - cos(theta);

        glVertex2d(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0, 0, 0);

    drawAxis();
    drawCycloid();

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 8, -1, 3, -1, 1);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(900, 400);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 0);

    glutMainLoop();
    return 0;
}