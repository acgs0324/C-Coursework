#include <stdio.h>
#include "graphics.h"
#include "background.h"
#include <math.h>

void drawBackground(Cell grid[grid_num][grid_num]) {
    background();
    clear();
    drawCell(grid);
    drawGrid();
}

void drawGrid() {
    setColour(black);
    int end_vertex = grid_size*(grid_num + 1);
    for (int i = 0; i <= grid_num*grid_size; i+=grid_size) {
        drawLine(grid_size, grid_size+i, end_vertex, grid_size+i);
        drawLine(grid_size+i, grid_size, grid_size+i, end_vertex);
    }
}

void drawCell(Cell grid[grid_num][grid_num]) { //Paint the Cells
    for (int i = 0; i < grid_num; i++) {
        for (int j = 0; j < grid_num; j++) {
            switch (grid[i][j].type) {
                case empty:
                    break;
                case wall:
                    setColour(black);
                    fillRect(grid[i][j].x, grid[i][j].y, grid_size, grid_size); break;
                case start:
                    setColour(green);
                    fillRect(grid[i][j].x, grid[i][j].y, grid_size, grid_size); break;
                case marker:
                    setColour(red);
                    drawMarker(grid[i][j].x, grid[i][j].y); break;
            }
        }
    }
}

void initCell(Cell grid[grid_num][grid_num]) {
    for (int i = 0; i < grid_num; i++) {
        for (int j = 0; j < grid_num; j++) {
            grid[i][j] = (Cell) { .x = grid_size * (i + 1), .y = grid_size * (j + 1), .type = 0, .visited = 0 };
        }
    }
}

void resetCellVisit(Cell grid[grid_num][grid_num]) {
    for (int i = 0; i < grid_num; i++) {
        for (int j = 0; j < grid_num; j++) {
            grid[i][j].visited = 0;
        }
    }
}

void drawKochSnowflake(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        // Base case
        drawLine(x1, y1, x2, y2);
    } else {
        double deltaX = x2 - x1;
        double deltaY = y2 - y1;
       
        double x3 = x1 + deltaX / 3;
        double y3 = y1 + deltaY / 3;

        double x4 = (0.5 * (x1 + x2) + (y2 - y1) * sqrt(3) / 6);
        double y4 = (0.5 * (y1 + y2) - (x2 - x1) * sqrt(3) / 6);
       
        double x5 = x1 + deltaX * 2 / 3;
        double y5 = y1 + deltaY * 2 / 3;

        drawKochSnowflake(x1, y1, x3, y3, depth - 1);
        drawKochSnowflake(x3, y3, x4, y4, depth - 1);
        drawKochSnowflake(x4, y4, x5, y5, depth - 1);
        drawKochSnowflake(x5, y5, x2, y2, depth - 1);
    }
}

void drawMarker(int x, int y) {
    int depth = 3;
    x += 10;
    y += 10;
    int size = grid_size - 20;
    double x1 = x, y1 = y + size * 4 / 5;
    double x2 = x + size, y2 = y + size * 4 / 5;
    double x3 = x + size / 2, y3 = y + size * 4 / 5 - sqrt(pow(size, 2) - pow(size / 2, 2));

    drawKochSnowflake(x2, y2, x1, y1, depth);
    drawKochSnowflake(x1, y1, x3, y3, depth);
    drawKochSnowflake(x3, y3, x2, y2, depth);
}