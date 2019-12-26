#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BOOLEAN unsigned short
#define TRUE 1
#define FALSE 0
#define MAXSIZECOL 12
#define MAXSIZEROW 12
#define ZERO 0
#define MAXSTRINGSIZE 1000
#define IS_MINE -1
#define EXTRA_COL 2
#define EXTRA_ROW 2
#define TEN 10
#define TWO 2
#define ONE 1
#define END_INPUT 999
#define HIDE_CHAR '.'

//definding struct of item in the board.
typedef struct
{
	short value_in_cube;
	BOOLEAN is_opened;
} cube_in_board;

void init_board(cube_in_board *ptr_board)
{
	cube_in_board *ptr_end_board = ptr_board + (MAXSIZECOL + EXTRA_COL) * (MAXSIZEROW + EXTRA_ROW);
	while (ptr_board < ptr_end_board)
	{
		ptr_board->value_in_cube = ZERO;
		ptr_board->is_opened = FALSE;
		ptr_board++;
	}
	ptr_end_board->value_in_cube = ZERO;
	ptr_end_board->is_opened = FALSE;
}

void print_row(cube_in_board **ptr_board)
{
	for (int i = ZERO; i < MAXSIZECOL; i++)
	{
		((*ptr_board)->is_opened == TRUE) ? printf("%3hd", (*ptr_board)->value_in_cube):
			printf("%3c", HIDE_CHAR);
		(*ptr_board)++;
	}
}

void print_board(cube_in_board *ptr_board)
{
	cube_in_board *ptr_start = ptr_board;
	cube_in_board *ptr_board_last_address = ptr_board + (MAXSIZECOL) * (MAXSIZEROW)+(MAXSIZECOL+EXTRA_COL);
	while (ptr_board < ptr_board_last_address)
	{
		print_row(&ptr_board);

		printf("\n");

		ptr_board++;
		ptr_board++;
	}
}

void insert_mines_to_the_board(char mines[])
{
	printf("please enter your mines: \n");
	gets(mines);
}

short string_to_value(char **ptr_str)
{
	short number = ZERO;
	while (**ptr_str != ' ' && **ptr_str != "" && **ptr_str != '\0')
	{
		number = number * TEN + **ptr_str - '0';
		*((*ptr_str)++);
	}
	(**ptr_str != '\0') ? *((*ptr_str)++) : ZERO;
	return number;
}

void set_mines_in_the_board(cube_in_board (*ptr_board)[MAXSIZECOL +EXTRA_COL], short **ptr_array, short *size)
{
	char mines[MAXSTRINGSIZE];
	insert_mines_to_the_board(mines);
	char *ptr = &mines[ZERO];
	short temp;
	short x;
	short y;
	while (*ptr != '\0' &&  *ptr != "")
	{
		temp = string_to_value(&ptr);
		x = temp;

		*ptr_array = (short*)realloc(*ptr_array, sizeof(short)*(++(*size)));
		*(*ptr_array+ (*size) - ONE) = x;

		temp = string_to_value(&ptr);
		y = temp;

		*ptr_array = (short*)realloc(*ptr_array, sizeof(short)*(++(*size)));
		*(*ptr_array + (*size) - ONE) = y;

		ptr_board[x][y].value_in_cube = IS_MINE;
	}
}


void mine_around(cube_in_board board[][MAXSIZECOL+EXTRA_COL], int row, int col)
{
	for (short counter = ZERO; counter <= TWO; counter++)
	{
		(board[row][col + counter].value_in_cube != IS_MINE) ? board[row][col + counter].value_in_cube += 1 : ZERO;
	}
}

void find_mines_and_set_value(cube_in_board board[][MAXSIZECOL+EXTRA_COL], short *ptr_array, short size)
{
	int counter = ZERO;
	int x;
	int y;
	short *ptr_end = ptr_array + size;
	while ( ptr_array != ptr_end )
	{
		x = *ptr_array;
		ptr_array++;
		y = *ptr_array;
		ptr_array++;
		for (short counter = -ONE; counter < TWO ; counter++)
		{
			mine_around(board , x + counter , y - ONE);
		}
	}
}

void end_game_message(unsigned short number)
{
	(number == ONE) ? printf("you stepped on a mine. \n"):ZERO;
	(number == TWO) ? printf("you won!! \n"):ZERO;
}

void main(void)
{
	short *ptr_array = NULL;
	unsigned short size = ZERO;
	short amount_of_mines_in_board;
	unsigned short amount_of_open_cubes = ZERO;
	unsigned short result = ZERO;
	cube_in_board board[MAXSIZEROW + EXTRA_ROW][MAXSIZECOL + EXTRA_COL];
	cube_in_board *ptr_start = &board[ZERO][ZERO];
	init_board(ptr_start);
	cube_in_board *ptr_player_board = &board[ONE][ONE];
	set_mines_in_the_board(ptr_start, &ptr_array, &size);
	print_board(ptr_player_board);
	printf("\n");
	find_mines_and_set_value(ptr_start, ptr_array, size);
	amount_of_mines_in_board = size / TWO;
	free(ptr_array);
	print_board(ptr_player_board);
	printf("\n");
	short x;
	short y;
	printf("please enter the row:");
	scanf("%hd", &x);
	(x == END_INPUT) ? result = END_INPUT : ZERO;
	while (!result)
	{
		printf("please enter the column:");
		scanf("%hd", &y);

		if (board[x][y].value_in_cube == IS_MINE)
		{
			result = ONE;
		}
		else
		{
			(board[x][y].is_opened == TRUE) ? printf("you already opened this cube.\n") : amount_of_open_cubes++;;
			(amount_of_open_cubes + amount_of_mines_in_board == MAXSIZECOL * MAXSIZEROW) ? result = TWO : ZERO;
		}
		board[x][y].is_opened = TRUE;
		print_board(ptr_player_board);
		if (!result)
		{
			printf("\nplease enter the row:");
			scanf("%hd", &x);
		}
		
	}
	end_game_message(result);
	printf("game over\n");
	scanf("%hu", &x);
}