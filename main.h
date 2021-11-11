#include <GLUT/glut.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define BG_R 0
#define BG_G 0.5
#define BG_B 0
#define DISK_RADIUS 0.2
#define DISK_DELTA  0.5

void display();
void idle();
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void init(int argc, char *argv[], const unsigned int called_line);