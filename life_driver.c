//life_driver.c
//
//Life Driver program
//Roger Priebe 9/5/2018
//EE 312


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

//This file is a driver program for the life.c module.
//This program must work with your implementations life.h and life.c
//Do not change the function definitions for populateWorld, showWorld or
//iterateGeneration.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "life.h"

// Use ./life.c <file>.txt <#iterations> to run on linux
int main(int argc, char *argv[]) {
    //edit these two lines and use the command line arguments
    //char fName[] = "world.txt";  //uncomment for debugging
    char fName[35];
    strcpy(fName, argv[1]);
    //const int numGenerations = 11; //uncomment for debugging
    const int numGenerations = atoi(argv[2]); //uncomment for linux testing
    const int MAX_ROWS = 80; //we want the world to fit on one screen
    //array of strings that will hold the grid
    char *world[MAX_ROWS];
    int numRows;
    int numCols;
    populateWorld(fName, world, &numRows, &numCols);
    showWorld(world, numRows, numCols);
    for(int iteration = 0; iteration < numGenerations; iteration++) {
        // code to clear screen goes here
        // uncommment for Windows
        //system("cls"); //Windows only
        //printf("WIN\n");
        //uncommment for Linux
        system("clear"); //Linux only
        iterateGeneration(world, numRows, numCols);
        showWorld(world, numRows, numCols);
    }
    for(int i = 0; i < numRows; i++) {   // FREEING allocated memory for grid
        free(world[i]); //frees allocated memory from function populateWorld
    }
    return 0;
}



