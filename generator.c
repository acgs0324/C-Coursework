#include "background.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int besideStart(int, int, Cell [grid_num][grid_num]);

int checkReachable(int, int, int, int, Cell [grid_num][grid_num]);

int canPlaceRobot(int x_num, int y_num) {
    return (x_num >= 0 && x_num < grid_num && y_num >= 0 && y_num < grid_num);
}

void GenerateCells(int cell_num, type cell_type, Cell grid[grid_num][grid_num], int robot_x, int robot_y) { //Generate walls or markers
    srand(time(NULL));
    int i = 0;
    while (i < cell_num) {
        int cell_x = rand()%grid_num;
        int cell_y = rand()%grid_num;

        if (grid[cell_x][cell_y].type == empty && !besideStart(cell_x, cell_y, grid)) {
            if (cell_type == marker && !checkReachable(robot_x, robot_y, cell_x, cell_y, grid)) {
                continue;
            }
            grid[cell_x][cell_y].type = cell_type;
            i++;
        }
        if (cell_type == marker) {
            resetCellVisit(grid);
        }
    }
}

int checkReachable(int robot_x_num, int robot_y_num, int marker_x, int marker_y, Cell grid[grid_num][grid_num]) {
    grid[robot_x_num][robot_y_num].visited = 1;
    
    if (robot_x_num == marker_x && robot_y_num == marker_y) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        int new_x = robot_x_num + dx[i];
        int new_y = robot_y_num + dy[i];
        if (canPlaceRobot(new_x, new_y) && !grid[new_x][new_y].visited && grid[new_x][new_y].type != wall) {
            if (checkReachable(new_x, new_y, marker_x, marker_y, grid)) {
                return 1;
            }
        }
    }
    return 0;
}

int besideStart(int x, int y, Cell grid[grid_num][grid_num]) {

    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (grid[new_x][new_y].type == start && canPlaceRobot(new_x, new_y)) {
            return 1;
        }
    }
    return 0;
}