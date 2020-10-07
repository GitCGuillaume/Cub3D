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
	if (keycode == 65307)
	{
		free(map->full_line);	
		if (map->mlx_window)
			mlx_destroy_window(map->mlx_ptr, map->mlx_window);
		free(map->mlx_ptr);
		if (map->lines)
		{
			while (map->lines[i] != 0)
			{
				free(map->lines[i]);
				i++;
			}
			free(map->lines);
		}
		i = 0;
		if (map->check_lines)
		{
			while (map->check_lines[i] != 0)
			{
				free(map->check_lines[i]);
				i++;
			}
			free(map->check_lines);
		}
		i = 0;
		if (map->colour != NULL)
		{
			while (i < 6)
			{
				free(map->colour[i]);
				i++;
			}
			free(map->colour);
		}
		i = 0;
		if (map->resolution)
		{
			while (i < 2)
			{
				free(map->resolution[i]);
				i++;
			}
			free(map->resolution);
		}
		free(map->north_path);
		free(map->east_path);
		free(map->west_path);
		free(map->south_path);
		free(map->sprite_path);
		exit(0);
		return (0);
	}
	return (0);
}

int	search_player(t_map *map, int i)
{
	int j;

	j = 0;
	if (map->lines)
	{
		while (map->lines[i])
		{
			j = 0;
			while (map->lines[i][j] != '\0')
			{
				if (map->lines[i][j] == 'N' || map->lines[i][j] == 'S'
					|| map->lines[i][j] == 'E' || map->lines[i][j] == 'W')
				{
					map->player_exist++;
					map->player.pos_y = i;
					map->player.pos_x = j;
				}
				j++;
			}
			i++;
		}
	}
	if (map->player_exist != 1)
		return (0);
	return (1);
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
	return (0);
}
