#include <GLUT/glut.h>
#include <math.h>

void drawAxis() {
    double x, y;

    glBegin(GL_LINES);
    glVertex2d(-0.5, 0);
    glVertex2d(3, 0);
    glVertex2d(0, -1.5);
    glVertex2d(0, 1.5);
    for (x = 0; x < 3; x++) {
        glVertex2d(x, -0.05);
        glVertex2d(x, 0.05);
    }
    for (y = -1; y < 1.5; y += 0.5) {
        glVertex2d(-0.05, y);
        glVertex2d(0.05, y);
    }
    glEnd();
}

void drawCardioid() {
    double x, y, theta;

    glBegin(GL_LINE_STRIP);
    for (theta = 0; theta < 2 * M_PI; theta += 0.01) {
        x = cos(theta) * (1 + cos(theta));
        y = sin(theta) * (1 + cos(theta));

        glVertex2d(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0, 0, 0);

    drawAxis();
    drawCardioid();

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 3.5, -2, 2, -1, 1);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(450, 400);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 0);

    glutMainLoop();
    return 0;
}