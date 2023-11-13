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

// while (!isEmpty(&step_record)) {
        //     robot_y_num = pop(&step_record);
        //     robot_x_num = pop(&step_record);
        //     robot_dir = getDirection(prev_robot_x_num, prev_robot_y_num, robot_x_num, robot_y_num);
        //     drawRobot(grid, robot_x_num, robot_y_num, robot_dir);
        //     prev_robot_x_num = robot_x_num;
        //     prev_robot_y_num = robot_y_num;
        //     for (int i = 0; i < 4; i++) {
        //         int new_x = robot_x_num + dx[i];
        //         int new_y = robot_y_num + dy[i];
        //         if (grid[new_x][new_y].type == start && isValid(new_x, new_y)) {
        //             resetStack(&step_record);
        //             push(&step_record, new_x);
        //             push(&step_record, new_y);
        //             printf("Home is found \n");
        //         }
        //     }
        // }

        
// if (robot_dir == north) {
        //     prev_robot_x_num = robot_x_num;
        //     prev_robot_y_num = robot_y_num+1;
        // } else if (robot_dir == east) {
        //     prev_robot_x_num = robot_x_num-1;
        //     prev_robot_y_num = robot_y_num;
        // } else if (robot_dir == south) {
        //     prev_robot_x_num = robot_x_num;
        //     prev_robot_y_num = robot_y_num-1;
        // } else if (robot_dir == west) {
        //     prev_robot_x_num = robot_x_num+1;
        //     prev_robot_y_num = robot_y_num;
        // }

    // grid[0][4].type = 1;
    // grid[0][4].visited = true;
    // grid[9][1].type = 1;
    // grid[9][1].visited = true;
    // grid[8][2].type = 1;
    // grid[8][2].visited = true;
    // grid[0][1].type = 3;
    
void GenerateWalls(int wall_num, Cell grid[grid_num][grid_num]) {
    srand(time(NULL));
    int i = 0;
    while (i < wall_num) {
        int wall_x = rand()%grid_num; 
        int wall_y = rand()%grid_num;

        if (grid[wall_x][wall_y].type == empty && !besideStart(wall_x, wall_y, grid)) { // No need to check if it is duplicate, becuase it checks if it is empty
            grid[wall_x][wall_y].type = wall;
            i++;
        }
    }
}

void GenerateMarkers(int marker_num, Cell grid[grid_num][grid_num], int robot_x, int robot_y) {
    srand(time(NULL));
    int i = 0;
    printf("Marker num: %d\n", marker_num);
    while (i < marker_num) {
        int marker_x = rand()%grid_num;
        int marker_y = rand()%grid_num;
        
        if (grid[marker_x][marker_y].type == empty && checkReachable(robot_x, robot_y, marker_x, marker_y, grid) && !besideStart(marker_x, marker_y, grid)) {
            grid[marker_x][marker_y].type = marker;
            i++;
        }
        resetCellVisit(grid);
    }
}

void drawMarkerOnRobot(Cell grid[grid_num][grid_num], int robot_x_num, int robot_y_num) {
    setColour(red);
    //Draw circle marker
    int x = grid[robot_x_num][robot_y_num].x;
    int y = grid[robot_x_num][robot_y_num].y;
    
    // fillOval(x+grid_size/4, y+grid_size/4, grid_size/2, grid_size/2);
    //fillRect(x, y, grid_size, grid_size);
    // displayImage("Star_onRobot.png", x+grid_size/5, y+grid_size/5);
}


// int depth_first_search(int* robot_x_num, int* robot_y_num, int prev_robot_x_num, int prev_robot_y_num, Stack *step_record, Cell grid[grid_num][grid_num], direction *robot_dir) {
//     grid[*robot_x_num][*robot_y_num].visited = 1;
    
//     // Animation of move robot, each time by quarter of grid_size
//     // for (int i = 1; i <= 10; i++) {
//     //     float x_diff = grid[*robot_x_num][*robot_y_num].x - grid[prev_robot_x_num][prev_robot_y_num].x;
//     //     float y_diff = grid[*robot_x_num][*robot_y_num].y - grid[prev_robot_x_num][prev_robot_y_num].y;
//     //     placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x+x_diff/10*i, grid[prev_robot_x_num][prev_robot_y_num].y+y_diff/10*i, *robot_dir, 0);
//     // }
//     sleep(50);
//     placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir, 0);
//     push(step_record, *robot_x_num);
//     push(step_record, *robot_y_num);
//     push(step_record, *robot_dir);
    
//     if (grid[*robot_x_num][*robot_y_num].type == marker) { // If marker is found
//         grid[*robot_x_num][*robot_y_num].type = empty;
//         drawBackground(grid);
//         placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir ,1);
//         return 1;
//     }
    
//     for (int i = 0; i < 4; i++) {
//         int new_x = *robot_x_num + dx[i];
//         int new_y = *robot_y_num + dy[i];
//         if (isValid(new_x, new_y) && grid[new_x][new_y].type == 3) {
//             *robot_dir = i;
//             if(depth_first_search(&new_x, &new_y, *robot_x_num, *robot_y_num, step_record, grid, robot_dir)) {
//                 return 1;
//             };
//         }
//     }

//     for (int i = 0; i < 4; i++) {
//         int new_x = *robot_x_num + dx[i];
//         int new_y = *robot_y_num + dy[i];
//         // sleep(100);
//         if (isValid(new_x, new_y) && !grid[new_x][new_y].visited && grid[new_x][new_y].type != wall) {
//             *robot_dir = i;
//             // depth_first_search(&new_x, &new_y, *robot_x_num, *robot_y_num, grid, robot_dir);
//             if(depth_first_search(&new_x, &new_y, *robot_x_num, *robot_y_num, step_record, grid, robot_dir)) {
//                 return 1;
//             };
//         }
//     }

//     *robot_dir = getDirection(*robot_x_num, *robot_y_num, prev_robot_x_num, prev_robot_y_num);
//     // for (int i = 1; i <= 10; i++) {
//     //     float x_diff = grid[*robot_x_num][*robot_y_num].x - grid[prev_robot_x_num][prev_robot_y_num].x;
//     //     float y_diff = grid[*robot_x_num][*robot_y_num].y - grid[prev_robot_x_num][prev_robot_y_num].y;
//     //     placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x-x_diff/10*i, grid[prev_robot_x_num][prev_robot_y_num].y-y_diff/10*i, *robot_dir);
//     // }
//     sleep(100);
//     placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x, grid[prev_robot_x_num][prev_robot_y_num].y, *robot_dir, 0);
//     push(step_record, prev_robot_x_num);
//     push(step_record, prev_robot_y_num);
//     push(step_record, *robot_dir);
//     return 0;
// }


void updateRobotPosition(int* robot_x_num, int* robot_y_num, int prev_robot_x_num, int prev_robot_y_num, direction *robot_dir, Stack *step_record, Cell grid[grid_num][grid_num]) {
    grid[*robot_x_num][*robot_y_num].visited = 1;
    // int prev_robot_x_num = *robot_x_num + dx[(*robot_dir+ 2) % 4];
    // int prev_robot_y_num = *robot_y_num + dy[(*robot_dir+ 2) % 4];
    float x_diff = grid[*robot_x_num][*robot_y_num].x - grid[prev_robot_x_num][prev_robot_y_num].x;
    float y_diff = grid[*robot_x_num][*robot_y_num].y - grid[prev_robot_x_num][prev_robot_y_num].y;
    // if(getDirection(prev_robot_x_num, prev_robot_y_num, *robot_x_num, *robot_y_num) != *robot_dir) {
    //     sleep(1000);
    //     placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x, grid[prev_robot_x_num][prev_robot_y_num].y, *robot_dir, 1);
    //     sleep(1000);
    // }
    for (int i = 1; i <= 10; i++) {
        placeRobot(grid[prev_robot_x_num][prev_robot_y_num].x+x_diff/10*i, grid[prev_robot_x_num][prev_robot_y_num].y+y_diff/10*i, *robot_dir, 0);
        sleep(10);
    }
    // placeRobot(grid[*robot_x_num][*robot_y_num].x, grid[*robot_x_num][*robot_y_num].y, *robot_dir, 0);
    push(step_record, *robot_x_num);
    push(step_record, *robot_y_num);
    push(step_record, *robot_dir);
}