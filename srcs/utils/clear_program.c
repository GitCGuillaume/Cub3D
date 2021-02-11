#include "../../includes/cub.h"

void	clear_array(t_map *map)
{
	int	i;

	i = 0;
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
	if (map->lines_copy)
	{
		while (map->lines_copy[i] != 0)
		{
			free(map->lines_copy[i]);
			i++;
		}
		free(map->lines_copy);
	}
}

void	clear_array_two(t_map *map)
{
	int	i;

	i = 0;
	if (map->resolution)
	{
		while (2 > i)
		{
			if (map->resolution[i] != NULL)
				free(map->resolution[i]);
			i++;
		}
		free(map->resolution);
	}
	i = 0;
	if (map->colour)
	{
		while (i < 6)
		{
			if (map->colour[i] != NULL)
				free(map->colour[i]);
			i++;
		}
		free(map->colour);
	}
}

void	clear_image(t_map *map)
{
	if (map->mlx_window)
		mlx_destroy_window(map->mlx_ptr, map->mlx_window);
	if (map->image[0].mlx_get_data)
		mlx_destroy_image(map->mlx_ptr, map->image[0].mlx_image);
	if (map->image[1].mlx_get_data)
		mlx_destroy_image(map->mlx_ptr, map->image[1].mlx_image);
	if (map->image[2].mlx_get_data)
		mlx_destroy_image(map->mlx_ptr, map->image[2].mlx_image);
	if (map->image[3].mlx_get_data)
		mlx_destroy_image(map->mlx_ptr, map->image[3].mlx_image);
	if (map->image[4].mlx_get_data)
		mlx_destroy_image(map->mlx_ptr, map->image[4].mlx_image);
	if (map->image[5].mlx_get_data)
		mlx_destroy_image(map->mlx_ptr, map->image[5].mlx_image);
	if (map->mlx_ptr)
		free(map->mlx_ptr);
}

void	clear_path(t_map *map)
{
	if (map->north_path)
		free(map->north_path);
	if (map->east_path)
		free(map->east_path);
	if (map->west_path)
		free(map->west_path);
	if (map->south_path)
		free(map->south_path);
	if (map->sprite_path)
		free(map->sprite_path);
	if (map->sprite)
		free(map->sprite);
}
