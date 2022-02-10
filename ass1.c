/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Yunfan Zeng 1273125
   Dated:     9/09/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/


/****************************************************************/

/* Stage one */
void init_board(int*);

/* Stage two */
int dupe_check(int, int, int*);
int board_valid(int*);

/* Stage three */
void create_cell_group(int, int*);
int is_unique_num(int*, int*);
int lin_search(int, int*, int*);
int strat_one(int*, int*);
void update_board(int, int*, int*);

/****************************************************************/

/* Main program controls all the action */
int 
main(int argc, char *argv[]) {
    int n, scan, not_finished;
	n = 0;
	not_finished = 1;
	int board[NCLL] = {0};
	int update[(NCLL * 2)] = {0};
	
    fill_c2s();
    
    while ((scanf("%d", & scan)) == 1) {
        board[n] = scan;
        n++;
    }

    /* Printing initial board */
    init_board(board);

    /* While changes are made through strat_one(), not_finished will remain
	 * true so that it can continue solving, if the board is not valid, the
	 * program will exit
     */
     
	/* Checks board validity */
	if (board_valid(board) != 1) {
		return 0;
	}
	
    while (not_finished) {
        /* Identifies changes */
        not_finished = strat_one(board, update);
        /* Implements changes */
        update_board(not_finished, board, update);
    }

    /* Printing final board after all possible changes are implemented */
    init_board(board);
    return 0;
}



/* Prints the formatted sudoku board with the number of unknown cells and 
 * "ta daa!!!" if solved.
 */
void
init_board(int *board) {
    int unknowns = 0;	/* Counts unknown cells */
    printf("\n");

    /* Prints all 81 cells of the board with dividers */
    for (int i = 0; i < NCLL; i++) {
        int cell_num = i + 1;

        /* Prints the values of the sudoku board */ 
        if (board[i] == 0) {
            printf(".");
            unknowns++;
        } else {
            printf("%d", board[i]);
        }

        /* Prints the dividers if applicable after values are added */
        if (cell_num % NDIG != 0) {
            printf(" ");
        }
        if (cell_num % (NDIG * NDIM) == 0 && cell_num != NCLL) {
            printf("\n------+-------+------\n");
        } else if (cell_num % NDIG == 0) {
            printf("\n");
        } else if (cell_num % NDIM == 0) {
            printf("| ");
        }
    }

    printf("\n%2d cells are unknown\n", unknowns);

    /* Completion condition */
    if (unknowns == 0) {
        printf("\nta daa!!!\n");
    }
}



/* Returns whether the board violates any rules of sudoku. Will state the 
 * incorrect row/col/sqr set and the number of the violations
 */
int 
board_valid(int *board) {
    int cell_id, cell_val, set_vio, vio, first_loop;
    set_vio = 0;
    vio = 0;
    first_loop = 1;

    // Checks every possible set for duplicate numbers
    for (int i = 0; i < NSET; i++) {
    	/* Need to reinitalise array to 0 every loop as not all array indexs
    	 * are replaced with each iteration and depends on the sudoku board
    	 */
        int duplicate[NDIG + 1] = {0}; 

        /* Increments array values to match number of occurences */
        for (int j = 0; j < NDIG; j++) {
            cell_id = s2c[i][j];
            cell_val = board[cell_id];
            duplicate[cell_val]++;
        }
        
        /* Checks number of violations per set and set violations */
        int num_of_vio = dupe_check(i, first_loop, duplicate);
        if (num_of_vio) {
            first_loop = 0;
            vio += num_of_vio;
            set_vio++;
        }
    }
    
    /* Prints violations if applicable */
    if (vio) {
        printf("\n%d different sets have violations\n", set_vio);
        printf("%d violations in total\n", vio);
        return 0;
    }
    return 1;
}



/* Checks if there are any duplicate numbers in the row, col, and sqr's of
 * the sudoku board
 */
int 
dupe_check(int i, int first_loop, int *duplicate) {
    int vio, set_num, conv_set_num, sets_per_group, dupe_num, dupe_num_occ;
    char *set_name;    
    vio = 0;

    /* Loops through a given sudoku set for any duplicate numbers */
    for (int j = 1; j <= NDIG; j++) {
        if (duplicate[j] > 1) {
            vio++;
            set_num = i;
            conv_set_num = i + 1;
            dupe_num = j;
            dupe_num_occ = duplicate[j];
            sets_per_group = (NSET / NGRP);

            /* (default row) Identifies whether a set is a col or sqr */ 
            set_name = "row";
            if (set_num >= sets_per_group * 2) {
                conv_set_num -= sets_per_group * 2;
                set_name = "sqr";
            } else if (set_num >= sets_per_group) {
                conv_set_num -= sets_per_group;
                set_name = "col";
            }

			if (first_loop) {
                printf("\n");
            }
            
            /* Prints current set number, its name, its number with respect to
             * its name, the number of duplicates and the duplicate number
             */
            printf("set %2d (%s %d): %d instances of %d\n",
                set_num, set_name, conv_set_num, dupe_num_occ, dupe_num);

        }
    }
    return vio;		/* Returns the validity of the set */
}



/* Uses strategy one to solve the sudoku and returns the length of the 
 * update[] array (in the form [cell_id, cell_value,...]) if changes are made
 * and 0 otherwise 
 */
int 
strat_one(int *board, int *update) {
    int cell_id, cell_val, cell_group[NGRP * NDIG], first_loop, changes, 
    buffer, miss_num;
    
    first_loop = 1;
    changes = 0;
    buffer = 0;

    /* Checks all cells except for known cells for a unique missing number */
    for (int i = 0; i < NCLL; i++) {
        cell_id = i;
        cell_val = board[cell_id];

        /* Skips filled cells */
        if (cell_val != 0) {
            continue;
        }

        /* Create an array of all three sets and attempts to find a missing num
         */
        create_cell_group(cell_id, cell_group);
        miss_num = is_unique_num(board, cell_group);

        if (miss_num) {
            if (first_loop) {
                printf("\nstrategy one\n");
                first_loop = 0;
            }

            /* Populates update[] with the information to update the board */
            update[buffer] = cell_id;
            update[buffer + 1] = miss_num;
            changes++;
            buffer += 2;
            printf("row %d col %d must be %d\n",
                rownum(cell_id), colnum(cell_id), miss_num);
        }
    }

    /* If changes were made, continue the loop in main, otherwise, stop */
    if (changes) {
        return buffer;
    }
    return 0;
}



/* Creates an array (cell_group[]) that includes the cell ids of all three
 * sets that a cell is a part of 
 */
void 
create_cell_group(int cell_id, int *cell_group) {
    int set1, set2, set3;

    /* Retrieve the three sets related to the cell */
    set1 = c2s[cell_id][0];
    set2 = c2s[cell_id][1];
    set3 = c2s[cell_id][2];

    /* Populate cell_group[] with the cell id's of the three sets */
    for (int j = 0; j < NDIG; j++) {
        cell_group[j] = s2c[set1][j];
        cell_group[j + NDIG] = s2c[set2][j];
        cell_group[j + (2 * NDIG)] = s2c[set3][j];
    }
}



/* Checks if there is only one missing unique number in the sets related to 
 * the cell. Returns the number if found and 0 otherwise.
 */
int 
is_unique_num(int *board, int *cell_group) {
	int max_val, min_val, count, miss_num;
    max_val = 9;
    min_val = 1;
    count = 0;
    miss_num = 0;
    
    /* Identify a unique missing number for the cells sets */
    for (int j = min_val; j <= max_val; j++) {
        if (lin_search(j, board, cell_group) != 1) {
            miss_num = j;
            count++;
        }
        /* Exit if a number occurs more than once */
        if (count >= 2) {
            return 0;
        }
    }
    return miss_num;
}



/* A linear search function that returns 1 if num found and 0 otherwise 
 */
int 
lin_search(int num, int *board, int *cell_group) {
    /* Checks every related cell (row, col, sqr) for the specified num */
    for (int i = 0; i < NGRP * NDIG; i++) {
        int cell_id = cell_group[i];

        if (board[cell_id] == num) {
            return 1;
        }
    }
    return 0;
}



/* Uses information from update[] to implement all solved numbers to the board
 */
void 
update_board(int n, int *board, int *update) {
    /* Update[] is in the form (cell id, cell value,...) */
    for (int i = 0; i < n; i += 2) {
        board[update[i]] = update[i + 1];
    }
}


/* algorithms are fun!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/****************************************************************/


