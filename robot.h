#ifndef ROBOT_H
#define ROBOT_H

#include "background.h"
#include "Stack.h"

typedef enum {
    north = 0,
    east = 1,
    south = 2,
    west = 3
} direction;

void placeRobot(int, int, direction, int);
direction getInitDirection(char* );
direction getDirection(int, int, int, int);
void returnToStart(int*, int*, direction*, Stack *, Cell [grid_num][grid_num]);
int depth_first_search(int *, int *, int, int, Stack *, Cell [grid_num][grid_num], direction *);

#endif