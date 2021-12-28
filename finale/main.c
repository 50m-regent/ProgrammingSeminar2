#include "reversi.h"
#include "message.h"
#include "main.h"

void render_axis() {
    for (unsigned short x = 0; x < board_size.x; x++) {
        for (unsigned short y = 0; y < board_size.y; y++) {
            glLineWidth(AXIS_WIDTH);
            glColor3d(AXIS_R, AXIS_G, AXIS_B);
            glBegin(GL_LINE_STRIP);
                glVertex3d(DISK_DELTA * x, DISK_DELTA * y, 0);
                glVertex3d(DISK_DELTA * x, DISK_DELTA * y, DISK_DELTA * (board_size.z - 1));
            glEnd();
        }
    }

    for (unsigned short y = 0; y < board_size.y; y++) {
        for (unsigned short z = 0; z < board_size.z; z++) {
            glLineWidth(AXIS_WIDTH);
            glColor3d(AXIS_R, AXIS_G, AXIS_B);
            glBegin(GL_LINE_STRIP);
                glVertex3d(0, DISK_DELTA * y, DISK_DELTA * z);
                glVertex3d(DISK_DELTA * (board_size.x - 1), DISK_DELTA * y, DISK_DELTA * z);
            glEnd();
        }
    }

    for (unsigned short z = 0; z < board_size.z; z++) {
        for (unsigned short x = 0; x < board_size.x; x++) {
            glLineWidth(AXIS_WIDTH);
            glColor3d(AXIS_R, AXIS_G, AXIS_B);
            glBegin(GL_LINE_STRIP);
                glVertex3d(DISK_DELTA * x, 0, DISK_DELTA * z);
                glVertex3d(DISK_DELTA * x, DISK_DELTA * (board_size.y - 1), DISK_DELTA * z);
            glEnd();
        }
    }
}

void render_board() {
    for (unsigned short x = 0; x < board_size.x; x++) {
        for (unsigned short y = 0; y < board_size.y; y++) {
            for (unsigned short z = 0; z < board_size.z; z++) {
                switch (board[vec2i((Vector){x, y, z}, __LINE__)]) {
                    case BLACK:
                        glColor3d(0, 0, 0);
                        gluSphere(gluNewQuadric(), DISK_RADIUS, DISK_SLICE, DISK_SLICE);
                        break;
                    case WHITE:
                        glColor3d(1, 1, 1);
                        gluSphere(gluNewQuadric(), DISK_RADIUS, DISK_SLICE, DISK_SLICE);
                        break;
                    case PLACEABLE:
                        glColor3d(1, 1, 0);
                        gluSphere(gluNewQuadric(), PLACEABLE_RADIUS, DISK_SLICE, DISK_SLICE);
                        break;
                    case NONE:
                    default:
                        break;
                }
                glTranslatef(0, 0, DISK_DELTA);
            }
            glTranslatef(0, DISK_DELTA, -board_size.z * DISK_DELTA);
        }
        glTranslatef(DISK_DELTA, -board_size.y * DISK_DELTA, 0);
    }
    glTranslatef(-board_size.x * DISK_DELTA, 0, 0);
}

void render_ui() {
    glRasterPos2d(0, 0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        eyeX, eyeY, eyeZ,
        DISK_DELTA * board_size.x / 2.0, DISK_DELTA * board_size.y / 2.0, DISK_DELTA * board_size.z / 2.0,
        0, 1, 0
    );
    
    render_axis();
    render_board();
    render_ui();

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
        -4.0 * w / WINDOW_WIDTH,  4.0 * w / WINDOW_WIDTH,
        -4.0 * h / WINDOW_HEIGHT, 4.0 * h / WINDOW_HEIGHT,
        0, 10
    );
}

void keyin(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
            eyeX += STRIDE;
            glutPostRedisplay();
            break;
		case 's':
            eyeX -= STRIDE;
            glutPostRedisplay();
            break;
		case 'd':
            eyeY += STRIDE;
            glutPostRedisplay();
            break;
		case 'f':
            eyeY += STRIDE;
            glutPostRedisplay();
            break;
		case 'h':
            eyeZ += STRIDE;
            glutPostRedisplay();
            break;
		case 'j':
            eyeZ += STRIDE;
            glutPostRedisplay();
            break;
        case 'g':
            flip(get_move());
        
            turn %= 2;
            turn++;

            if (!set_placeable(__LINE__)) {
                puts(MES_PASS);
                turn %= 2;
                turn++;

                if (!set_placeable(__LINE__)) {
                    is_end = 1;
                    if (debug > 0) puts(MES_GAME_END);
                }
            }

            if (debug > 0) {
                printf(MES_ANNOUNCE, icons[turn]);
                out();
            }
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
    if (debug > 0) {
        printf(MES_ANNOUNCE, icons[turn]);
        out();
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) debug = atoi(argv[1]);

    get_board_size();
    init(argc, argv, __LINE__);
    glutMainLoop();
}