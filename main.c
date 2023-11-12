#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "graphics.h"
#include "background.h"
#include "Stack.h"
#include "robot.h"

const int grid_size = 60;
const int grid_num = 10;
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

int main(int argc, char **argv) {
    setWindowSize(grid_size*(grid_num+2), grid_size*(grid_num+2));
    
    Cell grid[grid_num][grid_num];
    initCell(grid);

    int robot_x_num = 0;
    int robot_y_num = 0;
    direction robot_dir = north;
    
    if (argc == 4) {
        robot_x_num = atoi(argv[1]);
        robot_y_num = atoi(argv[2]);
        robot_dir = getInitDirection(argv[3]);
        grid[atoi(argv[1])][atoi(argv[2])].type = 2;
    }

    srand(time(NULL));
    int wall_num = rand()%6 + 15;
    int marker_num = rand()%6 + 7;

    GenerateCells(wall_num, wall, grid, robot_x_num, robot_y_num);
    GenerateCells(marker_num, marker, grid, robot_x_num, robot_y_num);

    drawBackground(grid);
    placeRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, 0);
    sleep(500);
    
    int prev_robot_x_num = robot_x_num;
    int prev_robot_y_num = robot_y_num;
    while(marker_num > 0) {
        Stack* step_record = createStack(100);
        if(depth_first_search(&robot_x_num, &robot_y_num, prev_robot_x_num, prev_robot_y_num, step_record, grid, &robot_dir)) { //Start DFS
            printf("Marker left: %d\n", --marker_num);
        } else {
            printf("No marker found\n");
        }
        resetCellVisit(grid);
        sleep(300);
        returnToStart(&robot_x_num, &robot_y_num, &robot_dir, step_record, grid);
        sleep(1000);
        destroyStack(step_record);
    }
    return 0;
}