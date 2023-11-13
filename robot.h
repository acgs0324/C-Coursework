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

typedef struct {
    int x_num;
    int y_num;
    direction dir;
    int isCarryingAMarker;
} robot;

void displayRobot(robot, Cell [grid_num][grid_num]);
void pickUpMarker(robot*, Cell [grid_num][grid_num]);
void dropMarker(robot*, Cell [grid_num][grid_num]);
direction getInitDirection(char* );
direction getDirection(int, int, int, int);
void returnToStart(robot*, Stack *, Cell [grid_num][grid_num]);
int depth_first_search(robot*, int, int, Stack *, Cell [grid_num][grid_num]);

#endif