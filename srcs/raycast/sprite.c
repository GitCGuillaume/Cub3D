#include "../../includes/cub.h"

void	print_sprite(t_map *map, int pixel, int nb_sprite, int height)
{
	int	v;
	int	u;
	int	size;
	int	line_bytes;

	u = map->sprite[nb_sprite].u;
	size = (int)floor(map->sprite[nb_sprite].size);
	v = ((height - (map->res_y + size) / 2)
			+ size) * map->image[5].height / size;
	line_bytes = map->image[5].line_bytes;
	if (map->image[5].mlx_get_data[((v * line_bytes) + (u * 4)) + 0])
		map->image[0].mlx_get_data[pixel + 0] =
			map->image[5].mlx_get_data[((v * line_bytes) + (u * 4)) + 0];
	if (map->image[5].mlx_get_data[((v * line_bytes) + (u * 4)) + 1])
		map->image[0].mlx_get_data[pixel + 1] =
			map->image[5].mlx_get_data[((v * line_bytes) + (u * 4)) + 1];
	if (map->image[5].mlx_get_data[((v * line_bytes) + (u * 4)) + 2])
		map->image[0].mlx_get_data[pixel + 2] =
			map->image[5].mlx_get_data[((v * line_bytes) + (u * 4)) + 2];
}

void	while_height(t_map *map, int bottom, int nb_sprite, int width_left)
{
	int	height;
	int	size;

	size = (int)floor(map->sprite[nb_sprite].size);
	height = (map->res_y / 2) - (size / 2);
	if (height < 0)
		height = 0;
	while (bottom > height && map->sprite[nb_sprite].distance
			* (map->res_x / 5) < *(map->z_buffer + width_left))
	{
		print_sprite(map,
				(height * map->image[0].line_bytes)
				+ (width_left * 4), nb_sprite, height);
		height++;
	}
}

void	while_width(t_map *map, int nb_sprite, int width, int bottom)
{
	int	size;
	int	width_left;
	int	x_sprite;

	x_sprite = (int)floor(map->sprite[nb_sprite].x_sprite);
	size = (int)floor(map->sprite[nb_sprite].size);
	width_left = (map->res_x / 2)
		+ x_sprite - (size / 2);
	if (width_left < 0)
		width_left = 0;
	while (width > width_left)
	{
		map->sprite[nb_sprite].u = ((width_left - (map->res_x / 2)
					- x_sprite
					+ (size / 2)) + size) * map->image[5].width / size;
		while_height(map, bottom, nb_sprite, width_left);
		width_left++;
	}
}

void	sprite_mapping(t_map *map, unsigned int nb_sprite)
{
	int	bottom;
	int	width;
	int	size;

	size = (int)floor(map->sprite[nb_sprite].size);
	width = (map->res_x / 2) + (int)floor(map->sprite[nb_sprite].x_sprite)
		- (size / 2) + size;
	bottom = ((map->res_y - size) / 2) + size;
	if (bottom > map->res_y)
		bottom = map->res_y;
	if (width > map->res_x)
		width = map->res_x;
	while_width(map, nb_sprite, width, bottom);
}

/** We need to quicksort the sprite from distance, sprites will be displayed from the nearest to the farthest **/

void	display_sprite(t_map *map, int square, unsigned int nb_spt)
{
	quicksort_sprite(map, map->sprite, nb_spt, square);
	while (nb_spt > 0)
	{
		nb_spt--;
		map->sprite[nb_spt].distance = map->sprite[nb_spt].distance / square;
		map->sprite[nb_spt].degree = atan2(map->sprite[nb_spt].y
				- (square * (map->player.pos_y + 1.0)),
				map->sprite[nb_spt].x - (square * (map->player.pos_x + 1.0)));
		map->sprite[nb_spt].degree = (-map->sprite[nb_spt].degree)
			- degree_to_radian(map->player.degree_raycast);
		map->sprite[nb_spt].degree =
			correct_distance(radian_to_degree(map->sprite[nb_spt].degree));
		map->sprite[nb_spt].degree =
			degree_to_radian(map->sprite[nb_spt].degree);
		degree_check_divide(map, nb_spt);
		map->sprite[nb_spt].size = ((map->res_x / 2) / tan(0.523599))
			/ (cos(map->sprite[nb_spt].degree)
					* (map->sprite[nb_spt].distance));
		map->sprite[nb_spt].x_sprite = tan(map->sprite[nb_spt].degree)
			* ((map->res_x / 2) / tan(0.523599));
		map->sprite[nb_spt].x_sprite = -map->sprite[nb_spt].x_sprite;
		sprite_values_check(map, nb_spt);
		sprite_mapping(map, nb_spt);
	}
}
