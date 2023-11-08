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

typedef enum {
    north = 0,
    east = 1,
    south = 2,
    west = 3
} direction;


bool isValid(int x_num, int y_num) {
    return (x_num >= 0 && x_num < grid_num && y_num >= 0 && y_num < grid_num);
}

void PlaceRobot(int x, int y, direction robot_dir) {
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

bool depth_first_search(int* robot_x_num, int* robot_y_num, int prev_robot_x_num, int prev_robot_y_num, StepStack *step_record, Cell grid[grid_num][grid_num], direction *robot_dir) {
    //sleep(100);
    // printf("robot_x: %d, robot_y: %d\n", *robot_x_num, *robot_y_num);
    grid[*robot_x_num][*robot_y_num].visited = 1;
    clear();
    DrawCell(grid);
    DrawGrid(50, 50, grid_size, grid_num);
    PlaceRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir);
    push(step_record, *robot_x_num);
    push(step_record, *robot_y_num);
    if (grid[*robot_x_num][*robot_y_num].type == 3) {
        grid[*robot_x_num][*robot_y_num].type = 0;
        clear();
        DrawCell(grid);
        DrawGrid(50, 50, grid_size, grid_num);
        PlaceRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir);
        sleep(1000);
        for (int i = 0; i < grid_num; i++) {
            for (int j = 0; j < grid_num; j++) {
                // if(grid[i][j].visited == 1 && grid[i][j].type != 1) {
                //     grid[i][j].visited = 0;
                // } else {
                //     grid[i][j].visited = 1;
                // }
                grid[i][j].visited = 1;
            }
        }
        return true;
    }

    // Define the 4 possible movement directions (north, east, south, west)
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    
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
        // clear();
        // DrawCell(grid_num, grid_size, grid);
        // DrawGrid(50, 50, grid_size, grid_num);
        // PlaceRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir, grid_size);
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
    *robot_dir = getDirection(prev_robot_x_num, prev_robot_y_num, *robot_x_num, *robot_y_num);
    *robot_dir = (*robot_dir + 2) % 4;
    clear();
    DrawCell(grid);
    DrawGrid(50, 50, grid_size, grid_num);
    PlaceRobot(grid[prev_robot_x_num][prev_robot_y_num].x, grid[prev_robot_x_num][prev_robot_y_num].y, *robot_dir);
    push(step_record, prev_robot_x_num);
    push(step_record, prev_robot_y_num);
    // printf("Move from (%d, %d) to (%d, %d)\n", prev_robot_x_num, prev_robot_y_num, *robot_x_num, *robot_y_num);
    return false;
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

int main(int argc, char **argv) {
    setWindowSize(600, 600);
    
    Cell grid[grid_num][grid_num];
    resetCell(grid);
    int robot_x_num = 0;
    int robot_y_num = 0;
    direction robot_dir = north;

    if (argc == 4) {
        robot_x_num = atoi(argv[1]);
        robot_y_num = atoi(argv[2]);
        robot_dir = initdirection(argv[3]);
        grid[atoi(argv[1])][atoi(argv[2])].robot = 1;
        grid[atoi(argv[1])][atoi(argv[2])].type = 2;
    }

    srand(time(NULL));

    int marker_num = rand()%6+3;
    // int marker_x[marker_num], marker_y[marker_num];
    int wall_num = rand()%10+5;
    // int wall_x[wall_num], wall_y[wall_num];
    
    GenerateWalls(wall_num, grid);
    GenerateMarkers(marker_num, grid, robot_x_num, robot_y_num);
    // grid[0][4].type = 1;
    // grid[0][4].visited = true;
    // grid[9][1].type = 1;
    // grid[9][1].visited = true;
    // grid[8][2].type = 1;
    // grid[8][2].visited = true;
    // grid[0][1].type = 3;
    

    DrawCell(grid);
    DrawGrid(x_offset, y_offset, grid_size, grid_num);
    PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir);
    // return 0;
    int prev_robot_x_num, prev_robot_y_num;

    StepStack step_record;
    step_record.top = -1;

    while(marker_num > 0) {
        if (robot_dir == north) {
            prev_robot_x_num = robot_x_num;
            prev_robot_y_num = robot_y_num+1;
        } else if (robot_dir == east) {
            prev_robot_x_num = robot_x_num-1;
            prev_robot_y_num = robot_y_num;
        } else if (robot_dir == south) {
            prev_robot_x_num = robot_x_num;
            prev_robot_y_num = robot_y_num-1;
        } else if (robot_dir == west) {
            prev_robot_x_num = robot_x_num+1;
            prev_robot_y_num = robot_y_num;
        }
        
        // clear();
        // DrawCell(grid);
        // DrawGrid(x_offset, y_offset, grid_size, grid_num);
        // PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);

        depth_first_search(&robot_x_num, &robot_y_num, prev_robot_x_num, prev_robot_y_num, &step_record, grid, &robot_dir);
        
        marker_num--;
        printf("Marker left: %d\n", marker_num);
        sleep(1000);

        for (int i = 0; i < grid_num; i++) {
            for (int j = 0; j < grid_num; j++) {
                grid[i][j].visited = 0;
                grid[i][j].robot = 0;
                if (i == 0 || i == grid_num-1 || j == 0 || j == grid_num-1) {
                    grid[i][j].edge = 1;
                } else {
                    grid[i][j].edge = 0;
                }
                if (grid[i][j].type == 1) {
                    grid[i][j].visited = 1;
                }
            }
        }

        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};

        while (!isEmpty(&step_record)) {
            int robot_y_num = pop(&step_record);
            int robot_x_num = pop(&step_record);
            for (int i = 0; i < 4; i++) {
                int new_x = robot_x_num + dx[i];
                int new_y = robot_y_num + dy[i];
                if (grid[new_x][new_y].type == 2 && isValid(new_x,new_y)) {
                    resetStack(&step_record);
                    initStack(&step_record);
                    push(&step_record, new_x);
                    push(&step_record, new_y);
                    printf("Home is found");
                }
            }
            printf("x: %d, y: %d\n", robot_x_num, robot_y_num);
            clear();
            DrawCell(grid);
            DrawGrid(50, 50, grid_size, grid_num);
            robot_dir = getDirection(prev_robot_x_num, prev_robot_y_num, robot_x_num, robot_y_num);
            //robot_dir = (robot_dir + 2) % 4;
            PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir);
            prev_robot_x_num = robot_x_num;
            prev_robot_y_num = robot_y_num;
        }
    }
    return 0;
}