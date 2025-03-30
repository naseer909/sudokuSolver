#include <iostream>
#include <vector>
using namespace std;

// Function to check if placing num at grid[row][col] is valid
bool isValid(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check if num is not in the current row
    for (int i = 0; i < 9; ++i) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check if num is not in the current column
    for (int i = 0; i < 9; ++i) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check if num is not in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle
bool solveSudoku(vector<vector<int>>& grid) {
    int row = -1;
    int col = -1;
    bool isFull = true;

    // Find an empty cell
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isFull = false;
                break;
            }
        }
        if (!isFull) {
            break;
        }
    }

    // If there are no empty cells, the puzzle is solved
    if (isFull) {
        return true;
    }

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;  // Place the number

            // Recursively attempt to solve the rest of the puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // If placing num doesn't solve the puzzle, reset the cell and backtrack
            grid[row][col] = 0;
        }
    }

    // If no number is valid, return false
    return false;
}

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Sample Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        cout << "Sudoku solved!" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}
