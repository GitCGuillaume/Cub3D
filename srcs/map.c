#include "../includes/cub.h"

#include <stdio.h>

int	initialization_map_struct(t_map *map)
{
	int	i;

	i = 0;
	if (!(map->colour = malloc(sizeof(unsigned char *) * 6)))
		return (0);
	while (6 > i)
	{
		map->colour[i] = NULL;
		i++;
	}
	if (!(map->resolution = malloc(sizeof(char *) * 2)))
	{
		free(map->colour);
		return (0);
	}
	i = 0;
	while (2 > i)
	{
		map->resolution[i] = NULL;
		i++;
	}
	map->ceiling_colour = -1;
	map->floor_colour = -1;
	map->is_north = 0;
	map->is_east = 0;
	map->is_west = 0;
	map->is_south = 0;
	map->is_sprite = 0;
	map->is_resolution = 0;
	map->colour_counter = 0;
	map->north_path = NULL;
	map->east_path = NULL;
	map->west_path = NULL;
	map->south_path = NULL;
	map->sprite_path = NULL;
	map->full_line = NULL;
	map->lines = NULL;
	map->player_exist = 0;
	return (1);
}

void	put_pixel(char *addr, int x, int y, unsigned int line_bytes, int bpp, int colour)
{
	int	pixel;
	int	x_pix;
	int	y_pix;

	x_pix = 0;
	y_pix = 0;
	while (320 > y_pix)
	{
		x_pix = 0;
		while (640 > x_pix)
		{
			pixel = (y_pix * line_bytes) + (x_pix * 4);
			addr[pixel + 0] = (colour) & 0xFF;
			addr[pixel + 1] = (colour >> 8) & 0xFF;
			addr[pixel + 2] = (colour >> 16) & 0xFF;
			addr[pixel + 3] = (colour >> 24) & 0xFF;
			x_pix++;
		}
		y_pix++;
	}
}

int	render_map(void *param)
{
	t_map *map;

	int line_bytes = 60;
	int bpp = 32;
	int endian = 0;

	map = (t_map *)param;
	if (!(map->mlx_image = mlx_new_image(map->mlx_ptr, map->x, map->y)))
		return (-1);
	map->mlx_get_data = mlx_get_data_addr(map->mlx_image, &bpp, &line_bytes, &endian);
	put_pixel(map->mlx_get_data, map->player.pos_x, map->player.pos_y, line_bytes, bpp, manage_bit_colour_ceiling(map));
	mlx_put_image_to_window(map->mlx_ptr, map->mlx_window, map->mlx_image, 0, 0);
	mlx_destroy_image(map->mlx_ptr, map->mlx_image);
	return (0);
}

int	initialization_map(t_map *map)
{
	int	x;
	int	y;

	x = ft_atoi(map->resolution[0]);
	y = ft_atoi(map->resolution[1]);
	if (!(map->mlx_ptr = mlx_init()))
		return (-1);
	if (!(mlx_get_screen_size(map->mlx_ptr, &map->x_tmp, &map->y_tmp)))
		return (-1);
	if ((x <= 50 || x > map->x_tmp) || (y <= 50 || y > map->y_tmp))
	{
		map->x = map->x_tmp;
		map->y = map->y_tmp;
	}
	else
	{
		map->x = x;
		map->y = y;
	}
	printf("x = %d y = %d", map->x, map->y);
	if (!(map->mlx_window = mlx_new_window(map->mlx_ptr, map->x, map->y, "Cub3D")))
		return (-1);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	initialization_player(&map->player);
	mlx_hook(map->mlx_window, 33, 1L << 17, close_program, (void *)map);
	mlx_loop_hook(map->mlx_ptr, &render_map, (void *)map);
	mlx_hook(map->mlx_window, KEYPRESS, 1L << 0, control_player, (void *)map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
