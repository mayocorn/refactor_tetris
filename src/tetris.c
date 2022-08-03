#include "tetris.h"

static void init_game(t_game_info *game_info);
static void init_game_info(t_game_info *game_info);
static void play_game(t_game_info *game_info);
static void terminate_game(t_game_info *game_info);

int main()
{
	t_game_info game_info;

	init_game(&game_info);
	play_game(&game_info);
	terminate_game(&game_info);
	return 0;
}

static void init_game(t_game_info *game_info)
{
	srand(time(NULL));
	initscr();
	timeout(1);
	init_game_info(game_info);
	create_new_mino(game_info);
	print_table(game_info);
}

static void init_game_info(t_game_info *game_info)
{
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COLUMN; j++)
			game_info->table[i][j] = 0;
	}
	game_info->score = 0;
	game_info->gameon = true;
	game_info->current_mino.array = NULL;
	game_info->current_mino.width = 0;
	gettimeofday(&(game_info->begin_time), NULL);
	game_info->timelimit = 400000;
	game_info->decrease = 1000;
}

static void play_game(t_game_info *game_info)
{
	while (game_info->gameon)
	{
		int c = getch();
		if (c != ERR)
			apply_key_action(game_info, c);
		if (is_passed_turn_time(game_info))
		{
			apply_key_action(game_info, 's');
			gettimeofday(&(game_info->begin_time), NULL);
		}
	}
}

static void terminate_game(t_game_info *game_info)
{
	delete_mino(game_info->current_mino);
	endwin();
	print_result(game_info);
}
