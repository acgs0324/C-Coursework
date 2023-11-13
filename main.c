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

    robot robot;
    robot.x_num = 0;
    robot.y_num = 0;
    robot.dir = north;
    robot.isCarryingAMarker = 0;
    
    if (argc == 4) {
        robot.x_num = atoi(argv[1]);
        robot.y_num = atoi(argv[2]);
        robot.dir = getInitDirection(argv[3]);
        grid[atoi(argv[1])][atoi(argv[2])].type = 2;
    }

    srand(time(NULL));
    int wall_num = rand()%6 + 15;
    int marker_num = rand()%3 + 3;

    GenerateCells(wall_num, wall, grid, robot.x_num, robot.y_num);
    GenerateCells(marker_num, marker, grid, robot.x_num, robot.y_num);

    drawBackground(grid);
    displayRobot(robot, grid);
    sleep(500);
    
    int prev_robot_x_num = robot.x_num;
    int prev_robot_y_num = robot.y_num;
    while(marker_num > 0) { 
        robot.x_num = prev_robot_x_num;
        robot.y_num = prev_robot_y_num;
        Stack* step_record = createStack(100);
        depth_first_search(&robot, prev_robot_x_num, prev_robot_y_num, step_record, grid);
        marker_num--;
        pickUpMarker(&robot, grid);
        resetCellVisit(grid);
        sleep(300);
        returnToHome(&robot, step_record, grid);
        dropMarker(&robot, grid);
        sleep(1000);
        destroyStack(step_record);
    }
    return 0;
}