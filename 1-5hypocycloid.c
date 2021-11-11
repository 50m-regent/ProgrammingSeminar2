#include <GLUT/glut.h>
#include <math.h>

void drawAxis() {
    double x, y;

    glBegin(GL_LINES);
    glVertex2d(-1.5, 0);
    glVertex2d(1.5, 0);
    glVertex2d(0, -1.5);
    glVertex2d(0, 1.5);
    for (x = -1; x < 1.5; x += 0.5) {
        glVertex2d(x, -0.05);
        glVertex2d(x, 0.05);
        
        y = x;
        glVertex2d(-0.05, y);
        glVertex2d(0.05, y);
    }
    glEnd();
}

void drawHypocycloid() {
    double x, y, theta;

    glBegin(GL_LINE_STRIP);
    for (theta = 0; theta < 2 * M_PI; theta += 0.01) {
        x = cos(theta);
        x = x * x * x;
        y = sin(theta);
        y = y * y * y;

        glVertex2d(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0, 0, 0);

    drawAxis();
    drawHypocycloid();

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -1, 1);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 0);

    glutMainLoop();
    return 0;
}