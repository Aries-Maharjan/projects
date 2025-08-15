#include <iostream>
#include <vector>

using namespace std;

#define N 9

// Define the Sudoku grid
int grid[N][N] = {
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

// Function to print the Sudoku grid
void printGrid() {
    for (int r = 0; r < N; r++) {
        for (int d = 0; d < N; d++) {
            if (d == 3 || d == 6)
                cout << " | ";
            cout << grid[r][d] << " ";
        }
        if (r == 2 || r == 5) {
            cout << endl;
            for (int i = 0; i < N; i++)
                cout << "---";
        }
        cout << endl;
    }
}
// Function to check if a number is present in a row
bool isInRow(int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Function to check if a number is present in a column
bool isInCol(int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Function to check if a number is present in a 3x3 box
bool isInBox(int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + startRow][col + startCol] == num)
                return true;
    return false;
}

// Function to check if a number can be placed at a specific position
bool isValid(int row, int col, int num) {
    return !isInRow(row, num) && !isInCol(col, num) && !isInBox(row - row % 3, col - col % 3, num);
}
// Function to find an empty cell in the grid
bool findEmptyCell(int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// Function to solve the Sudoku puzzle
bool solveSudoku() {
    int row, col;
    if (!findEmptyCell(row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku())
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}
// Function to play the game
void playGame() {
    int row, col, num;
    char choice;
    while (true) {
        printGrid();
        cout << "Enter row (1-9) and column (1-9) to place a number (or 0 0 to solve): ";
        cin >> row >> col;
        if (row == 0 && col == 0) {
            if (solveSudoku()) {
                cout << "Solved successfully!" << endl;
            } else {
                cout << "No solution exists!" << endl;
            }
            break;
        }
        cout << "Enter the number to place at [" << row << "," << col << "]: ";
        cin >> num;
        if (isValid(row - 1, col - 1, num)) {
            grid[row - 1][col - 1] = num;
        } else {
            cout << "Invalid move!" << endl;
        }
    }
}

int main() {
    playGame();
    return 0;
}
