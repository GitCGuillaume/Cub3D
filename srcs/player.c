#include "../includes/cub.h"

int	initialization_player(t_player *player)
{
	player->pos_x = 5;
	player->pos_y = 5;
	return (0);
}

int	close_program_key(int keycode, void *param, char *message, int msg_number)
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
		clear_array(map);
		clear_array_two(map);
		free(map->north_path);
		free(map->east_path);
		free(map->west_path);
		free(map->south_path);
		free(map->sprite_path);
		if (message != NULL)
		{
			ft_putstr_fd(message, msg_number);
		}
		exit(0);
		return (0);
	}
	return (0);
}
#include <stdio.h>
int	search_player(t_map *map, char **lines, int i)
{
	int j;

	j = 0;
	if (lines)
	{
		while (lines[i])
		{
			j = 0;
			while (lines[i][j] != '\0')
			{
				if (lines[i][j] == 'N' || lines[i][j] == 'S'
					|| lines[i][j] == 'E' || lines[i][j] == 'W')
				{
					map->player_exist++;
					map->player.pos_y = i;
					map->player.pos_x = j;
					printf("x=%d", map->player.pos_x);
					printf(" y=%d", map->player.pos_y);
				}
				j++;
			}
			i++;
		}
	}
	if (map->player_exist != 1)
		close_program(map, "No player in the map.\n", 2);
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
		close_program_key(keycode, param, "Closed OK.\n", 1);
	return (0);
}
