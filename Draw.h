const int x_offset; 
const int y_offset;
const int grid_size;;
const int grid_num; 

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

void DrawGrid(int, int ,int ,int);
void DrawCell(Cell grid[grid_num][grid_num]);
void initCell(Cell grid[grid_num][grid_num]);
void resetCell(Cell grid[grid_num][grid_num]);
void GenerateWalls(int, Cell grid[grid_num][grid_num]);
void GenerateMarkers(int, Cell grid[grid_num][grid_num], int, int );
void PlaceRobot(int, int, direction);
direction initdirection(char* );
direction getDirection(int, int, int, int);