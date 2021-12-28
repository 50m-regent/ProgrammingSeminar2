#ifndef MAIN_H
#define MAIN_H

#include <GLUT/glut.h>
#include <math.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define BG_R 0.3
#define BG_G 0.8
#define BG_B 0.3
#define DISK_RADIUS 0.2
#define DISK_SLICE 32
#define DISK_DELTA  0.5
#define PLACEABLE_RADIUS 0.05
#define STRIDE 0.1
#define AXIS_WIDTH 0.05
#define AXIS_R 0.6
#define AXIS_G 0.6
#define AXIS_B 0.6

unsigned turn = 1;
unsigned char debug = 1, *board, is_end = 0;
Vector board_size;
static GLdouble eyeX = 0, eyeY = 0, eyeZ = 0;

void render_axis();
void render_board();
void render_ui();
void display();
void idle();
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void init(int argc, char *argv[], const unsigned int called_line);

#endif