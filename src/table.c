#include "tetris.h"

static void erase_line(t_game_info *game_info, int row);
static void printw_composite_table(bool table1[ROW][COLUMN], bool table2[ROW][COLUMN]);

void set_mino_at_table(t_mino mino, bool table[ROW][COLUMN])
{
	for (int i = 0; i < mino.width; i++)
	{
		for (int j = 0; j < mino.width; j++)
		{
			if (mino.array[i][j])
				table[mino.pos.row + i][mino.pos.col + j] = mino.array[i][j];
		}
	}
}

void erase_line_if_needed(t_game_info *game_info)
{
	for (int i = 0; i < ROW; i++)
	{
		int cnt = 0;

		for (int j = 0; j < COLUMN; j++)
			cnt += game_info->table[i][j];

		if (cnt == COLUMN)
			erase_line(game_info, i);
	}
}

static void erase_line(t_game_info *game_info, int row)
{
	game_info->score += 100;

	for (int i = row; i > 0; i--)
	{
		for (int j = 0; j < COLUMN; j++)
			game_info->table[i][j] = game_info->table[i - 1][j];
	}
	for (int i = 0; i < COLUMN; i++)
		game_info->table[0][i] = 0;

	game_info->timelimit -= game_info->decrease;
	game_info->decrease = (game_info->decrease <= 1) ? 1 : game_info->decrease - 1;
}

void printw_table(t_game_info *game_info)
{
	bool mino_table[ROW][COLUMN] = {0};
	set_mino_at_table(game_info->current_mino, mino_table);

	clear();
	for (int i = 0; i < COLUMN - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	printw_composite_table(game_info->table, mino_table);
	printw("\nScore: %d\n", game_info->score);
}

void print_result(t_game_info *game_info)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			printf("%c ", game_info->table[i][j] ? '#' : '.');
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", game_info->score);
}

static void printw_composite_table(bool table1[ROW][COLUMN], bool table2[ROW][COLUMN])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			printw("%c ", (table1[i][j] + table2[i][j]) ? '#' : '.');
		printw("\n");
	}
}
