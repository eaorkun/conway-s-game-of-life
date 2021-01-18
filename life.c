#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
// life.c -- EE 312 Project 2

//
//new row identification
//improper malloc
//linux implemntation


/* Student information for project:
 *
 * Replace <NAME> with your name.
 *
 * On my honor, Eralp Orkun, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Eralp Orkun
 * email address: eaorkun@utexas.edu
 * UTEID: eao789
 * Section 5 digit ID: 16000
 * Date: 9/14/2020
 */

/* The populateWorld function reads the input file (which has the 0s and 1s)
 * and populate the world onto grid,
 * as well as noting the number of Rows and Columns.
 * Inputs: fname[]
 * Outputs: grid[], *numRows, *numCols
*/
void populateWorld(char fname[], char *grid[], int *numRows, int *numCols) {
    FILE *fp;
    char readVal;            //temporary storage for each read char in a row
    int countCols = 0;
    int countBtwRow = 0;
    bool readRow = true;
    fp = fopen(fname, "r");   // opening file for reading
    if(fp == NULL) {
        printf("Error opening file");
    }
    else {
        while(readRow) {    //count all valid elements in a row
            readVal = (char) fgetc(fp);
            if((readVal != '1') && (readVal != '0')) {
                readRow = false;
                countBtwRow++;
            }
            else {
                countCols++;
            }
        }
        *numCols = countCols; // Gets the number of Columns
        readRow = true;
        while(readRow) { //count any extra elements between rows (to account for weird text formatting)
            readVal = (char) fgetc(fp);
            if((readVal == '1') || (readVal == '0')) {
                readRow = false;
            }
            else {
                countBtwRow++;
            }
        }

        fclose(fp);                    //close file and
        fp = fopen(fname, "r");  //reopen to start at beginning
        char rowRead[(*numCols)+1];    //used to temporarily hold each line as string, dynamic allocation (+1 for null)
        while(fgets(rowRead, (*numCols)+1, fp) != NULL) { //reads each row until end of file
            static int countRows = 0;
            if(rowRead[strlen(rowRead)-1] == '\n') {             // Eliminate end-of-line char (just in case)
                rowRead[strlen(rowRead)-1] = '\0';
            }
            grid[countRows] = (char *) malloc((*numCols+1)*sizeof(char)); //dynamically allocate memory for grid
            for(int i = 0; i < *numCols; ++i) { //converts '1's & '0's to '*'s & '.'s
                if(rowRead[i] == '1') {
                    rowRead[i] = '*';
                }
                else if(rowRead[i] == '0') {
                    rowRead[i] = '.';
                }
                else {
                    printf("Grid Assignment Error \n");
                }
            }
            strcpy(grid[countRows], rowRead); //copy to grid
            countRows++;
            *numRows = countRows; //Updates the number of rows
            for(int i = 0; i < countBtwRow; i++) { //index to account for in-between chars
                readVal = (char) fgetc(fp);
            }
        }
        fclose(fp); //close file
    }
}

/* The showWorld function displays the state of the cells in using "*"s and "."s.
 * "*" = alive
 * "." = dead
 * Shows current generation (snapshot in time)
 * inputs: grid, numRows, numCols
 * outputs: print to console the current grid
*/
void showWorld(char *grid[], int numRows, int numCols) {
    for(int i = 0; i < numRows; ++i) { // prints grid row by row,
        printf("%s\n", grid[i]);       // grid is an array of strings
    }
}

/* Finds the number of alive
 * adjacent cells for a specified given cell.
 * Inputs: grid[], row, col, totalRow, totalCol
 * Outputs: Adjacent Alive cells
*/
int adjacentAlive(char *grid[], int row, int col, int totalRow, int totalCol) {
    int aliveCount = 0;
    for(int i = -1; i <= 1; ++i) {  //nested loop, checking 3x3 square around given point
        for(int j = -1; j <= 1; ++j) {
            if((row+i >= 0) && (row+i < totalRow) && (col+j >= 0) &&
               (col+j < totalCol) && ((grid[row+i][col+j] == '*') || (grid[row+i][col+j] == 'd'))) {
                aliveCount++;
            }
        }
    }
    if(grid[row][col] == '*') {  //subtracts 1 to adjust for self counting
        aliveCount = aliveCount-1;
    }
    return aliveCount;
}

/* The iterateGeneration function does most of the work,
 * evaluating each cell, and deciding whether it will die,
 * or live to see the next generation.
 * Inputs: grid[], numRows, numCols
 * Outputs: Updates grid[]
*/
void iterateGeneration(char *grid[], int numRows, int numCols) {
    for(int curRow = 0; curRow < numRows; curRow++) { //nested loop that goes to each point in 2D array
        for(int curCol = 0; curCol < numCols; curCol++) {
            if(grid[curRow][curCol] == '.') { // Prepares to update dead to alive if adjacent == 3
                int bornCount;
                bornCount = adjacentAlive(grid, curRow, curCol, numRows, numCols);
                if(bornCount == 3) {
                    grid[curRow][curCol] = 'a'; // Not immediate update so no interference with other calculations
                }
            }
            else if(grid[curRow][curCol] == '*') { // Prepares to update alive to dead if adjacent != 2 or 3
                int surviveCount;
                surviveCount = (adjacentAlive(grid, curRow, curCol, numRows, numCols));
                if((surviveCount != 2) && (surviveCount != 3)) {
                    grid[curRow][curCol] = 'd'; // Not immediate update so no interference with other calculations
                }
            }
            else {
                printf("BROKEN NEED FIX\n"); // for debugging
            }
        }
    }

    for(int curRow = 0; curRow < numRows; curRow++) {  //goes back through array and fixes update placeholders
        for(int curCol = 0; curCol < numCols; curCol++) {
            if(grid[curRow][curCol] == 'a') {
                grid[curRow][curCol] = '*';
            }
            if(grid[curRow][curCol] == 'd') {
                grid[curRow][curCol] = '.';
            }
        }
    }
}




