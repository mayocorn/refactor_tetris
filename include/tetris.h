#ifndef TETRIS_H
# define TETRIS_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>
# include <stdbool.h>

# define ROW 20
# define COLUMN 15

typedef struct
{
	int row;
	int col;
} t_mino_position; // coordinate of the top left of mino

typedef struct
{
	bool **array;
	int width;
	t_mino_position pos;
} t_mino;

const t_mino shapes[7] =
{
	// . # #
	// # # .
	// . . .
	{
		(bool *[]){(bool[]){0, 1, 1}, (bool[]){1, 1, 0}, (bool[]){0, 0, 0}}, // array
		3 // width
	},

	// # # .
	// . # #
	// . . .
	{
		(bool *[]){(bool[]){1, 1, 0}, (bool[]){0, 1, 1}, (bool[]){0, 0, 0}},
		3
	},

	// . # .
	// # # #
	// . . .
	{
		(bool *[]){(bool[]){0, 1, 0}, (bool[]){1, 1, 1}, (bool[]){0, 0, 0}},
		3
	},

	// . . #
	// # # #
	// . . .
	{
		(bool *[]){(bool[]){0, 0, 1}, (bool[]){1, 1, 1}, (bool[]){0, 0, 0}},
		3
	},

	// # . .
	// # # #
	// . . .
	{
		(bool *[]){(bool[]){1, 0, 0}, (bool[]){1, 1, 1}, (bool[]){0, 0, 0}},
		3
	},

	// # #
	// # #
	{
		(bool *[]){(bool[]){1, 1}, (bool[]){1, 1}},
		2
	},

	// . . . .
	// # # # #
	// . . . .
	// . . . .
	{
		(bool *[]){(bool[]){0, 0, 0, 0}, (bool[]){1, 1, 1, 1}, 
					(bool[]){0, 0, 0, 0}, (bool[]){0, 0, 0, 0}},
		4
	}
};

typedef struct
{
	bool table[ROW][COLUMN];
	unsigned int score;
	bool gameon;
	t_mino current_mino;
	t_mino next_mino;
	struct timeval begin_time;
	struct timeval current_time;
	suseconds_t timelimit; // time limit per turn
	int decrease; // decrease time when the line is erased
} t_game_info;

// mino.c
void create_new_mino(t_game_info *game_info);
void delete_mino(t_mino mino);
t_mino duplicate_mino(t_mino mino);
void rotate_mino(t_mino mino);

// action.c
void apply_key_action(t_game_info *game_info, int c);

// table.c
void set_mino_at_table(t_mino mino, bool table[ROW][COLUMN]);
void erase_line_if_needed(t_game_info *game_info);
void printw_table(t_game_info *game_info);
void print_result(t_game_info *game_info);

// judge.c
bool can_deploy_mino(t_game_info *game_info);
bool is_passed_turn_time(t_game_info *game_info);

#endif