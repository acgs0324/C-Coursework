#include "Draw.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void placeRobot(int x, int y, direction robot_dir) {
    foreground();
    clear();
    setColour(blue);
    x = x+2;
    y = y+2;
    int size = grid_size - 4;
    switch (robot_dir)  {
    case north: //north
        fillPolygon(3, (int[]){x, x+size/2, x+size}, (int[]){y+size, y, y+size});
        break;
    case east: //east
        fillPolygon(3, (int[]){x, x+size, x}, (int[]){y, y+size/2, y+size});
        break;
    case south: //south
        fillPolygon(3, (int[]){x, x+size/2, x+size}, (int[]){y, y+size, y});
        break;
    case west: //west
        fillPolygon(3, (int[]){x+size, x, x+size}, (int[]){y, y+size/2, y+size});
        break;
    }
    sleep(100);
}

direction initdirection(char* direction) {
    char direction_c = tolower(direction[0]);
    if (direction_c == 'n') {
        return north;
    } else if (direction_c == 'e') {
        return east;
    } else if (direction_c == 's') {
        return south;
    } else if (direction_c == 'w') {
        return west;
    } else {
        printf("Invalid direction\n");
        exit(1);
    }
}

direction getDirection(int prev_robot_x_num, int prev_robot_y_num, int robot_x_num, int robot_y_num) {
    if (prev_robot_x_num < robot_x_num) {
        return east; // Right
    } else if (prev_robot_x_num > robot_x_num) {
        return west; // Left
    } else if (prev_robot_y_num < robot_y_num) {
        return south; // Down
    } else {
        return north; // Up
    }
}