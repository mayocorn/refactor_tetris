#include "tetris.h"

void create_new_mino(t_game_info *game_info)
{
	t_mino *mino = &(game_info->current_mino);
	delete_mino(*mino);
	*mino = duplicate_mino(shapes[rand() % 7]);
	mino->pos.col = rand() % (COLUMN - mino->width + 1);
	mino->pos.row = 0;
	if (!can_deploy_mino(mino))
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

	new_mino.array = (char **)malloc(mino.width * sizeof(char *));
	if (new_mino.array == NULL)
		exit(EXIT_FAILURE);

	for (int i = 0; i < mino.width; i++)
	{
		new_mino.array[i] = (char *)malloc(mino.width * sizeof(char));
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
