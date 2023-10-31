#include <stdio.h>
#include "graphics.h"
#include "Draw.h"

void DrawGrid(int x_offset, int y_offset, int grid_size, int grid_num) {
    setColour(black);
    int rx = grid_num*grid_size + x_offset;
    int by = grid_num*grid_size + y_offset;
    for (int i = 0; i <= grid_num*grid_size; i+=grid_size) {
        drawLine(x_offset, y_offset+i, rx, y_offset+i);
        drawLine(x_offset+i, y_offset, x_offset+i, by);
    }
}