/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:21:08 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/12 14:42:54 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_map_four(t_map *map)
{
	int	textures_exist;

	textures_exist = 0;
	textures_exist = register_texture(map);
	if (textures_exist == 0)
		close_program(map, "Can't create textures image.\n", 2);
	if (!(start_ray_direction(map)))
		close_program(map, "Can't find direction's player.\n", 2);
	map->player.degree += 30.000000;
}

int	init_map_three(t_map *map)
{
	int	i;

	i = 0;
	map->colour = malloc(sizeof(unsigned char *) * 6);
	if (map->colour == NULL)
		return (0);
	while (6 > i)
	{
		map->colour[i] = NULL;
		i++;
	}
	i = 0;
	return (1);
}

void	init_map_two(t_map *map)
{
	int	i;

	i = 0;
	map->mlx_ptr = NULL;
	map->mlx_window = NULL;
	while (6 > i)
	{
		map->image[i].mlx_get_data = NULL;
		map->image[i].mlx_image = NULL;
		i++;
	}
	map->colour = NULL;
	map->is_north = 0;
	map->is_east = 0;
	map->is_west = 0;
	map->is_south = 0;
	map->ceiling_colour = -1;
	map->floor_colour = -1;
}

int	initialization_map_struct(t_map *map)
{
	int	init;

	init_map_two(map);
	map->colour_counter = 0;
	map->north_path = NULL;
	map->east_path = NULL;
	map->west_path = NULL;
	map->south_path = NULL;
	map->full_line = NULL;
	map->lines = NULL;
	map->lines_copy = NULL;
	map->player_exist = 0;
	map->res_x = 320;
	map->res_y = 200;
	init = init_map_three(map);
	if (init == 0)
		return (0);
	return (1);
}

void	get_screen_size(t_map *map)
{
	if ((mlx_get_screen_size(map->mlx_ptr, &map->x_tmp, &map->y_tmp)))
		close_program(map, "Can't get computer screen size.\n", 2);
	map->res_x = map->x_tmp;
	map->res_y = map->y_tmp;
}
