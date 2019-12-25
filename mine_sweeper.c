#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BOOLEAN unsigned short
#define TRUE 1
#define FALSE 0
#define MAXSIZECOL 4
#define MAXSIZEROW 4
#define ZERO 0
#define MAXSTRINGSIZE 1000
#define IS_MINE -1
#define ABS(x) ((x)<0)?-(x):(x) 

//definding struct of item in the board.
typedef struct
{
	short value_in_cube;
	BOOLEAN is_opened;
} cube_in_board;

void init_board(cube_in_board *ptr_board)
{
	cube_in_board *ptr_end_board = ptr_board + (MAXSIZECOL + 2) * (MAXSIZEROW + 2);
	while (ptr_board < ptr_end_board)
	{
		ptr_board->value_in_cube = ZERO;
		ptr_board->is_opened = FALSE;
		ptr_board++;
	}
	ptr_end_board->value_in_cube = ZERO;
	ptr_end_board->is_opened = FALSE;
}

void print_board(cube_in_board *ptr_board)
{
	cube_in_board *ptr_start = ptr_board;
	cube_in_board *ptr_board_last_address = ptr_board + (MAXSIZECOL+2) * (MAXSIZEROW+2);
	int max_col = MAXSIZECOL + 1;
	int current_col;
	while (ptr_start < ptr_board_last_address)
	{
		(ptr_start->is_opened == TRUE) ? printf("%3hd", ptr_start->value_in_cube) :
			printf(".");
		current_col = (ptr_start - ptr_board) % (max_col+1);
		(max_col == current_col) ? printf("\n") : ZERO;
		ptr_start++;
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
		number = number * 10 + **ptr_str - '0';
		*((*ptr_str)++);
	}
	(**ptr_str != '\0') ? *((*ptr_str)++) : ZERO;
	return number;
}

void set_mines_in_the_board(cube_in_board (*ptr_board)[MAXSIZECOL +2], short **ptr_array, short *size)
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
		*(*ptr_array+ (*size) -1) = x;

		temp = string_to_value(&ptr);
		y = temp;

		*ptr_array = (short*)realloc(*ptr_array, sizeof(short)*(++(*size)));
		*(*ptr_array + (*size) - 1) = y;

		ptr_board[x][y].value_in_cube = IS_MINE;
	}
}


void mine_around(cube_in_board board[][MAXSIZECOL+2], int row, int col)
{
	for (short counter = 0; counter <= 2; counter++)
	{
		(board[row][col + counter].value_in_cube != IS_MINE) ? board[row][col + counter].value_in_cube += 1 : ZERO;
	}
}

void find_mines_and_set_value(cube_in_board board[][MAXSIZECOL+2], short *ptr_array, short size)
{
	int counter = 0;
	int x;
	int y;
	short *ptr_end = ptr_array + size;
	while ( ptr_array != ptr_end )
	{
		x = *ptr_array;
		ptr_array++;
		y = *ptr_array;
		ptr_array++;
		for (short counter = -1; counter < 2 ; counter++)
		{
			mine_around(board , x + counter , y - 1);
		}
	}
}

void main(void)
{
	short *ptr_array = NULL;
	short size = 0;
	char c;
	cube_in_board board[MAXSIZEROW + 2][MAXSIZECOL + 2];
	cube_in_board *ptr_start = &board[0][0];
	init_board(ptr_start);
	cube_in_board *ptr_player_board = &board[1][1];
	set_mines_in_the_board(&board[0][0],&ptr_array,&size);
	print_board(ptr_start);
	printf("\n");
	find_mines_and_set_value(&board[0][0], ptr_array,size);
	free(ptr_array);
	print_board(ptr_start);
	printf("\n");
	short x = 1;
	short y = 1;
	while (x != 999)
	{
		printf("please enter the row:");
		scanf("%hd", &x);
		printf("please enter the row:");
		scanf("%hd", &y);

	}
	getche(&c);
}
