#include <GLUT/glut.h>

int theta = 0, phi = 0, psi = 0, rotateTheta = 0, rotatePhi = 0, rotatePsi = 0;

void rotate() {
    if (rotateTheta) theta++;
	glRotatef(theta, 1, 0, 0);
    if (rotatePhi) phi++;
	glRotatef(phi, 0, 1, 0);
    if (rotatePsi) psi++;
    glRotatef(psi, 0, 0, 1);
}

void renderTeapot() {
	glutSolidTeapot(0.5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    rotate();
    glutSolidDodecahedron();

	glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void key(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
            rotateTheta = 1 - rotateTheta;
            break;
        case 'y':
            rotatePhi = 1 - rotatePhi;
            break;
        case 'z':
            rotatePsi = 1 - rotatePsi;
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_DEPTH_TEST);

    // glEnable(GL_LIGHTING);

    GLfloat lP0[] = {-1, 1, -1, 1}, lC0[]= {1, 1, 1, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lP0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lC0);
    glEnable(GL_LIGHT0);

    gluLookAt(0, 0, -5, 0, 0, 1, 0, 1, 0);
    glOrtho(-5, 5, -5, 5, -5, 5);
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (h > w) {
        glOrtho(-1, 1, -(double)h / w, (double)h / w, -1, 1);
    } else {
        glOrtho(-(double)w / h, (double)w / h, -1, 1, -1, 1);
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("");

	init();
  
	glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}