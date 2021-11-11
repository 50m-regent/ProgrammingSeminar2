#include "reversi.h"
#include "message.h"
#include "main.h"

unsigned char debug = 0;
Vector board_size;

void board_test() {
    glTranslatef(1, 0, 0);
    for (unsigned short x = 0; x < board_size.x; x++) {
        for (unsigned short y = 0; y < board_size.y; y++) {
            for (unsigned short z = 0; z < board_size.z; z++) {
                if ((x + y + z) % 2) glColor3d(1, 1, 1);
                else                 glColor3d(0, 0, 0);

                gluSphere(gluNewQuadric(), DISK_RADIUS, 32, 32);
                glTranslatef(0, 0, DISK_DELTA);
            }
            glTranslatef(0, DISK_DELTA, -board_size.z * DISK_DELTA);
        }
        glTranslatef(DISK_DELTA, -board_size.y * DISK_DELTA, 0);
    }
    glTranslatef(-board_size.x * DISK_DELTA, 0, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        1, 1, 1,
        0, 0.2, 0.2,
        0, 1, 0
    );

    board_test();

    // if (!count_empty(__LINE__)) if (debug > 0) puts(MES_GAME_END);
/*
    if (!set_placeable(__LINE__)) {
        puts(MES_PASS);
        return;
    }

    if (debug > 0) {
        printf(MES_ANNOUNCE, icons[turn]);
        out();
    }
    
    // flip(get_move());
    
    turn %= 2;
    turn++;
*/

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        -2.0 * w / WINDOW_WIDTH,  2.0 * w / WINDOW_WIDTH,
        -2.0 * h / WINDOW_HEIGHT, 2.0 * h / WINDOW_HEIGHT,
        -2, 2
    );
}

void keyin(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
            glRotated(1, 1, 0, 0);
            glutPostRedisplay();
            break;
		case 's':
            glRotated(1, -1, 0, 0);
            glutPostRedisplay();
            break;
		case 'd':
            glRotated(1, 0, 1, 0);
            glutPostRedisplay();
            break;
		case 'f':
            glRotated(1, 0, -1, 0);
            glutPostRedisplay();
            break;
		case 'h':
            glRotated(1, 0, 0, 1);
            glutPostRedisplay();
            break;
		case 'j':
            glRotated(1, 0, 0, -1);
            glutPostRedisplay();
            break;
		case '\033':
		default:
            break;
	}
}

void init(int argc, char *argv[], const unsigned int called_line) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("3D Reversi");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyin);
    glutIdleFunc(idle);

    glClearColor(BG_R, BG_G, BG_B, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    board_init(__LINE__);
}

int main(int argc, char *argv[]) {
    if (argc > 1) debug = atoi(argv[1]);

    init(argc, argv, __LINE__);
    get_board_size();
    glutMainLoop();
}