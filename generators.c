#include "Draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

bool isDuplicate(int *x, int *y, int *i, int j) {
    for (int k = 0; k < *i; k++) {
        if (x[k] == x[*i] && y[k] == y[*i]) {
            i--;
            return true;
        }
    }
    return false;
}

bool isValid(int , int );

bool dfs(int robot_x_num, int robot_y_num, int marker_x, int marker_y, Cell temp_grid[grid_num][grid_num]) {

    temp_grid[robot_x_num][robot_y_num].visited = 1;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    
    if (robot_x_num == marker_x && robot_y_num == marker_y) {
        return true;
    }

    for (int i = 0; i < 4; i++) {
        int new_x = robot_x_num + dx[i];
        int new_y = robot_y_num + dy[i];
        if (isValid(new_x, new_y) && !temp_grid[new_x][new_y].visited) {
            if (dfs(new_x, new_y, marker_x, marker_y, temp_grid)) {
                return true;
            }
        }
    }
    return false;
}

void GenerateWalls(int wall_num, Cell grid[grid_num][grid_num]) {
    srand(time(NULL));
    int i = 0;
    while (i < wall_num) {
        int wall_x = rand()%grid_num; 
        int wall_y = rand()%grid_num;

        if (grid[wall_x][wall_y].type == empty) {
            grid[wall_x][wall_y].type = wall;
            grid[wall_x][wall_y].visited = true;
            i++;
        }
    }
}

void GenerateMarkers(int marker_num, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
    int counter = 0;
    Cell temp_grid[grid_num][grid_num];

    srand(time(NULL));
    int i = 0;
    while (i < marker_num) {
        for (int k = 0; k < grid_num; k++) {
            for (int s = 0; s < grid_num; s++) {
                temp_grid[k][s] = grid[k][s];
            }
        }
        if (counter > 1000) {
            break;
        }
        int marker_x = rand()%grid_num;
        int marker_y = rand()%grid_num;
        
        if (grid[marker_x][marker_y].type == empty && dfs(robot_x, robot_y, marker_x, marker_y, temp_grid)) {
            grid[marker_x][marker_y].type = marker;
            i++;
            for (int k = 0; k < grid_num; k++) {
                for (int s = 0; s < grid_num; s++) {
                    if (grid[k][s].type != 1) {
                        grid[k][s].visited = 0;
                    }
                }
            }
        }
    }
}

// void GenerateMarkers(int marker_num, int *marker_x, int *marker_y, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
//     srand(time(NULL));
//     int i, j;
//     int edge[] = {0, grid_num-1};

//     Cell temp_grid[grid_num][grid_num];
//     for (int k = 0; k < grid_num; k++) {
//             for (int s = 0; s < grid_num; s++) {
//                 temp_grid[k][s] = grid[k][s];
//         }
//     }

//     int counter = 0;
    
//     for (i = 0; i < marker_num; i++) {
//         if (counter > 1000000000) {
//             break;
//         }
//         marker_x[i] = rand()%grid_num;
//         // marker_y[i] = edge[rand()%2];
//         marker_y[i] = rand()%grid_num;
//         // if (marker_x[i] == 0 || marker_x[i] == grid_num-1) {
//         //     marker_y[i] = rand()%grid_num;
//         // }
//         for (j = 0; j < i; j++) {
//             if (marker_x[i] == marker_x[j] && marker_y[i] == marker_y[j]) {
//                 i--;
//                 break;
//             }
//         }
//         if (marker_x[i] == robot_x && marker_y[i] == robot_y) {
//             i--;
//         } else if (grid[marker_x[i]][marker_y[i]].type == 1) {
//             i--;
//         }
//         // else if (!dfs(robot_x, robot_y, marker_x[i], marker_y[i], temp_grid)) {
//         //     i--;
//         // } 
//         else if (dfs(robot_x, robot_y, marker_x[i], marker_y[i], temp_grid)){
//             grid[marker_x[i]][marker_y[i]].type = 3;
//         }
//         for (int k = 0; k < grid_num; k++) {
//             for (int s = 0; s < grid_num; s++) {
//                 if (temp_grid[k][s].type != 1) {
//                     temp_grid[k][s].visited = 0;
//                 }
//         }
//     }
//         counter++;
//         // else {
//         //     grid[marker_x[i]][marker_y[i]].type = 3;
//         // }
//         printf("marker_x: %d, marker_y: %d\n", marker_x[i], marker_y[i]);
//     }
// }