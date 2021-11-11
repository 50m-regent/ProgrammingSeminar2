#include <GLUT/glut.h>
#include <math.h>

#define VERTEX_NUM 7
#define ROTATION_SPEED M_PI / 50.0

void display() {
    static double rotation, dt = 4.0 * M_PI / (double)VERTEX_NUM;
    double x, y, theta = rotation;
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0, 0, 0);

    glBegin(GL_LINES);
    for (i = 0; i < VERTEX_NUM * 2; i++, theta += dt) {
        x = cos(theta);
        y = sin(theta);

        glVertex2d(x, y);
    }

    glEnd();
    glutSwapBuffers();

    rotation += ROTATION_SPEED;
}

void idle() {
    glutPostRedisplay();
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
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 0);

    glutMainLoop();
    return 0;
}