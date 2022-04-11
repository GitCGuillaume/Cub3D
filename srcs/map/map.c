/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:20:19 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/11 13:32:09 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	render_map(void *param)
{
	int			endian;
	t_map		*map;

	endian = 0;
	map = (t_map *)param;
	control_player((void *)map);
	if (map->image[0].mlx_image)
		mlx_destroy_image(map->mlx_ptr, map->image[0].mlx_image);
	map->image[0].mlx_image
		= mlx_new_image(map->mlx_ptr, map->res_x, map->res_y);
	if (map->image[0].mlx_image == NULL)
		close_program(map, "Can't create image display.\n", 2);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	if (map->image[0].mlx_get_data == NULL)
		close_program(map, "Can't get image datas.\n", 2);
	raycast(map);
	mlx_put_image_to_window(map->mlx_ptr,
		map->mlx_window, map->image->mlx_image, 0, 0);
	return (0);
}

/*
	Keypress_mask : 1L << 0
	Keypress_release : 1L << 1
	StructureNotifyMask : 1L << 17
*/

int	initialization_map(t_map *map)
{
	int	endian;

	endian = 0;
	if (!map)
		close_program(map, "No structure detected.\n", 2);
	map->mlx_ptr = mlx_init();
	if (map->mlx_ptr == NULL)
		close_program(map, "initialization mlx failed.\n", 2);
	get_screen_size(map);
	map->image[0].mlx_image = NULL;
	map->image[0].mlx_get_data = NULL;
	init_map_four(map);
	map->mlx_window
		= mlx_new_window(map->mlx_ptr, map->res_x, map->res_y, "Cub3D");
	if (map->mlx_window == NULL)
		close_program(map, "Can't create game window.\n", 2);
	mlx_hook(map->mlx_window,
		KEYPRESS, 1L << 0, control_press, (void *)map);
	mlx_hook(map->mlx_window,
		KEYRELEASE, 1L << 1, control_release, (void *)map);
	mlx_loop_hook(map->mlx_ptr, &render_map, (void *)map);
	mlx_hook(map->mlx_window, 33,
		1L << 17, close_program_cross, (void *)map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
