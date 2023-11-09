#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "graphics.h"
#include "Draw.h"
#include "StepStack.h"

const int x_offset = 50;
const int y_offset = 50;
const int grid_size = 50;
const int grid_num = 10;
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

bool isValid(int x_num, int y_num) {
    return (x_num >= 0 && x_num < grid_num && y_num >= 0 && y_num < grid_num);
}

void drawBackground(Cell grid[grid_num][grid_num]) {
    background();
    clear();
    DrawCell(grid);
    DrawGrid(50, 50, grid_size, grid_num);
}

void drawMarkerOnRobot(Cell grid[grid_num][grid_num], int robot_x_num, int robot_y_num) {
    setColour(red);
    //Draw circle marker
    int x = grid[robot_x_num][robot_y_num].x;
    int y = grid[robot_x_num][robot_y_num].y;
    fillOval(x+grid_size/4, y+grid_size/4, grid_size/2, grid_size/2);
    //fillRect(x, y, grid_size, grid_size);
}

void returnToStart(int robot_x_num, int robot_y_num, direction robot_dir, StepStack *step_record, Cell grid[grid_num][grid_num]) {
    int prev_robot_x_num, prev_robot_y_num;
    // drawRobot(grid, robot_x_num, robot_y_num, robot_dir);
    sleep(1000);
    while (!isEmpty(step_record)) {
        robot_dir = (pop(step_record) + 2) % 4;
        robot_y_num = pop(step_record);
        robot_x_num = pop(step_record);
        // robot_dir = getDirection(prev_robot_x_num, prev_robot_y_num, robot_x_num, robot_y_num);
        placeRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir);
        // drawRobot(grid, robot_x_num, robot_y_num, robot_dir);
        prev_robot_x_num = robot_x_num;
        prev_robot_y_num = robot_y_num;
        for (int i = 0; i < 4; i++) {
                int new_x = robot_x_num + dx[i];
                int new_y = robot_y_num + dy[i];
                if (grid[new_x][new_y].type == start && isValid(new_x, new_y)) {
                    resetStack(step_record);
                    push(step_record, new_x);
                    push(step_record, new_y);
                    push(step_record, (i + 2) % 4);
                    printf("Home is found \n");
            }
        }
    }
}

bool depth_first_search(int* robot_x_num, int* robot_y_num, int prev_robot_x_num, int prev_robot_y_num, StepStack *step_record, Cell grid[grid_num][grid_num], direction *robot_dir) {
    grid[*robot_x_num][*robot_y_num].visited = 1;
    
    placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir);
    push(step_record, *robot_x_num);
    push(step_record, *robot_y_num);
    push(step_record, *robot_dir);
    
    if (grid[*robot_x_num][*robot_y_num].type == marker) { // If marker is found
        grid[*robot_x_num][*robot_y_num].type = empty;
        drawBackground(grid);
        placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir);
        return true;
    }
    
    for (int i = 0; i < 4; i++) {
        int new_x = *robot_x_num + dx[i];
        int new_y = *robot_y_num + dy[i];
        if (isValid(new_x, new_y) && grid[new_x][new_y].type == 3) {
            *robot_dir = i;
            if(depth_first_search(&new_x, &new_y, *robot_x_num, *robot_y_num, step_record, grid, robot_dir)) {
                return true;
            };
        }
    }

    for (int i = 0; i < 4; i++) {
        int new_x = *robot_x_num + dx[i];
        int new_y = *robot_y_num + dy[i];
        sleep(100);
        if (isValid(new_x, new_y) && !grid[new_x][new_y].visited) {
            *robot_dir = i;
            // depth_first_search(&new_x, &new_y, *robot_x_num, *robot_y_num, grid, robot_dir);
            if(depth_first_search(&new_x, &new_y, *robot_x_num, *robot_y_num, step_record, grid, robot_dir)) {
                return true;
            };
        }
    }

    *robot_dir = getDirection(*robot_x_num, *robot_y_num, prev_robot_x_num, prev_robot_y_num);
    placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x, grid[prev_robot_x_num][prev_robot_y_num].y, *robot_dir);
    push(step_record, prev_robot_x_num);
    push(step_record, prev_robot_y_num);
    push(step_record, *robot_dir);

    return false;
}

int main(int argc, char **argv) {
    setWindowSize(600, 600);
    
    Cell grid[grid_num][grid_num];
    initCell(grid);

    int robot_x_num = 0;
    int robot_y_num = 0;
    
    // StepStack step_record;
    direction robot_dir = north;

    if (argc == 4) {
        robot_x_num = atoi(argv[1]);
        robot_y_num = atoi(argv[2]);
        robot_dir = getInitDirection(argv[3]);
        grid[atoi(argv[1])][atoi(argv[2])].robot = 1;
        grid[atoi(argv[1])][atoi(argv[2])].type = 2;
    }

    srand(time(NULL));
    int marker_num = rand()%6 + 5;
    int wall_num = rand()%6 + 10;
    GenerateWalls(wall_num, grid);
    GenerateMarkers(marker_num, grid, robot_x_num, robot_y_num);

    drawBackground(grid);
    placeRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir);

    int prev_robot_x_num, prev_robot_y_num;

    while(marker_num > 0) {
        // initStack(&step_record);
        StepStack* step_record = createStack(100);
        depth_first_search(&robot_x_num, &robot_y_num, prev_robot_x_num, prev_robot_y_num, step_record, grid, &robot_dir); //Start DFS
        printf("Marker left: %d\n", marker_num--);
        resetCell(grid);
        returnToStart(robot_x_num, robot_y_num, robot_dir, step_record, grid);
        destroyStack(step_record);
        sleep(1000);
    }
    return 0;
}