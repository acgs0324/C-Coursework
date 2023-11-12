#ifndef BACKGROUND_H
#define BACKGROUND_H

const int grid_num;
const int grid_size;

typedef enum {
    empty = 0,
    wall = 1,
    start = 2,
    marker = 3
} type;

typedef struct {
    int x; //top left corner
    int y; //top left corner
    type type; //0: empty, 1: wall, 2: start, 3: marker
    int visited; //0: not visited, 1: visited
} Cell;

// Define the 4 possible movement directions (north, east, south, west)
int dx[4];
int dy[4];

void drawBackground(Cell grid[grid_num][grid_num]);
void drawGrid();
void drawCell(Cell grid[grid_num][grid_num]);
void initCell(Cell grid[grid_num][grid_num]);
void resetCellVisit(Cell grid[grid_num][grid_num]);
void GenerateCells(int, type, Cell grid[grid_num][grid_num], int, int);
void drawMarker(int, int);
int canPlaceRobot(int, int);

#endif