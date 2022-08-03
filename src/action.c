#include "tetris.h"

static void move_mino(t_game_info *game_info);
static void fix_mino(t_game_info *game_info);

void apply_key_action(t_game_info *game_info, int key)
{
	game_info->next_mino = duplicate_mino(game_info->current_mino);

	if (key == 'a') // move left
		game_info->next_mino.pos.col--;
	else if (key == 's') // move down
		game_info->next_mino.pos.row++;
	else if (key == 'd') // move right
		game_info->next_mino.pos.col++;
	else if (key == 'w') // rotate
		rotate_mino(game_info->next_mino);

	// confirm position change
	if (can_deploy_mino(game_info->table, game_info->next_mino))
		move_mino(game_info);
	else if (key == 's')
		fix_mino(game_info);
	else
		delete_mino(game_info->next_mino);

	printw_table(game_info);
}

static void move_mino(t_game_info *game_info)
{
	delete_mino(game_info->current_mino);
	game_info->current_mino = game_info->next_mino;
}

static void fix_mino(t_game_info *game_info)
{
	delete_mino(game_info->next_mino);
	set_mino_at_table(game_info->current_mino, game_info->table);
	erase_line_if_needed(game_info);
	create_new_mino(game_info);
}
