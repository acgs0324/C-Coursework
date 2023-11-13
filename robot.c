#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graphics.h"
#include "robot.h"
#include "background.h"
#include "Stack.h"

int isCarryingAMarker(robot robot) {
    return robot.isCarryingAMarker == 1;
}

void displayRobot(robot robot, Cell grid[grid_num][grid_num]) {
    foreground();
    clear();
    setColour(isCarryingAMarker(robot) ? red : blue);
    int padding = 2;
    int x = grid[robot.x_num][robot.y_num].x + padding;
    int y = grid[robot.x_num][robot.y_num].y + padding;
    int size = grid_size - padding*2;
    switch (robot.dir)  {
    case north: 
        fillPolygon(3, (int[]){x, x+size/2, x+size}, (int[]){y+size, y, y+size});
        break;
    case east: 
        fillPolygon(3, (int[]){x, x+size, x}, (int[]){y, y+size/2, y+size});
        break;
    case south: 
        fillPolygon(3, (int[]){x, x+size/2, x+size}, (int[]){y, y+size, y});
        break;
    case west: 
        fillPolygon(3, (int[]){x+size, x, x+size}, (int[]){y, y+size/2, y+size});
        break;
    }
}

void forward(robot robot, Stack *step_record, Cell grid[grid_num][grid_num]) {
    grid[robot.x_num][robot.y_num].visited = 1;
    displayRobot(robot, grid);
    sleep(100);
    push(step_record, robot.x_num);
    push(step_record, robot.y_num);
    push(step_record, robot.dir);
}

void left(robot* robot, Cell grid[grid_num][grid_num], Stack *step_record) {
    sleep(100);
    robot->dir = (robot->dir + 3) % 4;
    push(step_record, robot->x_num);
    push(step_record, robot->y_num);
    push(step_record, robot->dir);
    displayRobot(*robot, grid);
    sleep(100);
}

void right(robot* robot, Cell grid[grid_num][grid_num], Stack *step_record) {
    sleep(100);
    robot->dir = (robot->dir + 1) % 4;
    push(step_record, robot->x_num);
    push(step_record, robot->y_num);
    push(step_record, robot->dir);
    displayRobot(*robot, grid);
    sleep(100);
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

void changeDirection(direction prev_robot_dir, direction robot_dir, robot* robot, Cell grid[grid_num][grid_num], Stack *step_record) {
    if (robot_dir == (prev_robot_dir + 1) % 4) {
        right(robot, grid, step_record);
    } else if (robot_dir == (prev_robot_dir + 3) % 4) {
        left(robot, grid, step_record);
    } else if (robot_dir == (prev_robot_dir + 2) % 4) {
        right(robot, grid, step_record);
        right(robot, grid, step_record);
    }
}

direction getDirection(int prev_robot_x_num, int prev_robot_y_num, int robot_x_num, int robot_y_num) {
    if (prev_robot_x_num < robot_x_num) {
        return east; 
    } else if (prev_robot_x_num > robot_x_num) {
        return west; 
    } else if (prev_robot_y_num < robot_y_num) {
        return south;
    } else {
        return north;
    }
}

int atHome(int robot_x_num, int robot_y_num, Cell grid[grid_num][grid_num]) {
    return grid[robot_x_num][robot_y_num].type == start;
}

int atMarker(robot robot, Cell grid[grid_num][grid_num]) {
    return grid[robot.x_num][robot.y_num].type == marker;
}

void pickUpMarker(robot* robot, Cell grid[grid_num][grid_num]) {
    grid[robot->x_num][robot->y_num].type = empty;
    robot->isCarryingAMarker = 1;
    drawBackground(grid);
    displayRobot(*robot, grid);
}

void dropMarker(robot* robot, Cell grid[grid_num][grid_num]) {
    sleep(200);
    robot->isCarryingAMarker = 0;
    displayRobot(*robot, grid);
}

void checkStartAndResetStack(robot robot, Stack *step_record, Cell grid[grid_num][grid_num]) {
    for (int i = 0; i < 4; i++) {
        int new_x = robot.x_num + dx[i];
        int new_y = robot.y_num + dy[i];
        if (atHome(new_x, new_y, grid) && canMoveForward(new_x, new_y)) {
            resetStack(step_record);
            push(step_record, new_x);
            push(step_record, new_y);
            push(step_record, (i + 2) % 4);
            break;
        }
    }
}

void returnToStart(robot* robot, Stack *step_record, Cell grid[grid_num][grid_num]) {
    robot->dir = (pop(step_record) + 2) % 4;
    int prev_robot_y_num = pop(step_record);
    int prev_robot_x_num = pop(step_record);
    while (!isEmpty(step_record)) {
        robot->dir = (pop(step_record) + 2) % 4;
        robot->y_num = pop(step_record);
        robot->x_num = pop(step_record);

        prev_robot_y_num = robot->y_num;
        prev_robot_x_num = robot->x_num;
        displayRobot(*robot, grid);
        sleep(100);
        checkStartAndResetStack(*robot, step_record, grid);
    }
}

int exploreBesides(robot* robot, Stack *step_record, Cell grid[grid_num][grid_num], type type) {
    direction prev_robot_dir = robot->dir;
    for (int i = 0; i < 4; i++) {
        int new_x = robot->x_num + dx[i];
        int new_y = robot->y_num + dy[i];
        if (canMoveForward(new_x, new_y) && grid[new_x][new_y].visited == 0 && grid[new_x][new_y].type == type) {
            if (i != robot->dir) {
                changeDirection(robot->dir, i, robot, grid, step_record);
            }
            int prev_robot_x_num = robot->x_num;
            int prev_robot_y_num = robot->y_num;
            robot->x_num = new_x;
            robot->y_num = new_y;
            if(depth_first_search(robot, prev_robot_x_num, prev_robot_y_num, step_record, grid)) {
                return 1;
            };
        }
    }
    return 0;
}

int depth_first_search(robot* robot, int prev_robot_x_num, int prev_robot_y_num, Stack *step_record, Cell grid[grid_num][grid_num]) {
    
    forward(*robot, step_record, grid);

    if (atMarker(*robot, grid)) {
        return 1;
    }
    
    if (exploreBesides(robot, step_record, grid, marker)) { 
        return 1;
    }
    
    if (exploreBesides(robot, step_record, grid, empty)) {
        return 1;
    }

    direction prev_robot_dir = robot->dir;
    direction robot_dir = getDirection(robot->x_num, robot->y_num, prev_robot_x_num, prev_robot_y_num);
    if (robot_dir != prev_robot_dir) {
        changeDirection(prev_robot_dir, robot_dir, robot, grid, step_record);
    }
    robot->x_num = prev_robot_x_num;
    robot->y_num = prev_robot_y_num;

    forward(*robot, step_record, grid);
    return 0;
}