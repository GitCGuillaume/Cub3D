/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:20:19 by gchopin           #+#    #+#             */
/*   Updated: 2021/02/04 17:31:33 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	render_map(void *param)
{
	int			endian;
	t_map	 * 	map;

	endian = 0;
	map = (t_map *)param;
	control_player((void *)map);
	if (map->image[0].mlx_image)
		mlx_destroy_image(map->mlx_ptr, map->image[0].mlx_image);
	map->image[0].mlx_image =
		mlx_new_image(map->mlx_ptr, map->res_x, map->res_y);
	if (map->image[0].mlx_image == NULL)
		close_program(map, "Can't create image display.\n", 2);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	map->z_buffer = malloc(sizeof(double) * ((double)map->res_x));
	if (map->z_buffer == NULL)
		close_program(map, "Z_buffer allocation failed.\n", 2);
	raycast(map);
	mlx_put_image_to_window(map->mlx_ptr,
			map->mlx_window, map->image->mlx_image, 0, 0);
	return (0);
}

void	take_screenshot(t_map *map, char *argv)
{
	int	endian;

	endian = 0;
	if (map->image[0].mlx_image)
		mlx_destroy_image(map->mlx_ptr, map->image[0].mlx_image);
	map->image[0].mlx_image =
		mlx_new_image(map->mlx_ptr, map->res_x, map->res_y);
	if (map->image[0].mlx_image == NULL)
		close_program(map, "Screenshot failed, can't create the picture.\n", 2);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	raycast(map);
	if (map->save == 1)
		create_bmp(map, argv);
}

int	initialization_map(t_map *map, char *argv, int argc)
{
	int	endian;

	endian = 0;
	map->mlx_ptr = mlx_init();
	if (map->mlx_ptr == NULL)
		close_program(map, "initialization mlx failed.\n", 2);
	get_screen_size(map);
	map->image[0].mlx_image = NULL;
	map->image[0].mlx_get_data = NULL;
	init_map_four(map);
	if (map->save == 1 && argc == 3)
		take_screenshot(map, argv);
	map->mlx_window =
		mlx_new_window(map->mlx_ptr, map->res_x, map->res_y, "Cub3D");
	if (map->mlx_window == NULL)
		close_program(map, "Can't create game window.\n", 2);
	mlx_hook(map->mlx_window,
			KEYPRESS, KEYPRESS_MASK, control_press, (void *)map);
	mlx_hook(map->mlx_window,
			KEYRELEASE, KEYRELEASE_MASK, control_release, (void *)map);
	mlx_loop_hook(map->mlx_ptr, &render_map, (void *)map);
	mlx_hook(map->mlx_window, 33, 1L << 17, close_program_cross, (void *)map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
