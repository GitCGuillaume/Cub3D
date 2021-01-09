#include "../includes/cub.h"

int	init_map_struct_two(t_map *map)
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
	return (1);
}

int	initialization_map_struct(t_map *map)
{
	int	init;

	init = init_map_struct_two(map);
	if (init == 0)
		return (0);
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
	map->lines_copy = NULL;
	map->player_exist = 0;
	map->image[0].mlx_image = 0;
	map->image[1].mlx_image = 0;
	map->player.offset_tex = 0.0;
	return (1);
}

void	put_pixel(t_map *map, int x, unsigned int line_bytes, int bpp, int colour)
{
	int	pixel;
	int	y_pix;

	//printf("height_walll=%d\n", map->player.height_wall);
//printf("bottom_walll=%d\n", map->player.bottom_wall);
	y_pix = map->player.height_wall;
	while (map->player.bottom_wall > y_pix)
	{
		//while (x > x_pix)
		//{
			pixel = (y_pix * line_bytes) + (x * 4);
			map->image[0].mlx_get_data[pixel + 0] = (colour) & 0xFF;
			map->image[0].mlx_get_data[pixel + 1] = (colour >> 8) & 0xFF;
			map->image[0].mlx_get_data[pixel + 2] = (colour >> 16) & 0xFF;
			map->image[0].mlx_get_data[pixel + 3] = (colour >> 24) & 0xFF;
		//}
		y_pix++;
	}
}
void	black_pixel(t_map *map, int x, unsigned int line_bytes, int bpp, int colour)
{
	int	pixel;
	int	y_pix;
	int z = 0;
	//printf("height_walll=%d\n", map->player.height_wall);
//printf("bottom_walll=%d\n", map->player.bottom_wall);
	y_pix = 0;
	while (x > z)
	{
		y_pix = 0;
		while (map->res_y > y_pix)
		{
			pixel = (y_pix * line_bytes) + (z * 4);
			map->image[0].mlx_get_data[pixel + 0] = (colour) & 0xFF;
			map->image[0].mlx_get_data[pixel + 1] = (colour >> 8) & 0xFF;
			map->image[0].mlx_get_data[pixel + 2] = (colour >> 16) & 0xFF;
			map->image[0].mlx_get_data[pixel + 3] = (colour >> 24) & 0xFF;
			y_pix++;
		}
		z++;
	}
}

#include <stdio.h>
int	render_map(void *param)
{
	t_map	*map;

	int	line_bytes;
	int	bpp;
	int	endian;

	line_bytes = 125;
	bpp = 32;
	endian = 0;
	map = (t_map *)param;
	//put_pixel(map->mlx_get_data, map->player.pos_x,
	//		map->player.pos_y, line_bytes, bpp, manage_bit_colour_ceiling(map));
	//camera_wall(map);
	//exit(0);
	/*if (map->image[0].mlx_image)
		mlx_destroy_image(map->mlx_ptr, map->image[0].mlx_image);
	if (!(map->image[0].mlx_image = mlx_new_image(map->mlx_ptr, map->res_x, map->res_y)))
		return (-1);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	*/
	raycast(map);
	mlx_put_image_to_window(map->mlx_ptr,
			map->mlx_window, map->image[0].mlx_image, 0, 0);	
	ft_swap(map->image[0].mlx_image, map->image[1].mlx_image);
	ft_swap(map->image[0].mlx_get_data, map->image[1].mlx_get_data);
	return (0);
}

int	initialization_map(t_map *map)
{
	int	x;
	int	y;
int	endian = 0;
	int	textures_exist;

	x = ft_atoi(map->resolution[0]);
	y = ft_atoi(map->resolution[1]);
	textures_exist = 0;
	if (!(map->mlx_ptr = mlx_init()))
		return (-1);
	if (!(mlx_get_screen_size(map->mlx_ptr, &map->x_tmp, &map->y_tmp)))
		return (-1);
	if ((x <= 50 || x > map->x_tmp) || (y <= 50 || y > map->y_tmp))
	{
		map->res_x = map->x_tmp;
		map->res_y = map->y_tmp;
	}
	else
	{
		map->res_x = x;
		map->res_y = y;
	}
	//camera_wall(map);
	printf("north_path=%s\n", map->north_path);
	if (!(map->mlx_window = mlx_new_window(map->mlx_ptr, map->res_x, map->res_y, "Cub3D")))
		return (-1);	
	if (!(map->image[0].mlx_image = mlx_new_image(map->mlx_ptr, map->res_x, map->res_y)))
		return (-1);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	textures_exist = register_texture(map);
	if (textures_exist == 0)
	{
		close_program(map, "Can't create textures image.\n", 2);
		return (-1);
	}
	//if (!(map->image[1].mlx_image = mlx_new_image(map->mlx_ptr, map->res_x, map->res_y)))
	//	return (-1);
	//map->image[1].mlx_get_data = mlx_get_data_addr(map->image[1].mlx_image,
	//		&map->image[1].bpp, &map->image[1].line_bytes, &endian);	
	//put_pixel(map->image[0].mlx_get_data, 500, map->player.height_wall, map->image[0].line_bytes, map->image[0].bpp, manage_bit_colour_ceiling(map));

	/*if (!(map->image[0].mlx_image = mlx_xpm_file_to_image(map->mlx_ptr, map->north_path, &map->image[0].height, &map->image[0].width)))
		return (-1);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	if (!(map->image[4].mlx_image = mlx_new_image(map->mlx_ptr, map->res_x, map->res_y)))
		return (-1);
	map->image[4].mlx_get_data = mlx_get_data_addr(map->image[4].mlx_image,
			&map->image[4].bpp, &map->image[4].line_bytes, &endian);
	//int pixel = (y_pix * line_bytes) + (x_pix * 4);
	printf("sixtyfour=%d\n", map->image[0].width);
	printf("sixtyfour=%d\n", map->image[0].height);
	int i, j;
	i = 0;
	j = 0;
while (20 > j)
{
	i = 0;
	while (20 > i)
	{
	map->image[4].mlx_get_data[((j) * map->image[4].line_bytes) + (i * 4) + 0]
		= map->image[0].mlx_get_data[((1 * map->image[0].line_bytes) + (1 * 4)) + 0];
	map->image[4].mlx_get_data[((j) * map->image[4].line_bytes) + (i * 4) + 1]
		= map->image[0].mlx_get_data[((1 * map->image[0].line_bytes) + (1 * 4)) + 1];
	map->image[4].mlx_get_data[((j) * map->image[4].line_bytes) + (i * 4) + 2]
		= map->image[0].mlx_get_data[((1 * map->image[0].line_bytes) + (1 * 4)) + 2];
	map->image[4].mlx_get_data[((j) * map->image[4].line_bytes) + (i * 4) + 3]
		= map->image[0].mlx_get_data[((1 * map->image[0].line_bytes) + (1 * 4)) + 3];
		i++;
	}
	j++;
}*/
	//printf("line_bytes=%d\n", map->image[0].line_bytes);
	//printf("bpp=%d\n", map->image[0].bpp);
	if (!(start_ray_direction(map)))
		exit(0);
	map->player.degree += 30.0;
	mlx_hook(map->mlx_window, KEYPRESS, 1L << 0, control_player, (void *)map);
	//if (map->image[0].mlx_image)
	//	mlx_destroy_image(map->mlx_ptr, map->image[0].mlx_image);
	mlx_loop_hook(map->mlx_ptr, &render_map, (void *)map);
	mlx_hook(map->mlx_window, 33, 1L << 17, close_program, (void *)map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
