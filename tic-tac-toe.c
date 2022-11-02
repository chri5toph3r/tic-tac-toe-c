#include <stdio.h>

#define TRUE		1
#define FALSE		0
#define BLANK 		'-'
#define SYMBOL_ONE	'o'
#define SYMBOL_TWO	'x'

int last_row;
int last_col;


// fills the board pointer points to, with given character
//////////////////////////////////////////////////////////
void fill_board(char (*symbols_list)[3][3], char blank) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			(*symbols_list)[row][col] = blank;
		}
	}
}

// prints in the console board pointer point
////////////////////////////////////////////
void print_board(char (*symbols_list)[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			printf("%c", (*symbols_list)[row][col]);
		}
		printf("\n");
	}
	printf("\n");
}

// ask for symbol and check if its correct
//////////////////////////////////////////
int write_symbol(char (*symbols)[3][3], char symbol) {

	char col_letter;
	int row;
	int col;

	printf("Give col row: ");
	fflush(stdout);
	scanf("%c %i", &col_letter, &row);

	row--;

	if (!(row >= 0 && row < 3)) {
		return FALSE;
	} // if row incorrect

	switch (col_letter) {
		case 'A':
		case 'a':
			col = 0;
			break;
		case 'B':
		case 'b':
			col = 1;
			break;
		case 'C':
		case 'c':
			col = 2;
			break;
		default:
			return FALSE;
	}

	if ((*symbols)[row][col] != BLANK) {
		return FALSE;
	}

	last_row = row;
	last_col = col;
	(*symbols)[row][col] = symbol;

	return TRUE;
}

int check_winner(char (*symbols)[3][3]) {
	// check row
	if (((*symbols)[last_row][0] == (*symbols)[last_row][1]) &&
		((*symbols)[last_row][1] == (*symbols)[last_row][2])) {
		return TRUE;
	}

	// check column
	if (((*symbols)[0][last_col] == (*symbols)[1][last_col]) &&
		((*symbols)[1][last_col] == (*symbols)[2][last_col])) {
		return TRUE;
	}

	// check diagonal
	int diag_t_b[3][2] = {{0, 0}, {1, 1}, {2, 2}};

	// loop through diag_t_b array
	for (int tile = 0; tile < 3; tile++) {
		if (diag_t_b[tile][0] == last_row) {
			if (diag_t_b[tile][1] == last_col) {

				if (((*symbols)[diag_t_b[0][0]][diag_t_b[0][1]] == (*symbols)[diag_t_b[1][0]][diag_t_b[1][1]]) &&
					((*symbols)[diag_t_b[1][0]][diag_t_b[1][1]] == (*symbols)[diag_t_b[2][0]][diag_t_b[2][1]])) {
						return TRUE;
				}
			}
		}
	}

	// check diagonal /
	int diag_b_t[3][2] = {{2, 0}, {1, 1}, {0, 2}};

	// loop through diag_b_t array
	for (int tile = 0; tile < 3; tile++) {
		if (diag_b_t[tile][0] == last_row) {
			if (diag_b_t[tile][1] == last_col) {

				if (((*symbols)[diag_b_t[0][0]][diag_b_t[0][1]] == (*symbols)[diag_b_t[1][0]][diag_b_t[1][1]]) &&
					((*symbols)[diag_b_t[1][0]][diag_b_t[1][1]] == (*symbols)[diag_b_t[2][0]][diag_b_t[2][1]])) {
						return TRUE;
				}
			}
		}
	}
	return FALSE;
}


int main() {

	char symbols[2] = {SYMBOL_ONE, SYMBOL_TWO};
	char board[3][3];
	char turn = 0;

	fill_board(&board, BLANK);

	char filler = 'n';

	int is_winner = FALSE;
	while(!is_winner && turn < 9)
	{
		if (write_symbol(&board, symbols[turn%2]))
		{
			print_board(&board);
			is_winner = check_winner(&board);
			if (!is_winner) {
				turn++;
			}
		}
		scanf("%c", &filler);

	}
	if (is_winner){
		printf("%c won", symbols[turn%2]);
	} else {
		printf("no one won");
	}
	return 0;
}
