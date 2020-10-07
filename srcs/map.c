#include "../includes/cub.h"

#include <stdio.h>

int	initialization_map_struct(t_map *map)
{
	if (!(map->colour = malloc(sizeof(char *) * 6)))
		return (0);
	if (!(map->resolution = malloc(sizeof(char *) * 2)))
	{
		free(map->colour);
		return (0);
	}
	/*map->colour[0] = NULL;
	map->colour[1] = NULL;
	map->colour[2] = NULL;
	map->colour[3] = NULL;
	map->colour[4] = NULL;
	map->colour[5] = NULL;
	map->resolution[0] = NULL;
	map->resolution[1] = NULL;
	*/
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

void	put_pixel(char *addr, int x, int y, int line_bytes, int bpp, int colour)
{
	while (x != 500)
	{
		y = 0;
		while (y != 500)
		{
			addr[(y * bpp) + x] = colour;
			y++;
		}
		x++;
	}
	/*x = x + 100;
	y = 5;
	while (y != 500)
	{
		addr[(y * bpp) + x] = colour;
		y++;
		//dst = addr + (y * sizetest + x * (bbp / 8));
	}*/

}

int	render_map(void *param)
{
	t_map *map;
	t_player	player;

	int line_bytes = 4;
	int bpp = 32;
	int endian = 0;

	map = (t_map *)param;
	if (!(map->mlx_image = mlx_new_image(map->mlx_ptr, 1400, 1400)))
		return (-1);
	map->mlx_get_data = mlx_get_data_addr(map->mlx_image, &line_bytes, &bpp, &endian);
	put_pixel(map->mlx_get_data, map->player.pos_x, map->player.pos_y, line_bytes, bpp, 0xABCDEF);
	mlx_put_image_to_window(map->mlx_ptr, map->mlx_window, map->mlx_image, 0, 0);
	mlx_destroy_image(map->mlx_ptr, map->mlx_image);
	//initialization_player(&player);
	return (0);
}

int	initialization_map(t_map *map)
{
	if (!(map->mlx_ptr = mlx_init()))
		return (-1);
	if (!(map->mlx_window = mlx_new_window(map->mlx_ptr, 1400, 1400, "Cub3D")))
		return (-1);
	initialization_player(&map->player);
	parse_line_fd(map);
	//printf("player.pos_x1=%d", player.pos_x);
	//mlx_key_hook(map->mlx_window, close_pro, (void *)map);
	mlx_hook(map->mlx_window, 33, 1L << 17, close_program, (void *)map);
	mlx_loop_hook(map->mlx_ptr, &render_map, (void *)map);
	mlx_hook(map->mlx_window, KEYPRESS, 1L << 0, control_player, (void *)map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
