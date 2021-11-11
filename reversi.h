#ifndef REVERSI_H
#define REVERSI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

static char *icons[] = {" ", "○", "●", "."}; // icons presenting each player and placeable cells

enum {
    NONE,
    BLACK,
    WHITE
}; // turn number of each player

static unsigned turn = 1; // 1: black, 2: white
static unsigned char *board;
extern unsigned char debug; // print logs if true.

static Dl_info info; // for logging

typedef struct {
    short x, y, z;
} Vector; // Vector struct

static const Vector DELTAS[27] = {
    {-1, -1, -1}, { 0, -1, -1}, { 1, -1, -1},
    {-1, -1,  0}, { 0, -1,  0}, { 1, -1,  0},
    {-1, -1,  1}, { 0, -1,  1}, { 1, -1,  1},
    {-1,  0, -1}, { 0,  0, -1}, { 1,  0, -1},
    {-1,  0,  0}, { 0,  0,  0}, { 1,  0,  0},
    {-1,  0,  1}, { 0,  0,  1}, { 1,  0,  1},
    {-1,  1, -1}, { 0,  1, -1}, { 1,  1, -1},
    {-1,  1,  0}, { 0,  1,  0}, { 1,  1,  0},
    {-1,  1,  1}, { 0,  1,  1}, { 1,  1,  1}
}; // Neighborhood vectors for searching.
extern Vector board_size;

// Add two vectors.
static inline const Vector vector_sum(
    const Vector v1,
    const Vector v2,
    const unsigned int called_line // The line number calls this function
); // Return: The sum of vectors.

// Calculate index from vector.
static inline const int vec2i(
    const Vector v,
    const unsigned int called_line // The line number calls this function
); // Return: index

// Get board size with standard input.
void get_board_size();

// Initialize board.
void board_init(
    const unsigned int called_line // The line number calls this function
);

// Count empty cells
const unsigned count_empty(
    const unsigned int called_line // The line number calls this function
); // Return: Amount of empty cells.

// Search the board for one direction.
const unsigned char search(
    const Vector now,        // The cell searching now.
    const Vector delta,      // The direction of searching.
    const unsigned char flip // Flip disks while searching if true.
); // Return: True if there is a player's cell in the direction.

// Check if the cell is placeable or not.
const unsigned char is_placeable(
    const Vector cell,
    const unsigned int called_line // The line number calls this function
); // Return: True if the cell is placeable, else false.

// Set placeable cells' number to 3
const unsigned set_placeable(
    const unsigned int called_line // The line number calls this function
); // Return: The amount of placeable cells.

// Game outputs
void out();

// Get next move
const Vector get_move(); // Return: Vector of the move

// Flip the disks.
void flip(
    const Vector move
);

// Run the game.
void play(
    const unsigned int called_line // The line number calls this function
);

#endif