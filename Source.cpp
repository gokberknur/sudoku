
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "color.h"


/* Term Project for SE420 - 2015-2016 Spring
Kazım Gökberk Nur
20100601028


// Color.h library I found it from internet also, I used for painting cout function

CSP - Backtracking Method Implementation, Sudoku solving
This alghorithm implemented via using this source: https://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf

Logic behind this (backtracking):

-	Find row, col of an unassigned cell
-	If there is none, return true
-	For digits from 1 to 9
-	a) If there is no conflict for digit at row,col
-	assign digit to row,col and recursively try fill in rest of grid
-	b) If recursion successful, return true
-	c) Else, remove digit and try another
-	If all digits have been tried and nothing worked, return false
*/


// Defining size of sudoku, as we know sudoku game is 9x9 game 
#define Size 9
using namespace std;

// This function finds an entry in Sudoku that is still unassigned
bool FindEmptySpot(int Sudoku[Size][Size], int &row, int &col);

// check if there are 0's 
bool IsOkay(int Sudoku[Size][Size], int row, int col, int num);


// send to our prepared sudoku problem and try to assign values to available places (zeros (0's))
bool SolveSudoku(int Sudoku[Size][Size])
{
	int row, col;


	//If there are no "0"'s in the array return true, and problem solved yaaaaaaay!
	if (FindEmptySpot(Sudoku, row, col) == false)
		return true; // success!

					 // cout << "Iam row\t =" << row << " \tI am col \t =" << col;
					 // valid numbers are 1 to 9 
	for (int num = 1; num <= 9; num++)
	{
		// if it is okay
		if (IsOkay(Sudoku, row, col, num) == true)
		{
			// assign it temporary
			Sudoku[row][col] = num;

			// return, if success, yay!
			if (SolveSudoku(Sudoku) == true)
				return true;


			//solution is not possible set that value to 0 and call the function again
			Sudoku[row][col] = 0;
		}
	}
	return false; // recursive, backtracking
}

/* Searches the Sudoku to find an entry that is still unassigned. If
found, the reference parameters row, col will be set the location
that is unassigned, and true is returned. If no unassigned entries
remain, false is returned. */

//Finds empty spots (zero(0)'s) and  if finds, ref parameters 
bool FindEmptySpot(int Sudoku[Size][Size], int &row, int &col)
{
	for (row = 0; row < Size; row++)
		for (col = 0; col < Size; col++)
			if (Sudoku[row][col] == 0)
				return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
in the specified row matches the given number. */
bool UsedInRow(int Sudoku[Size][Size], int row, int num)
{
	for (int col = 0; col < Size; col++)
		if (Sudoku[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
in the specified column matches the given number. */
bool UsedInCol(int Sudoku[Size][Size], int col, int num)
{
	for (int row = 0; row < Size; row++)
		if (Sudoku[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
within the specified 3x3 box matches the given number. */
bool UsedInBox(int Sudoku[Size][Size], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (Sudoku[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

/* Returns a boolean which indicates whether it will be legal to assign
num to the given row,col location. */

bool IsOkay(int Sudoku[Size][Size], int row, int col, int num)
{


	// Checks if that number already exist in current row and it's column and inside the it's 3x3 box

	return	!UsedInRow(Sudoku, row, num) &&
		!UsedInCol(Sudoku, col, num) &&
		!UsedInBox(Sudoku, row - row % 3, col - col % 3, num);
}

/* A utility function to print Sudoku  */
void Show(int Sudoku[Size][Size])
{
	cout << "*****\t SOLUTION \t *****\n";

	for (int row = 0; row < Size; row++)
	{
		if (row == 3 || row == 6) {
			printf("\n");
		}
		for (int col = 0; col < Size; col++) {

			if (col == 3 || col == 6) {
				printf("\t");
			}

			printf("%2d", Sudoku[row][col]);
		}
		printf("\n");

	}
}

//Showing which position we are entering, selected position painted with red on the line 173
// on line 177 we are coloring other positions with white.
void ShowInput(int Sudoku[Size][Size], int a, int b)
{
	for (int row = 0; row < Size; row++)
	{
		if (row == 3 || row == 6) {
			printf("\n");
		}
		for (int col = 0; col < Size; col++) {

			if (col == 3 || col == 6) {
				printf("\t");
			}

			if (row == a && col == b) {
				//Painting red to selected value
				cout << red;
				printf("%2d", Sudoku[row][col]);
				//resetting color (default is white
				cout << white;
			}
			else {
				printf("%2d", Sudoku[row][col]);
			}
		}
		printf("\n");

	}
}

int main()
{
	// 0 represents empty location
	// This is sample sudoku you can solve it using these lines:
	/*	if (SolveSudoku(Sudoku) == true)
		Show(Sudoku);
		else
		printf("Solution is not possible check it again");
		system("PAUSE"); 
		
		*/
	int Sudoku[Size][Size] = { 
								{ 1, 6, 4,	 0, 0, 0,	0, 0, 2 },
								{ 2, 0, 0,	 4, 0, 3,	9, 1, 0 },
								{ 0, 0, 5,	 0, 8, 0,	4, 0, 7 },

								{ 0, 9, 0,	 0, 0, 6,	5, 0, 0 },
								{ 5, 0, 0,	 1, 0, 2,	0, 0, 8 },
								{ 0, 0, 8,	 9, 0, 0,	0, 3, 0 },

								{ 8, 0, 9,	 0, 4, 0,	2, 0, 0 },
								{ 0, 7, 3,	 5, 0, 9,	0, 0, 1 },
								{ 4, 0, 0,	 0, 0, 0,	6, 7, 9 }
								};

	//Initialize empty sudoku. full of zero's
	int a[9][9] = { 0 };

	//Start filling sudoku, for empty spaces enter zero (0)
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			int temp = a[i][j];

			//Info texts
			cout << "If you are done with entering  puzzle enter -1\n";
			cout << "Enter " << i + 1 << ".Row " << j + 1 << ".Column of sudoku\n";
			//ShowInput function is for painting cout function. This is for location which position you're entering.
			
			ShowInput(a, i, j);
			//Ask number 
			cin >> temp;
			//Number has to be between 1 and zero
			if (temp > 9 || temp < -1) {
				cout << "******** \t Enter a valid number \t ********* \n";
				//IF users enters invalid value, go back to loop and do "j-1" because we don't want to fill that position with invalid number
				j--;
				continue;
			}

			//If user enters -1 call solve function 
			if (temp == -1) {

				if (SolveSudoku(a) == true){
					Show(a);
					break;
				}
				else {
					//If solution not possibble this will be printed
					printf("Solution is not possible check it again");
				system("PAUSE");
				}
			}
			else {
				//IF user enters a valid number assign it to selected position in the array
				a[i][j] = temp;
			}
			//this is for clearing screen, makes the cmd screen more cool and pretty :) 
			system("cls");
		}
	}

	


	
	system("PAUSE");
	return 0;


}

