#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graphics.h"
#include "robot.h"
#include "background.h"
#include "Stack.h"

void placeRobot(int x, int y, direction robot_dir, int isCarryingAMarker) {
    foreground();
    clear();
    setColour(isCarryingAMarker ? red : blue);
    int padding = 2;
    x = x+padding;
    y = y+padding;
    int size = grid_size - padding*2;

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
    // sleep(100);
}

direction getInitDirection(char* direction) {
    char direction_c = tolower(direction[0]);
    switch (direction_c) {
        case 'n':
            return north;
        case 'e':
            return east;
        case 's':
            return south;
        case 'w':
            return west;
        default:
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

void checkStartAndResetStack(int robot_x_num, int robot_y_num, direction robot_dir, Stack *step_record, Cell grid[grid_num][grid_num]) {
    for (int i = 0; i < 4; i++) {
        int new_x = robot_x_num + dx[i];
        int new_y = robot_y_num + dy[i];
        if (grid[new_x][new_y].type == start && canPlaceRobot(new_x, new_y)) {
            resetStack(step_record);
            push(step_record, new_x);
            push(step_record, new_y);
            push(step_record, (i + 2) % 4);
            break;
        }
    }
}

void returnToStart(int* robot_x_num, int* robot_y_num, direction* robot_dir, Stack *step_record, Cell grid[grid_num][grid_num]) {
    *robot_dir = (pop(step_record) + 2) % 4;
    int prev_robot_y_num = pop(step_record);
    int prev_robot_x_num = pop(step_record);
    while (!isEmpty(step_record)) {
        *robot_dir = (pop(step_record) + 2) % 4;
        *robot_y_num = pop(step_record);
        *robot_x_num = pop(step_record);
        
        // for (int i = 1; i <= 10; i++) {
        //     float x_diff = grid[robot_x_num][robot_y_num].x - grid[prev_robot_x_num][prev_robot_y_num].x;
        //     float y_diff = grid[robot_x_num][robot_y_num].y - grid[prev_robot_x_num][prev_robot_y_num].y;
        //     placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x+x_diff/10*i, grid[prev_robot_x_num][prev_robot_y_num].y+y_diff/10*i, robot_dir, 1);
        //     sleep(10);
        // }
        prev_robot_y_num = *robot_y_num;
        prev_robot_x_num = *robot_x_num;
        placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir, 1);
        sleep(50);
        checkStartAndResetStack(*robot_x_num, *robot_y_num, *robot_dir, step_record, grid);
    }
}

void updateRobotPosition(int* robot_x_num, int* robot_y_num, direction *robot_dir, Stack *step_record, Cell grid[grid_num][grid_num]) {
    grid[*robot_x_num][*robot_y_num].visited = 1;
    placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir, 0);
    push(step_record, *robot_x_num);
    push(step_record, *robot_y_num);
    push(step_record, *robot_dir);
    sleep(100);
}

int checkForMarker(int* robot_x_num, int* robot_y_num, direction *robot_dir, Cell grid[grid_num][grid_num], Stack *step_record) {
    if (grid[*robot_x_num][*robot_y_num].type == marker) {
        grid[*robot_x_num][*robot_y_num].type = empty;
        drawBackground(grid);
        push(step_record, *robot_x_num);
        push(step_record, *robot_y_num);
        push(step_record, *robot_dir);
        placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir ,1);
        return 1;
    }
    return 0;
}

int exploreBesides(int* robot_x_num, int* robot_y_num, Stack *step_record, Cell grid[grid_num][grid_num], direction *robot_dir, int visited, type type) {
    for (int i = 0; i < 4; i++) {
        int new_x = *robot_x_num + dx[*robot_dir];
        int new_y = *robot_y_num + dy[*robot_dir];
        if (canPlaceRobot(new_x, new_y) && grid[new_x][new_y].visited == visited && grid[new_x][new_y].type == type) {
            if(depth_first_search(&new_x, &new_y, *robot_x_num, *robot_y_num, step_record, grid, robot_dir)) {
                return 1;
            };
        }
        *robot_dir = (*robot_dir + 1) % 4;
    }
    return 0;
}


int depth_first_search(int* robot_x_num, int* robot_y_num, int prev_robot_x_num, int prev_robot_y_num, Stack *step_record, Cell grid[grid_num][grid_num], direction *robot_dir) {
    updateRobotPosition(robot_x_num, robot_y_num, robot_dir, step_record, grid);
    
    // grid[*robot_x_num][*robot_y_num].visited = 1;
    // for (int i = 1; i <= 10; i++) {
    //     float x_diff = grid[*robot_x_num][*robot_y_num].x - grid[prev_robot_x_num][prev_robot_y_num].x;
    //     float y_diff = grid[*robot_x_num][*robot_y_num].y - grid[prev_robot_x_num][prev_robot_y_num].y;
    //     placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x+x_diff/10*i, grid[prev_robot_x_num][prev_robot_y_num].y+y_diff/10*i, *robot_dir, 0);
    //     sleep(10);
    // }

    // placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir, 0);
    push(step_record, *robot_x_num);
    push(step_record, *robot_y_num);
    push(step_record, *robot_dir);

    if (checkForMarker(robot_x_num, robot_y_num, robot_dir, grid, step_record)) {
        return 1;
    }
    
    if (exploreBesides(robot_x_num, robot_y_num, step_record, grid, robot_dir, 0, marker)) { // Find marker around
        return 1;
    }
    
    if (exploreBesides(robot_x_num, robot_y_num, step_record, grid, robot_dir, 0, empty)) { // Explore unvisited empty cell
        return 1;
    }
    *robot_dir = getDirection(*robot_x_num, *robot_y_num, prev_robot_x_num, prev_robot_y_num);
    // for (int i = 1; i <= 10; i++) {
    //     float x_diff = grid[prev_robot_x_num][prev_robot_y_num].x - grid[*robot_x_num][*robot_y_num].x;
    //     float y_diff = grid[prev_robot_x_num][prev_robot_y_num].y - grid[*robot_x_num][*robot_y_num].y;
    //     placeRobot(grid[*robot_x_num][*robot_y_num].x+x_diff/10*i, grid[*robot_x_num][*robot_y_num].x+y_diff/10*i, *robot_dir, 0);
    // }
    // // placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x, grid[prev_robot_x_num][prev_robot_y_num].y, *robot_dir, 0);
    // sleep(100);
    push(step_record, prev_robot_x_num);
    push(step_record, prev_robot_y_num);
    push(step_record, *robot_dir);
    updateRobotPosition(&prev_robot_x_num, &prev_robot_y_num, robot_dir, step_record, grid);
    return 0;
}