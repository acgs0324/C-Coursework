#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>
#include <time.h>
#include "Draw.h"
#include <stdbool.h>

const int x_offset = 50;
const int y_offset = 50;
const int grid_size = 50;
const int grid_num = 10;

typedef struct {
    int x; //top left corner
    int y; //top left corner
    int type; //0: empty, 1: wall, 2: start, 3: marker
    int edge; //0: not edge, 1: edge
    int visited; //0: not visited, 1: visited
    int robot; //0: no robot, 1: robot
} Cell;

typedef struct {
    int array[1000];
    int top;
} StepStack;


typedef enum {
    north = 0,
    east = 1,
    south = 2,
    west = 3
} direction;

void push(StepStack* step_record, int data) {
    step_record->array[++step_record->top] = data;
}

int pop(StepStack* step_record) {
    return step_record->array[step_record->top--];
}

void DrawCell(Cell grid[grid_num][grid_num]) {
    int i, j;
    for (i = 0; i < grid_num; i++) {
        for (j = 0; j < grid_num; j++) {
            if (grid[i][j].type == 1) {
                setColour(black);
                fillRect(grid[i][j].x, grid[i][j].y, grid_size, grid_size);
            } else if (grid[i][j].type == 2) {
                setColour(green);
                fillRect(grid[i][j].x, grid[i][j].y, grid_size, grid_size);
            } else if (grid[i][j].type == 3) {
                setColour(red);
                fillRect(grid[i][j].x, grid[i][j].y, grid_size, grid_size);
            } 
            // else if (grid[i][j].visited == 1) {
            //     setColour(orange);
            //     fillRect(grid[i][j].x, grid[i][j].y, grid_size, grid_size);
            // }
            setColour(black);
            // Draw Grid
            // drawPolygon(4, (int[]){grid[i][j].x,grid[i][j].x+grid_size,grid[i][j].x+grid_size,grid[i][j].x}, (int[]){grid[i][j].y,grid[i][j].y,grid[i][j].y+grid_size,grid[i][j].y+grid_size});
        }
    }
}

void GenerateMarkers(int marker_num, int *marker_x, int *marker_y, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
    srand(time(NULL));
    int i, j;
    int edge[] = {0, grid_num-1};
    for (i = 0; i < marker_num; i++) {
        marker_x[i] = rand()%grid_num;
        // marker_y[i] = edge[rand()%2];
        marker_y[i] = rand()%grid_num;
        // if (marker_x[i] == 0 || marker_x[i] == grid_num-1) {
        //     marker_y[i] = rand()%grid_num;
        // }
        for (j = 0; j < i; j++) {
            if (marker_x[i] == marker_x[j] && marker_y[i] == marker_y[j]) {
                i--;
                break;
            }
        }
        if (marker_x[i] == robot_x && marker_y[i] == robot_y) {
                i--;
        } else {
            grid[marker_x[i]][marker_y[i]].type = 3;
        }
        
        printf("marker_x: %d, marker_y: %d\n", marker_x[i], marker_y[i]);
    }
}

void GenerateWalls(int wall_num, int *wall_x, int *wall_y, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
    srand(time(NULL));
    int i, j;
    int edge[] = {0, grid_num-1};
    for (i = 0; i < wall_num; i++) {
        wall_x[i] = rand()%grid_num;
        // wall_y[i] = edge[rand()%2];
        wall_y[i] = rand()%grid_num;
        // if (wall_x[i] == 0 || wall_x[i] == grid_num-1) {
        //     wall_y[i] = rand()%grid_num;
        // }
        for (j = 0; j < i; j++) {
            if (wall_x[i] == wall_x[j] && wall_y[i] == wall_y[j]) {
                i--;
                break;
            }
        }
        if (wall_x[i] == robot_x && wall_y[i] == robot_y) {
            i--;
        } else if (grid[wall_x[i]][wall_y[i]].type == 3) {
            i--;
        } else {
            grid[wall_x[i]][wall_y[i]].type = 1;
            grid[wall_x[i]][wall_y[i]].visited = 1;
        }
        
        printf("wall_x: %d, wall_y: %d\n", wall_x[i], wall_y[i]);
    }
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

bool isValid(int x_num, int y_num) {
    return (x_num >= 0 && x_num < grid_num && y_num >= 0 && y_num < grid_num);
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
    // *robot_dir = getDirection(prev_robot_x_num, prev_robot_y_num, *robot_x_num, *robot_y_num);
    // *robot_dir = (*robot_dir + 2) % 4;
    // clear();
    // DrawCell(grid);
    // DrawGrid(50, 50, grid_size, grid_num);
    // PlaceRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir);
    // printf("Move from (%d, %d) to (%d, %d)\n", prev_robot_x_num, prev_robot_y_num, *robot_x_num, *robot_y_num);
    return false;
}

void initStack(StepStack* step_record) {
    step_record->top = -1; // -1 indicates an empty stack
}

int isEmpty(StepStack* step_record) {
    return step_record->top == -1;
}

void resetCell(Cell grid[grid_num][grid_num]) {
    for (int i = 0; i < grid_num; i++) {
        for (int j = 0; j < grid_num; j++) {
            grid[i][j].x = x_offset + i*grid_size;
            grid[i][j].y = y_offset + j*grid_size;
            grid[i][j].type = 0;
            grid[i][j].visited = 0;
            grid[i][j].robot = 0;
            if (i == 0 || i == grid_num-1 || j == 0 || j == grid_num-1) {
                grid[i][j].edge = 1;
            } else {
                grid[i][j].edge = 0;
            }
        }
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
        robot_dir = atoi(argv[3]);
        grid[atoi(argv[1])][atoi(argv[2])].robot = 1;
        grid[atoi(argv[1])][atoi(argv[2])].type = 2;
    }

    int marker_num = 5;
    int marker_x[marker_num], marker_y[marker_num];
    int wall_num = 10;
    int wall_x[wall_num], wall_y[wall_num];

    GenerateMarkers(marker_num, marker_x, marker_y, grid, robot_x_num, robot_y_num);
    GenerateWalls(wall_num, wall_x, wall_y, grid, robot_x_num, robot_y_num);
    
    DrawCell(grid);
    DrawGrid(x_offset, y_offset, grid_size, grid_num);
    PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir);

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
        while (!isEmpty(&step_record)) {
            int y = pop(&step_record);
            int x = pop(&step_record);
            printf("x: %d, y: %d\n", x, y);
            clear();
            DrawCell(grid);
            DrawGrid(50, 50, grid_size, grid_num);
            robot_dir = getDirection(prev_robot_x_num, prev_robot_y_num, x, y);
            //robot_dir = (robot_dir + 2) % 4;
            PlaceRobot(grid[x][y].x, grid[x][y].y, robot_dir);
            prev_robot_x_num = x;
            prev_robot_y_num = y;
        }
    }
    return 0;
}

