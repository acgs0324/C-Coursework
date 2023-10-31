#include <stdio.h>
#include <stdbool.h>

// Define the structure for a cell in the grid
struct Cell {
    int row, col;
    bool visited;
};

// Define the dimensions of the grid
#define ROWS 4
#define COLS 4

// Define the 4 possible movement directions (up, down, left, right)
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// Check if a cell is within the grid boundaries
bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

// Depth-First Search function
void DFS(struct Cell grid[ROWS][COLS], int row, int col) {
    grid[row][col].visited = true; // Mark the current cell as visited

    printf("Visiting cell (%d, %d)\n", row, col);

    // Explore the neighboring cells
    for (int i = 0; i < 4; i++) {
        int newRow = row + dr[i];
        int newCol = col + dc[i];

        if (isValid(newRow, newCol) && !grid[newRow][newCol].visited) {
            DFS(grid, newRow, newCol);
        }
    }
}

int main() {
    struct Cell grid[ROWS][COLS];

    // Initialize the grid with cells and mark them as unvisited
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j].row = i;
            grid[i][j].col = j;
            grid[i][j].visited = false;
        }
    }

    // Perform DFS starting from a specific cell (e.g., cell (0, 0))
    DFS(grid, 0, 0);

    return 0;
}

// #include <stdio.h>

// // Define the struct to represent a cell in the grid
// struct Cell {
//     int x;
//     int y;
//     int visited;
// };

// // Define the grid size
// #define ROWS 4
// #define COLS 4

// // Function to perform depth-first search
// void dfs(struct Cell grid[ROWS][COLS], int x, int y) {
//     if (x < 0 || x >= ROWS || y < 0 || y >= COLS || grid[x][y].visited)
//         return;

//     // Mark the cell as visited
//     grid[x][y].visited = 1;

//     // Print or perform any other operation on the cell
//     printf("Visiting cell (%d, %d)\n", x, y);

//     // Perform DFS on neighboring cells
//     dfs(grid, x + 1, y); // Right
//     dfs(grid, x - 1, y); // Left
//     dfs(grid, x, y + 1); // Down
//     dfs(grid, x, y - 1); // Up
// }

// int main() {
//     // Create a grid of cells
//     struct Cell grid[ROWS][COLS];
    
//     // Initialize the grid and mark all cells as unvisited
//     for (int i = 0; i < ROWS; i++) {
//         for (int j = 0; j < COLS; j++) {
//             grid[i][j].x = i;
//             grid[i][j].y = j;
//             grid[i][j].visited = 0;
//         }
//     }

//     // Call the DFS function starting from a specific cell (e.g., cell (0, 0))
//     dfs(grid, 0, 2);

//     return 0;
// }
