#include "tetris.h"

static bool is_out_of_table(int row, int col);

bool can_deploy_mino(t_game_info *game_info)
{
	t_mino mino = game_info->next_mino;

	for (int i = 0; i < mino.width; i++)
	{
		for (int j = 0; j < mino.width; j++)
		{
			if (mino.array[i][j] == false)
				continue;

			// position in table
			int row = mino.pos.row + i;
			int col = mino.pos.col + j;

			if (is_out_of_table(row, col) || game_info->table[row][col])
				return false;
		}
	}
	return true;
}

bool is_passed_turn_time(t_game_info *game_info)
{
	gettimeofday(&(game_info->current_time), NULL);

	suseconds_t current = game_info->current_time.tv_sec * 1000000 + game_info->current_time.tv_usec;
	suseconds_t begin = game_info->begin_time.tv_sec * 1000000 + game_info->begin_time.tv_usec;

	return (current - begin > game_info->timelimit);
}

static bool is_out_of_table(int row, int col)
{
	return (row < 0 || row >= ROW || col < 0 || col >= COLUMN);
}
