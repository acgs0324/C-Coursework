#ifndef BACKGROUND_H
#define BACKGROUND_H

const int cell_num;
const int cell_size;

typedef enum {
    empty = 0,
    wall = 1,
    home = 2,
    marker = 3
} type;

typedef struct {
    int x; //top left corner
    int y; //top left corner
    type type;
    int visited;
} Cell;

int dx[4];
int dy[4];

void drawBackground(Cell grid[cell_num][cell_num]);
void drawGrid();
void drawCell(Cell grid[cell_num][cell_num]);
void initCell(Cell grid[cell_num][cell_num]);
void resetCellVisit(Cell grid[cell_num][cell_num]);
void GenerateCells(int, type, Cell grid[cell_num][cell_num], int, int);
void drawMarker(int, int);
int canMoveForward(int, int);

#endif