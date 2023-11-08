#include <stdio.h>
#include "graphics.h"
#include "Draw.h"

void DrawGrid(int x_offset, int y_offset, int grid_size, int grid_num) { //Draw the Grid
    setColour(black);
    int rx = grid_num*grid_size + x_offset;
    int by = grid_num*grid_size + y_offset;
    for (int i = 0; i <= grid_num*grid_size; i+=grid_size) {
        drawLine(x_offset, y_offset+i, rx, y_offset+i);
        drawLine(x_offset+i, y_offset, x_offset+i, by);
    }
}

void DrawCell(Cell grid[grid_num][grid_num]) { //Paint the Cells
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

void resetCell(Cell grid[grid_num][grid_num]) { //Reset the Cells
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