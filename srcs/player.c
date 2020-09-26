#include "../includes/cub.h"

int	initialization_player(t_player *player)
{
	player->pos_x = 5;
	player->pos_y = 5;
	return (0);
}
#include <stdio.h>

int	close_program_key(int keycode, void *param)
{
	int	i;
	t_map *map;

	i = 0;
	map = (t_map *)param;
	printf("keyc=%d", keycode);
	if (keycode == 65307)
	{
		printf("keyc=%d", keycode);
		free(map->full_line);	
		if (map->mlx_window)
			mlx_destroy_window(map->mlx_ptr, map->mlx_window);
		free(map->mlx_ptr);
		//if (map->mlx_image)
		//	mlx_destroy_image(map->mlx_ptr, map->mlx_image);
		/*if (map->lines)
		{
			while (map->lines[i] != 0)
			{
				free(map->lines[i]);
				i++;
			}
			free(map->lines);
		}
		*/
		exit(0);
		return (0);
	}
	return (0);
}

int	control_player(int keycode, void *param)
{
	t_map *command;
	command = (t_map *)param;
	if (keycode == 'w')
		command->player.pos_y -= 1;
	else if (keycode == 115)
		command->player.pos_y += 1;
	else if (keycode == 97)
		command->player.pos_x -= 1;
	else if (keycode == 100)
		command->player.pos_x += 1;
	else if (keycode == 65307)
		close_program_key(keycode, param);
	printf("key=%d", keycode);
	printf("\npos_x=%d", command->player.pos_x);
	printf("\npos_y=%d", command->player.pos_y);
	return (0);
}
