#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>
#include <time.h>
#include "Draw.h"
#include <stdbool.h>

typedef struct {
    int x; //top left corner
    int y; //top left corner
    int x_num;
    int y_num;
    int type; //0: empty, 1: wall, 2: start, 3: marker
    int edge; //0: not edge, 1: edge
    int visited; //0: not visited, 1: visited
    int robot; //0: no robot, 1: robot
} Cell;

typedef enum {
    north = 0,
    east = 1,
    south = 2,
    west = 3
} direction;

void DrawCell(int grid_num, int grid_size, Cell grid[grid_num][grid_num]) {
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
            else if (grid[i][j].visited == 1) {
                setColour(orange);
                fillRect(grid[i][j].x, grid[i][j].y, grid_size, grid_size);
            }
            setColour(black);
            // Draw Grid
            // drawPolygon(4, (int[]){grid[i][j].x,grid[i][j].x+grid_size,grid[i][j].x+grid_size,grid[i][j].x}, (int[]){grid[i][j].y,grid[i][j].y,grid[i][j].y+grid_size,grid[i][j].y+grid_size});
        }
    }
}

void GenerateMarkers(int marker_num, int *marker_x, int *marker_y, int grid_num, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
    srand(time(NULL));
    int i, j;
    int edge[] = {0, grid_num-1};
    for (i = 0; i < marker_num; i++) {
        marker_x[i] = rand()%grid_num;
        marker_y[i] = edge[rand()%2];
        if (marker_x[i] == 0 || marker_x[i] == grid_num-1) {
            marker_y[i] = rand()%grid_num;
        }
        for (j = 0; j < i; j++) {
            if (marker_x[i] == marker_x[j] && marker_y[i] == marker_y[j]) {
                i--;
                break;
            } else if (marker_x[i] == robot_x && marker_y[i] == robot_y) {
                i--;
                break;
            }
        }
        grid[marker_x[i]][marker_y[i]].type = 3;
        printf("marker_x: %d, marker_y: %d\n", marker_x[i], marker_y[i]);
    }
}

void GenerateWalls(int marker_num, int *marker_x, int *marker_y, int grid_num, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
    srand(time(NULL));
    int i, j;
    int edge[] = {0, grid_num-1};
    for (i = 0; i < marker_num; i++) {
        marker_x[i] = rand()%grid_num;
        marker_y[i] = edge[rand()%2];
        if (marker_x[i] == 0 || marker_x[i] == grid_num-1) {
            marker_y[i] = rand()%grid_num;
        }
        for (j = 0; j < i; j++) {
            if (marker_x[i] == marker_x[j] && marker_y[i] == marker_y[j]) {
                i--;
                break;
            } else if (marker_x[i] == robot_x && marker_y[i] == robot_y) {
                i--;
                break;
            } else if (grid[marker_x[i]][marker_y[i]].type == 3) {
                i--;
                break;
            }
        }
        grid[marker_x[i]][marker_y[i]].type = 1;
        grid[marker_x[i]][marker_y[i]].visited = 1;
        printf("marker_x: %d, marker_y: %d\n", marker_x[i], marker_y[i]);
    }
}

void PlaceRobot(int x, int y, direction robot_dir, int grid_size) {
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
}

bool isValid(int x_num, int y_num, int grid_num) {
    return (x_num >= 0 && x_num < grid_num && y_num >= 0 && y_num < grid_num);
}

bool depth_first_search(int* robot_x_num, int* robot_y_num, direction *robot_dir, int grid_size, int grid_num, Cell grid[grid_num][grid_num]) {
    //sleep(100);
    printf("robot_x: %d, robot_y: %d\n", *robot_x_num, *robot_y_num);
    if (grid[*robot_x_num][*robot_y_num].type == 3) {
        grid[*robot_x_num][*robot_y_num].type = 0;
        clear();
        DrawCell(grid_num, grid_size, grid);
        DrawGrid(50, 50, grid_size, grid_num);
        PlaceRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, 0, grid_size);
        sleep(1000);
        for (int i = 0; i < grid_num; i++) {
            for (int j = 0; j < grid_num; j++) {
                grid[i][j].visited = 1;
            }
        }
    }
    grid[*robot_x_num][*robot_y_num].visited = 1;
    // Define the 4 possible movement directions (up, down, left, right)
    
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        clear();
        DrawCell(grid_num, grid_size, grid);
        DrawGrid(50, 50, grid_size, grid_num);
        PlaceRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir, grid_size);
        int new_x = *robot_x_num + dx[i];
        int new_y = *robot_y_num + dy[i];
        sleep(100);
        if (isValid(new_x, new_y, grid_num) && !grid[new_x][new_y].visited) {
            if (i == 0) {
                *robot_dir = 0;
            } else if (i == 1) {
                *robot_dir = 2;
            } else if (i == 2) {
                *robot_dir = 3;
            } else if (i == 3) {
                *robot_dir = 1;
            }
            depth_first_search(&new_x, &new_y, robot_dir, grid_size, grid_num, grid);
            // if(depth_first_search(&new_x, &new_y, grid_size, grid_num, grid)) {
            //     return true;
            // };
        }

        // if (i == 0) {
        //     if (*robot_y_num - 1 >= 0 && grid[*robot_x_num][*robot_y_num - 1].type != 1 && grid[*robot_x_num][*robot_y_num - 1].visited != 1) {
        //         *robot_y_num -= 1;
        //         depth_first_search(robot_x_num, robot_y_num, grid_size, grid_num, grid);
        //     }
        // } else if (i == 1) {
        //     if (*robot_x_num + 1 < grid_num && grid[*robot_x_num + 1][*robot_y_num].type != 1 && grid[*robot_x_num + 1][*robot_y_num].visited != 1) {
        //         *robot_x_num += 1;
        //         depth_first_search(robot_x_num, robot_y_num, grid_size, grid_num, grid);
        //     }
        // } else if (i == 2) {
        //     if (*robot_y_num + 1 < grid_num && grid[*robot_x_num][*robot_y_num + 1].type != 1 && grid[*robot_x_num][*robot_y_num + 1].visited != 1) {
        //         *robot_y_num += 1;
        //         depth_first_search(robot_x_num, robot_y_num, grid_size, grid_num, grid);
        //     }
        // } else if (i == 3) {
        //     if (*robot_x_num - 1 >= 0 && grid[*robot_x_num - 1][*robot_y_num].type != 1 && grid[*robot_x_num - 1][*robot_y_num].visited != 1) {
        //         *robot_x_num -= 1;
        //         depth_first_search(robot_x_num, robot_y_num, grid_size, grid_num, grid);
        //     }
        // }
    }
    return false;
}

// void PlaceCorrect(int* x, int* y, int x_offset, int y_offset, int grid_size, int grid_num) {
//     if (*x < x_offset) {
//         *x = x_offset;
//     } else if (*x > x_offset + grid_num*grid_size) {
//         *x = grid_num*grid_size + x_offset;
//     } else if (*y < y_offset) {
//         *y = y_offset;
//     } else if (*y > y_offset + grid_num*grid_size) {
//         *y = grid_num*grid_size + y_offset;
//     }
// }

void MoveFoward(int* robot_x_num, int* robot_y_num, direction* dir, int grid_num, Cell grid[grid_num][grid_num]) {
    if (*dir == north) {
        if (*robot_y_num - 1 >= 0 && grid[*robot_x_num][*robot_y_num - 1].type != 1) {
            *robot_y_num -= 1;
        } else {
            *dir = east;
        }
    } else if (*dir == east) {
        if (*robot_x_num + 1 < grid_num && grid[*robot_x_num + 1][*robot_y_num].type != 1) {
            *robot_x_num += 1;
        } else {
            *dir = south;
        }
    } else if (*dir == south) {
        if (*robot_y_num + 1 < grid_num && grid[*robot_x_num][*robot_y_num + 1].type != 1) {
            *robot_y_num += 1;
        } else {
            *dir = west;
        }
    } else if (*dir == west) {
        if (*robot_x_num - 1 >= 0 && grid[*robot_x_num - 1][*robot_y_num].type != 1) {
            *robot_x_num -= 1;
        } else {
            *dir = north;
        }
    }
}


int main(int argc, char **argv) {
    setWindowSize(600, 600);
    const int x_offset = 50;
    const int y_offset = 50;
    const int grid_size = 50;
    const int grid_num = 10;
    
    Cell grid[grid_num][grid_num];
    int i, j;
    for (i = 0; i < grid_num; i++) {
        for (j = 0; j < grid_num; j++) {
            grid[i][j].x = x_offset + i*grid_size;
            grid[i][j].y = y_offset + j*grid_size;
            grid[i][j].x_num = i;
            grid[i][j].y_num = j;
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

    int robot_x_num = 0;
    int robot_y_num = 0;
    direction robot_dir = north;

    if (argc == 4) {
        robot_x_num = atoi(argv[1]);
        robot_y_num = atoi(argv[2]);
        robot_dir = atoi(argv[3]);
        grid[atoi(argv[1])][atoi(argv[2])].robot = 1;
        // grid[atoi(argv[1])][atoi(argv[2])].visited = 1;
        grid[atoi(argv[1])][atoi(argv[2])].type = 2;
        // printf("robot_x: %d, robot_y: %d, robot_dir: %d\n", robot_x, robot_y, robot_dir);
    }

    int marker_num = 5;
    int marker_x[marker_num], marker_y[marker_num];
    GenerateMarkers(marker_num, marker_x, marker_y, grid_num, grid, grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y);
    GenerateWalls(marker_num, marker_x, marker_y, grid_num, grid, grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y);
    printf("marker_x: %d, marker_y: %d\n", marker_x[0], marker_y[0]);
    DrawCell(grid_num, grid_size, grid);
    DrawGrid(x_offset, y_offset, grid_size, grid_num);
    PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
    sleep(200);
    // int* Step_record = NULL;
    // Step_record = (int*)malloc(sizeof(int)*20);
    int Step_record[500];
    i = 0;
    clear();
    DrawCell(grid_num, grid_size, grid);
    DrawGrid(x_offset, y_offset, grid_size, grid_num);
    // MoveFoward(&robot_x_num, &robot_y_num, &robot_dir, grid_num, grid);

    while(marker_num > 1) {
        int k;
        clear();
        DrawCell(grid_num, grid_size, grid);
        DrawGrid(x_offset, y_offset, grid_size, grid_num);
        // MoveFoward(&robot_x_num, &robot_y_num, &robot_dir, grid_num, grid);
        depth_first_search(&robot_x_num, &robot_y_num, &robot_dir, grid_size, grid_num, grid);
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
        // if (grid[robot_x_num][robot_y_num].type == 3) {
        //     marker_num--;
        //     PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        //     sleep(500);
        //     // grid[robot_x_num][robot_y_num].type = 0;
        //     for (int j = i; j >= 0; j--) {
        //         if (Step_record[j] == 0) {
        //             robot_dir = 2;
        //             clear();
        //             DrawCell(grid_num, grid_size, grid);
        //             DrawGrid(x_offset, y_offset, grid_size, grid_num);
        //             PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        //             grid[robot_x_num][robot_y_num].type = 0;
        //             sleep(100);
        //             robot_y_num++;
        //         } else if (Step_record[j] == 1) {
        //             robot_dir = 3;
        //             clear();
        //             DrawCell(grid_num, grid_size, grid);
        //             DrawGrid(x_offset, y_offset, grid_size, grid_num);
        //             PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        //             grid[robot_x_num][robot_y_num].type = 0;
        //             sleep(100);
        //             robot_x_num--;
        //         } else if (Step_record[j] == 2) {
        //             robot_dir = 0;
        //             clear();
        //             DrawCell(grid_num, grid_size, grid);
        //             DrawGrid(x_offset, y_offset, grid_size, grid_num);
        //             PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        //             grid[robot_x_num][robot_y_num].type = 0;
        //             sleep(100);
        //             robot_y_num--;
        //         } else if (Step_record[j] == 3) {
        //             robot_dir = 1;
        //             clear();
        //             DrawCell(grid_num, grid_size, grid);
        //             DrawGrid(x_offset, y_offset, grid_size, grid_num);
        //             PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        //             grid[robot_x_num][robot_y_num].type = 0;
        //             sleep(100);
        //             robot_x_num++;
        //         }
        //         // } else if (Step_record[j] == 4) {
        //         //     sleep(200);
        //         //     robot_dir = 0;
        //         // } else if (Step_record[j] == 5) {
        //         //     sleep(200);
        //         //     robot_dir = 0;
        //         // } else if (Step_record[j] == 6) {
        //         //     sleep(200);
        //         //     robot_dir = 0;
        //         // } else if (Step_record[j] == 7) {
        //         //     sleep(200);
        //         //     robot_dir = 0;
        //         // }
        //         if (grid[robot_x_num][robot_y_num].type != 2) {
        //             grid[robot_x_num][robot_y_num].type = 3;
        //         }
        //         clear();
        //         DrawCell(grid_num, grid_size, grid);
        //         DrawGrid(x_offset, y_offset, grid_size, grid_num);
        //         PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        //         //sleep(100);
        //         printf("1\n");
        //     }
        //     i = 0;
        // }
        // PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        // // if (marker_num == 0) {
        // //     break;
        // // }
        // sleep(100);
    }
        // printf("i: %d\n", i);
        // for (int j = i; j >= 0; j--) {
        //     if (Step_record[j] == 0) {
        //         robot_dir = 2;
        //         robot_y_num++;
        //     } else if (Step_record[j] == 1) {
        //         robot_dir = 3;
        //         robot_x_num--;
        //     } else if (Step_record[j] == 2) {
        //         robot_dir = 0;
        //         robot_y_num--;
        //     } else if (Step_record[j] == 3) {
        //         robot_dir = 1;
        //         robot_x_num++;
        //     } else if (Step_record[j] == 4) {
        //         robot_dir = 3;
        //     } else if (Step_record[j] == 5) {
        //         robot_dir = 0;
        //     } else if (Step_record[j] == 6) {
        //         robot_dir = 1;
        //     } else if (Step_record[j] == 7) {
        //         robot_dir = 2;
        //     }
        //     clear();
        //     DrawCell(grid_num, grid_size, grid);
        //     DrawGrid(x_offset, y_offset, grid_size, grid_num);
        //     PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);
        //     sleep(20);
        //     printf("1\n");
        // }


    // //  PlaceCorrect(&robot_x, &robot_y, x_offset, y_offset, grid_size, grid_num);
    // PlaceRobot(grid[robot_x_num][robot_y_num].x, grid[robot_x_num][robot_y_num].y, robot_dir, grid_size);

    // int i;
    // for (i = 0; i < 20; i++) {
    //     robot_dir = (robot_dir+1)%4;
    //     clear();
    //     DrawGrid(x_offset, y_offset, grid_size, grid_num);
    //     // PlaceCorrect(&robot_x, &robot_y, x_offset, y_offset, grid_size, grid_num);
    //     PlaceRobot(robot_x, robot_y, robot_dir, grid_size);
    //     sleep(200);
    // }
    // // int i;
    // // for (i = 0; i < 9; i++) {
    // //     clear();
    // //     DrawGrid(x_offset, y_offset, grid_size, grid_num);
    // //     setColour(orange);
    // //     DrawMarker(115+30*i, 30);
    // //     //fillRect(115+30*i, 30, 30, 30);
    // //     sleep(200);
    // // }
    return 0;
}

