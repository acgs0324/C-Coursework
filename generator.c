#include "background.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int besideHome(int, int, Cell [cell_num][cell_num]);

int getReachableCells(int, int, Cell [cell_num][cell_num]);

int canMoveForward(int x_num, int y_num) {
    return (x_num >= 0 && x_num < cell_num && y_num >= 0 && y_num < cell_num);
}

void GenerateCells(int gen_cell_num, type cell_type, Cell grid[cell_num][cell_num], int robot_x, int robot_y) {
    srand(time(NULL));
    int i = 0;
    if (cell_type == marker) {
        getReachableCells(robot_x, robot_y, grid);
    }
    while (i < gen_cell_num) {
        int cell_x = rand()%cell_num;
        int cell_y = rand()%cell_num;

        if (grid[cell_x][cell_y].type == empty && !besideHome(cell_x, cell_y, grid)) {
            if (cell_type == marker && grid[cell_x][cell_y].visited != 1) { //Only check reachability for markers
                continue;
            }
            grid[cell_x][cell_y].type = cell_type;
            i++;
        }
    }
    if (cell_type == marker) {
            resetCellVisit(grid);
    }
}

int getReachableCells(int robot_x_num, int robot_y_num, Cell grid[cell_num][cell_num]) {
    grid[robot_x_num][robot_y_num].visited = 1;
    
    for (int i = 0; i < 4; i++) {
        int new_x = robot_x_num + dx[i];
        int new_y = robot_y_num + dy[i];
        if (canMoveForward(new_x, new_y) && !grid[new_x][new_y].visited && grid[new_x][new_y].type != wall) {
            if (getReachableCells(new_x, new_y, grid)) {
                return 1;
            }
        }
    }
    return 0;
}

int besideHome(int x, int y, Cell grid[cell_num][cell_num]) {

    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (grid[new_x][new_y].type == home && canMoveForward(new_x, new_y)) {
            return 1;
        }
    }
    return 0;
}