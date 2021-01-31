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
	i = 0;
	while (6 > i)
	{
		map->image[i].mlx_get_data = NULL;
		i++;
	}
	return (1);
}

int	initialization_map_struct(t_map *map)
{
	int	init;
	//t_image lst;

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
	map->nb_sprite = 0;
	map->sprite = 0;
	return (1);
}

void	put_pixel(t_map *map, int x, unsigned int line_bytes, int colour)
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
			//map->image[0].mlx_get_data[pixel + 3] = (colour >> 24) & 0xFF;
		//}
		y_pix++;
	}
}
void	black_pixel(t_map *map, int x, unsigned int line_bytes, int colour)
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
			//map->image[0].mlx_get_data[pixel + 3] = (colour >> 24) & 0xFF;
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
	control_player((void *)map);
	if (map->image[0].mlx_image)
		mlx_destroy_image(map->mlx_ptr, map->image[0].mlx_image);
	if (!(map->image[0].mlx_image = mlx_new_image(map->mlx_ptr, map->res_x, map->res_y)))
		return (-1);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	raycast(map);
	mlx_put_image_to_window(map->mlx_ptr,
			map->mlx_window, map->image->mlx_image, 0, 0);	
	//ft_swap(map->image[0].mlx_image, map->image[1].mlx_image);
	//ft_swap(map->image[0].mlx_get_data, map->image[1].mlx_get_data);
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
	if (!(map->mlx_window = mlx_new_window(map->mlx_ptr, map->res_x, map->res_y, "Cub3D")))
		return (-1);	
	if (!(map[0].image->mlx_image = mlx_new_image(map->mlx_ptr, map->res_x, map->res_y)))
		return (-1);
	map->image[0].mlx_get_data = mlx_get_data_addr(map->image[0].mlx_image,
			&map->image[0].bpp, &map->image[0].line_bytes, &endian);
	if (map->image[0].mlx_get_data == NULL)
		close_program(map, "image creation failed.\n", 2);
	map->sprite = malloc(sizeof(t_sprite) * map->nb_sprite);
	if (map->sprite == NULL)
		close_program(map, "Sprite memory allocation failed.\n", 2);
	if (map->nb_sprite > 0)
		find_sprite(map);
	textures_exist = register_texture(map);
	if (textures_exist == 0)
	{
		close_program(map, "Can't create textures image.\n", 2);
		return (-1);
	}
	if (!(start_ray_direction(map)))
		return (-1);
	map->player.degree += 30.0;
	mlx_hook(map->mlx_window, KEYPRESS, KEYPRESS_MASK, control_press, (void *)map);
	mlx_hook(map->mlx_window, KEYRELEASE, KEYRELEASE_MASK, control_release, (void *)map);
	//mlx_hook(map->mlx_window, KEYPRESS, KEYPRESS_MASK, control_player, (void *)map);
	mlx_loop_hook(map->mlx_ptr, &render_map, (void *)map);
	mlx_hook(map->mlx_window, 33, 1L << 17, close_program_cross, (void *)map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
