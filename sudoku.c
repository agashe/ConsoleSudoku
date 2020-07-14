/**
 * Sudoku 1.0 (14/7/2020)
 * Auther: Mohamed Yousef (modi401@hotmail.com)
 * License: Open Source.
 */

/* ************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define ROWS 9
#define COLS 9

#define TRUE  1
#define FALSE 0

#define ENTER 10

char map[ROWS][COLS];
char org[ROWS][COLS];

/* ************************************** */

char welcome_message(){
    char answer = 0;

    puts(" ######### ##     ## ########  ######### ##     ## ##     ## ");
    puts(" ##        ##     ## ##     ## ##     ## ##   ##   ##     ## ");
    puts(" ######### ##     ## ##     ## ##     ## #####     ##     ## ");
    puts("        ## ##     ## ##     ## ##     ## ##   ##   ##     ## ");
    puts(" ######### ######### ########  ######### ##     ## ######### \n");
    puts("             2020 (C) CREATED BY MOHAMED YOUSEF              \n");
    puts("                   press ENTER to start                      ");

    // Check user's input.
    scanf("%c", &answer);
    
    if (answer == ENTER) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void init_layout(){
	int i, j;

	for (i = 0;i < ROWS;i++) {
		for (j = 0;j < COLS;j++) {
			map[i][j] = org[i][j];
		}
	}	
}

void clear(){
	system("@cls||clear");
}

int rand_num(int min, int max){
	return (rand() % (max-min+1)) + min;
}

char check_row(int row, int val){
	int k;

	// check if the value repeated in the row!!
	for (k = 0;k < ROWS;k++) {
		if (org[row][k] == val) {
			return FALSE;
		}
	}

	return TRUE;
}

char check_col(int col, int val){
	int k;

	// check if the value repeated in the column!!
	for (k = 0;k < COLS;k++) {
		if (org[k][col] == val) {
			return FALSE;
		}
	}

	return TRUE;
}

char check_box(int row, int col, int val){
	int i, j, start_row, start_col;

	// decide box start(row, col)
	if (row < 3) start_row = 0;
	else if (row < 6) start_row = 3;
	else start_row = 6;
	
	if (col < 3) start_col = 0;
	else if (col < 6) start_col = 3;
	else start_col = 6;

	// check all the 9 blocks of the box
	for (i = 0;i <= 2; i++) {
		for (j = 0;j <= 2; j++) {
			if (org[start_row+i][start_col+j] == val) 
				return FALSE;
		}
	}

	return TRUE;
}

void generate_sudoku(){
	int i, j, val;

	for (i = 0;i < ROWS;i++) {
		for (j = 0;j < COLS;j++) {
			val = rand_num(1, 9);
			if (check_row(i, val) && check_col(j, val) && check_box(i, j, val)) {
				org[i][j] = val;
			}
		}
	}
}

void draw_layout(){
	int i, j, k;
	
	/* Print Column Letters */
	for (i = 0;i < COLS;i++) {
		if (i == 0)
			printf("    ");
					
		printf("%c   ", (65+i));

		if (i == 2 || i == 5 || i == 8)
			printf("   ");
	}
	
	/* Print Map */
	for (i = 0;i < ROWS;i++) {
		/** empty line after letters line **/
		if (i == 0)
			printf("\n\n");

		/** dashed line before rows in middle **/
		if (i == 0 || i == 3 || i == 6) {
			printf("   ");
			for (k = 0;k < (COLS+26);k++) {
				if (k == 11 || k == 23)
					printf("    ");
				else 
					printf("-");
			}

			printf("\n");
		}

		/** print the row number and the values!! **/
		printf("%d |", i+1);
		
		for (j = 0;j < COLS;j++) {
			if (org[i][j] != 0) {
				printf(" %d`|", map[i][j]);
			}
			else if (org[i][j] == 0 && map[i][j] != 0) {
				printf(" %c |", map[i][j]);
			}
			else {
				printf("   |");
			}

			if (j == 2 || j == 5)
				printf("  |");
		}
		
		printf("\n");
		
		/** dashed line after each row **/
		printf("   ");
		for (k = 0;k < (COLS+26);k++) {
			if (k == 11 || k == 23)
				printf("    ");
			else 
				printf("-");
		}

		printf("\n");

		/** separate each 3 rows with empty line **/
		if (i == 2 || i == 5 || i == 8)
			printf("\n");
	}
}

void process(char *command){
	if (command[0] == '\0' && command[1] == '\0' && command[2] == '\0' && command[3] == '\0')
		return;
		
	if (command[0] < 97 || command[0] > 105)
		return;
	else if (command[1] < 49 || command[1] > 57)
		return;
	else if (command[2] != '=')
		return;
	else if (command[3] < 49 || command[3] > 57)
		return;

	/* else */
	if (org[(command[1]-49)][(command[0]-97)] == 0) {
		map[(command[1]-49)][(command[0]-97)] = command[3];
	}
}

char check_win(){
	int i, j;

	// check if the map correct
	for (i = 0;i < ROWS;i++) {
		for (j = 0;j < COLS;j++) {
			if (!check_row(i, map[i][j]) || !check_col(j, map[i][j]) || !check_box(i, j, map[i][j])) {
				return FALSE;
			}
		}
	}

	return TRUE;
}

void main(){
	char command[4] = "";
	
	/* ********************* */
	
	clear();
	if (!welcome_message()) return;
	
	/* ********************* */

	srand(time(0));
	generate_sudoku();
	init_layout();
	
	/* ********************* */
	
	while(strcmp(command, "quit") != 0) {
		clear();
		draw_layout();
		
		printf("Enter Command:\n");
		scanf("%s", command);
		process(command);
		
		if (check_win()) {
			clear();
			printf("***** Congratulations , You Win! *****\n");
			return;
		}
	}

	/* ********************* */
	
	printf("Bye Bye\n");
}
