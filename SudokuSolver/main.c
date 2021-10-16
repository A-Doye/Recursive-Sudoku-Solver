#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/////////////////////////////////////////////
//
// Recursive Sudoku Solver
//
// Author: Alexander Doye
// Version: 1.0
// Completed: 09/10/2021
//
/////////////////////////////////////////////

void printSudoku(int **sudokuGrid);

// Returns true if the new value can be placed according to the rules of Sudoku
bool validSolution(int **testGrid, int newVal, int row, int col);

// Returns true if empty cell is found, and sets row and column to its location
bool findEmptyCell(int **sudokuGrid, int *row, int *column);

// Solves the puzzle, recursively
bool solveSudoku(int **sudokuGrid);

int main() {
    printf("-----------------------------\n\n"
           "  ~RECURSIVE SUDOKU SOLVER~\n\n"
           "-----------------------------\n\n");

    // Empty grid creation
    int **sudokuGrid;
    sudokuGrid = malloc(sizeof(int*) * 9);

    for (int i = 0; i < 9; i++) {
        sudokuGrid[i] = malloc(sizeof(int*) * 9);
    }

    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            sudokuGrid[i][j] = 0;
        }
    }

    // Hard code in values to be solved
    sudokuGrid[0][0] = 5;
    sudokuGrid[0][1] = 3;
    sudokuGrid[0][4] = 7;

    sudokuGrid[1][0] = 6;
    sudokuGrid[1][3] = 1;
    sudokuGrid[1][4] = 9;
    sudokuGrid[1][5] = 5;

    sudokuGrid[2][1] = 9;
    sudokuGrid[2][2] = 8;
    sudokuGrid[2][7] = 6;

    sudokuGrid[3][0] = 8;
    sudokuGrid[3][4] = 6;
    sudokuGrid[3][8] = 3;

    sudokuGrid[4][0] = 4;
    sudokuGrid[4][3] = 8;
    sudokuGrid[4][5] = 3;
    sudokuGrid[4][8] = 1;

    sudokuGrid[5][0] = 7;
    sudokuGrid[5][4] = 2;
    sudokuGrid[5][8] = 6;

    sudokuGrid[6][1] = 6;
    sudokuGrid[6][6] = 2;
    sudokuGrid[6][7] = 8;

    sudokuGrid[7][3] = 4;
    sudokuGrid[7][4] = 1;
    sudokuGrid[7][5] = 9;
    sudokuGrid[7][8] = 5;

    sudokuGrid[8][4] = 8;
    sudokuGrid[8][7] = 7;
    sudokuGrid[8][8] = 9;

    printf("Unsolved sudoku:\n");
    printSudoku(sudokuGrid);

    solveSudoku(sudokuGrid);

    printf("\nSolved sudoku:\n");
    printSudoku(sudokuGrid);

    free(sudokuGrid);

    return 0;
}

void printSudoku(int **sudokuGrid) {
    //printf("Lets go!");
    int rowDivide = 0;
    for (int i = 0; i<9; i++) {
        int columnDivide = 0;
        //printf("I'm run");
        for (int j = 0; j<9; j++) {
            printf(" %d ", sudokuGrid[i][j]);
            columnDivide++;
            if (columnDivide%3 == 0 && columnDivide < 7) {
                printf("|");
            }
        }
        printf("\n");
        rowDivide++;
        if (rowDivide%3 == 0 && rowDivide < 7) {
            printf("---------+---------+---------\n");
        }
    }
}

bool validSolution(int **testGrid, int newVal, int row, int col) {

    // Find its box and check if its already present
    int boxRow = row, boxCol = col;
    boxRow = boxRow-(boxRow%3);
    boxCol = boxCol-(boxCol%3);

    for (int i = boxRow; i<boxRow+3; i++) {
        for (int j = boxCol; j < boxCol + 3; j++) {
            // Skip comparing against the target square (though this shouldn't matter as it should always be 0)
            if (row == i && col == j) {
                continue;
            }
            if (newVal == testGrid[i][j]) {
                return false;
            }
        }
    }

    // Test if it already exists in the row / column
    for (int i = 0; i<9; i++) {
        if (col == i) {
            continue;
        }
        if (testGrid[row][i] == newVal) {
            return false;
        }
    }

    for (int i = 0; i<9; i++) {
        if (row == i) {
            continue;
        }
        if (testGrid[i][col] == newVal) {
            return false;
        }
    }

    // If we reach here we know all tests have been passed, so it must be a valid placement
    return true;
}

bool findEmptyCell(int **sudokuGrid, int *row, int *column) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(!sudokuGrid[i][j]) {
                *row = i;
                *column  = j;

                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int **sudokuGrid) {
    int row;
    int col;

    if(!findEmptyCell(sudokuGrid, &row, &col)) return true;

    // Solves the sudoku recursively, marking dead ends with 0's if reached
    for (int guess = 1; guess < 10; guess++) {
        if (validSolution(sudokuGrid, guess, row, col)) {
            sudokuGrid[row][col] = guess;

            if(solveSudoku(sudokuGrid)) return true;
            sudokuGrid[row][col] = 0;
        }
    }
    return false;
}
