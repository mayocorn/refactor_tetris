#include "tetris.h"

void apply_key_action(t_game_info *game_info, int c)
{
	game_info->next_mino = duplicate_mino(game_info->current_mino);

	if (c == 'a') // move left
		game_info->next_mino.pos.col--;
	else if (c == 's') // move down
		game_info->next_mino.pos.row++;
	else if (c == 'd')  // move right
		game_info->next_mino.pos.col++;
	else if (c == 'w')  // rotate
		rotate_mino(game_info->next_mino);

	if (can_deploy_mino(game_info))	// confirm position change
	{
		delete_mino(game_info->current_mino);
		game_info->current_mino = game_info->next_mino;
	}
	else if (c == 's')
	{
		set_mino_at_table(game_info->current_mino, game_info->table);
		erase_line_if_needed(game_info);
		create_new_mino(game_info);
	}

	printw_table(game_info);
}