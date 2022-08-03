#include "tetris.h"

#define SHAPE_TYPES 7
const t_mino shapes[SHAPE_TYPES] =
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

void create_new_mino(t_game_info *game_info)
{
	t_mino *mino = &(game_info->current_mino);

	delete_mino(*mino);
	*mino = duplicate_mino(shapes[rand() % SHAPE_TYPES]);
	mino->pos.col = rand() % (COLUMN - mino->width + 1);
	mino->pos.row = 0;
	if (!can_deploy_mino(game_info->table, game_info->current_mino))
		game_info->gameon = false;
}

void delete_mino(t_mino mino)
{
	for (int i = 0; i < mino.width; i++)
		free(mino.array[i]);
	free(mino.array);
}

t_mino duplicate_mino(t_mino mino)
{
	t_mino new_mino = mino;

	new_mino.array = (bool **)malloc(mino.width * sizeof(char *));
	if (new_mino.array == NULL)
		exit(EXIT_FAILURE);

	for (int i = 0; i < mino.width; i++)
	{
		new_mino.array[i] = (bool *)malloc(mino.width * sizeof(char));
		if (new_mino.array[i] == NULL)
			exit(EXIT_FAILURE);

		for (int j = 0; j < mino.width; j++)
			new_mino.array[i][j] = mino.array[i][j];
	}

	return new_mino;
}

void rotate_mino(t_mino mino)
{
	t_mino tmp = duplicate_mino(mino);

	for (int i = 0; i < mino.width; i++)
	{
		for (int j = 0; j < mino.width; j++)
			mino.array[i][j] = tmp.array[mino.width - j - 1][i];
	}

	delete_mino(tmp);
}
