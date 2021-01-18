// life.h
// -- EE 312 Project 2

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
 *///
// Created by priebe on 9/5/2018.
//

#ifndef UNTITLED1_LIFE_H
#define UNTITLED1_LIFE_H

/* The populateWorld function reads the input file (which has the 0s and 1s)
 * and populate the world onto grid,
 * as well as noting the number of Rows and Columns.
 * Inputs: fname[]
 * Outputs: grid[], *numRows, *numCols
*/
void populateWorld(char fname[], char *grid[], int *numRows, int *numCols);

/* The showWorld function displays the state of the cells in using "*"s and "."s.
 * "*" = alive
 * "." = dead
 * Shows current generation (snapshot in time)
 * inputs: grid, numRows, numCols
 * outputs: print to console the current grid
*/
void showWorld(char *grid[], int numRows, int numCols);

/* The iterateGeneration function does most of the work,
 * evaluating each cell, and deciding whether it will die,
 * or live to see the next generation.
 * Inputs: grid[], numRows, numCols
 * Outputs: Updates grid[]
*/
void iterateGeneration(char *grid[], int numRows, int numCols);

#endif //UNTITLED1_LIFE_H