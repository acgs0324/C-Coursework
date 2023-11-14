#ifndef ROBOT_H
#define ROBOT_H

#include "background.h"
#include "stack.h"

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

void displayRobot(robot, Cell [cell_num][cell_num]);
void pickUpMarker(robot*, Cell [cell_num][cell_num]);
void dropMarker(robot*, Cell [cell_num][cell_num]);
direction getInitDirection(char* );
direction getDirection(int, int, int, int);
void returnToHome(robot*, Stack *, Cell [cell_num][cell_num]);
int depth_first_search(robot*, int, int, Stack *, Cell [cell_num][cell_num]);

#endif