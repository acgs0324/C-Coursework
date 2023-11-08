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


// bool dfs(int robot_x_num, int robot_y_num, int marker_x, int marker_y, Cell temp_grid[grid_num][grid_num]) {
//     //Define the 4 possible movement directions (north, east, south, west)
//     temp_grid[robot_x_num][robot_y_num].visited = 1;
//     int dx[] = {0, 1, 0, -1};
//     int dy[] = {-1, 0, 1, 0};
    
//     if (robot_x_num == marker_x && robot_y_num == marker_y) {
//         return true;
//     }

//     for (int i = 0; i < 4; i++) {
//         int new_x = robot_x_num + dx[i];
//         int new_y = robot_y_num + dy[i];
//         if (isValid(new_x, new_y) && !temp_grid[new_x][new_y].visited) {
//             if (dfs(new_x, new_y, marker_x, marker_y, temp_grid)) {
//                 return true;
//             }
//         }
//     }
//     printf("cannot find marker\n");
//     return false;
// }

// void GenerateWalls(int wall_num, int *wall_x, int *wall_y, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
//     srand(time(NULL));
//     int i, j;
//     int edge[] = {0, grid_num-1};
//     for (i = 0; i < wall_num; i++) {
//         wall_x[i] = rand()%grid_num;
//         // wall_y[i] = edge[rand()%2];
//         wall_y[i] = rand()%grid_num;
//         // if (wall_x[i] == 0 || wall_x[i] == grid_num-1) {
//         //     wall_y[i] = rand()%grid_num;
//         // }
//         for (j = 0; j < i; j++) {
//             if (wall_x[i] == wall_x[j] && wall_y[i] == wall_y[j]) {
//                 i--;
//                 break;
//             }
//         }
//         if (wall_x[i] == robot_x && wall_y[i] == robot_y) {
//             i--;
//         } else if (grid[wall_x[i]][wall_y[i]].type == 3) {
//             i--;
//         } else {
//             grid[wall_x[i]][wall_y[i]].type = 1;
//             grid[wall_x[i]][wall_y[i]].visited = 1;
//         }
//         printf("wall_x: %d, wall_y: %d\n", wall_x[i], wall_y[i]);
//     } 
// }

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