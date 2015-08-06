//
//  Maz.cpp
//  
//
//  Created by Winnie Wong on 2015-06-04.
//
//

#include "MazeSolver.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#define NUMROWS 15
#define NUMCOLS 15

using namespace std;

int numPaths = 0;
int expected = 0;
char array[100];

// Pre-Condition: Must have a 15x15 maze with a definitive solution, a non-negative i and j value, and a valid index value within the global array
// Post-Condition: Solve and print out valid paths to the exit in the maze. If maze exit location has more than one solution, maze will take the quickest and most convenient path.

void generate_all_paths(char maze[NUMROWS][NUMCOLS], int i, int j, int index) {
    
    if (j == (NUMCOLS - 1)) {
        numPaths++;
    cout << "Path " << numPaths << ": ";
    for (int i = 0; i < index; i++) {
        cout << array[i] << ", ";
    }
        cout << array[index] << endl;
        
        if (numPaths == expected) {
            cout << numPaths << " total paths" <<endl;
        }
    }

    if ((maze[1][0] != '#') && (i == 1) && (j == 0)) { //start condition
        //index should be 0
        array[index] = maze[1][0];
        maze[1][0] = '1';
        for (int e = 0; e < NUMCOLS; e++) {
            if (maze[e][NUMCOLS-1] != '#' && maze[e][NUMCOLS - 2] != '#') {
                expected++;
            }
        }
    }
    
    
    
    if ((maze[i][j+1] != '#') && (maze[i][j+1] != '1')) { //right
        array[index+1] = maze[i][j+1];
        maze[i][j+1] = '1';
        generate_all_paths(maze, i, j+1, index + 1);
    }
    
    
    if ((maze[i][j-1] != '#') && (maze[i][j-1] != '1')) { //left
        array[index+1] = maze[i][j-1];
        maze[i][j-1] = '1';
        generate_all_paths(maze, i, j-1, index+1);
    }
    
    
    
    if ((maze[i-1][j] != '#') && (maze[i-1][j] != '1')) { //up
        array[index + 1] = maze[i-1][j];
        maze[i-1][j] = '1';
        generate_all_paths(maze, i-1, j, index+1);
    }
    
    if ((maze[i+1][j]!= '#') && (maze[i+1][j] != '1')) { //down
        array[index+1] = maze[i+1][j];
        maze[i+1][j] = '1';
        generate_all_paths(maze, i+1, j, index+1);
    }
    
    
    
    
}

// Pre-condition: Has a valid 15x15 maze named "maze.txt"
// Post-condition: Fill in rows and columns of maze starting with position 0. If there is an error readimg the maze, return 0, otherwise return 1.
// Referenced from http://www.cs.columbia.edu/~sable/summer2000/maze.c

int read_maze(char maze[NUMROWS][NUMCOLS], int *sRow, int *sCol) {
    
    FILE *fpMaze;
    int row, col;
    
    //Open maze text file and make sure it opens
    if ((fpMaze = fopen("maze.txt", "r")) == NULL) {
        cout << "Could not open" << endl;
        return 0;
    }
    
    for (row = 0; row < NUMROWS; row++) {
        for (col = 0; col < NUMCOLS; col++) {
            maze[row][col] = getc(fpMaze);
            
            //Check if this is starting position
            if (maze[row][col] == '0') {
                *sRow = row;
                *sCol = col;
            }
        }
        
        //Ignore newline at end of each row
        getc(fpMaze);
    }
    return 1;
}

// Main function
// Assume that maze will only consist of characters {#,a,b,c,d,...,z}
// Assume that maze will never have 2 of the same characters beside each other
// Assume there are no loops in the maze
// Referenced from http://www.cs.columbia.edu/~sable/summer2000/maze.c

int main() {
    
    char maze[NUMROWS][NUMCOLS];
    int startRow, startCol; //starting point in maze
    
    if (read_maze(maze, &startRow, &startCol) == 0) { //try to read the maze file
        printf( "Error reading maze from file maze.txt!\n");
        return 0;
    }
    
    generate_all_paths(maze, 1, 0, 0); //starting point always [1][0]
    
    return 0;
}
# MazeSolver
