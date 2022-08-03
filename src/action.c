#include "tetris.h"

static void move_mino(t_game_info *game_info);
static void fix_mino(t_game_info *game_info);

void apply_key_action(t_game_info *game_info, int c)
{
	game_info->next_mino = duplicate_mino(game_info->current_mino);

	if (c == 'a') // move left
		game_info->next_mino.pos.col--;
	else if (c == 's') // move down
		game_info->next_mino.pos.row++;
	else if (c == 'd') // move right
		game_info->next_mino.pos.col++;
	else if (c == 'w') // rotate
		rotate_mino(game_info->next_mino);

	// confirm position change
	if (can_deploy_mino(game_info->table, game_info->next_mino))
		move_mino(game_info);
	else if (c == 's')
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
