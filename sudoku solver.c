//sudoku puzzle solver
#include <stdio.h>

int main();

/*It calls functions to input the Sudoku grid, validate it, and attempt to solve it.
It then prints the solved puzzle or an error message if the puzzle is unsolvable.*/
int input_grid();

int validate_grid();
int solve_cell(int row, int column);
int is_valid(int row, int column, int value);
void print_grid();

int original[9][9], grid[9][9];

int main()
{
	if (! input_grid()) {
		printf("error: unable to input grid\n");
		return 0;
	}

	printf("\nvalidating puzzle... ");
	if (! validate_grid()) {
		printf("invalid!\n");
		return 0;
	}

	printf("valid.\n\nsolving following puzzle:\n");
	print_grid();

	if (! solve_cell(0, 0)) {
		printf("\nunfortunately, your puzzle is unsolvable\n");
		return 0;
	}

	printf("\npuzzle solved:\n");
	print_grid();
	return 0;
}
/* input_grid is responsible for taking user input for the Sudoku grid.
It prompts the user to enter the puzzle row by row, using numbers for known cells and '.' or '0' for missing cells.*/
int input_grid()
{
	int character, row, column;
	row = column = 0;

	printf("enter rows line by line. use numbers for known cells, ");
	printf("zero or dot for missing cells.\nrow 1: ");

	while (row < 9) {
		character = getchar();

		if ('0' <= character && character <= '9' || character == '.') {
			if (column > 8) {
				printf("error: each row has maximum 9 cells\n");
				return 0;
			}

			if (character != '.')
				original[row][column] =
					grid[row][column] = character - '0';

			column++;

		} else if (character == '\n') {
			column = 0;
			row++;

			printf("row %i: ", row + 1);
		}
	}

	return 1;
}
/* validate_grid checks if the initially input Sudoku grid is valid.
It ensures that no row, column, or 3x3 subgrid contains duplicate numbers, violating Sudoku rules.*/
int validate_grid()
{
	int i, j;

	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			if (grid[i][j])
				if (! is_valid(i, j, grid[i][j]))
					return 0;

	return 1;
}
/* solve_cell is a recursive function responsible for solving the Sudoku puzzle.
It attempts to fill each cell with a number from 1 to 9 while checking if the number is valid according to Sudoku rules.
If it successfully fills all cells, it returns 1, indicating success. If it cannot find a valid */
int solve_cell(int row, int column)
{
	int number = 1;

	if (column == 9) {
		column = 0;
		row++;
	}

	if (row == 9)
		return 1;

	while (number < 10) {
		if (is_valid(row, column, number)) {
			grid[row][column] = number;

			if (solve_cell(row, column + 1))
				return 1;
		}

		grid[row][column] = 0;

		number++;
	}

	return 0;
}
/* is_valid checks if placing a particular value in a cell at a given row and column is valid according to Sudoku rules.
It checks if the value is already present in the row, column, or 3x3 subgrid and returns 1 if it's a valid placement, and 0 if it's not.*/
int is_valid(int row, int column, int value)
{
	int i, j, r, c;

	if (original[row][column] != 0)
		if (original[row][column] != value)
			return 0;

	for (i = 0; i < 9; i++) {
		if (i != column)
			if (grid[row][i] == value)
				return 0;

		if (i != row)
			if (grid[i][column] == value)
				return 0;
	}

	r = (row / 3) * 3;
	c = (column / 3) * 3;
	for (i = r; i < r + 3; i++)
		for (j = c; j < c + 3; j++)
			if (i != row || j != column)
				if (grid[i][j] == value)
					return 0;

	return 1;
}

void print_grid()
{
	int i, j;

	for (i = 0; i < 10; i++) {
		if (i % 3 == 0)
			printf("+-------+-------+-------+\n");

		if (i == 9)
			return;

		for (j = 0; j < 9; j++) {
			if (j % 3 == 0)
				printf("| ");

			grid[i][j] != 0 ? printf("%d ", grid[i][j]) : printf(". ");
		}

		printf("|\n");
	}
}











