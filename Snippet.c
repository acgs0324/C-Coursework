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