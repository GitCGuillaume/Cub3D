#include "../../includes/cub.h"

int	init_sprite(t_map *map, int nb_sprite, int i, int j)
{
	map->sprite[nb_sprite].y =
		((i + 1) * (map->res_x / 5)) + (map->res_x / 5) / 2;
	map->sprite[nb_sprite].x =
		((j + 1) * (map->res_x / 5)) + (map->res_x / 5) / 2;
	map->sprite[nb_sprite].degree = 0;
	map->sprite[nb_sprite].x_sprite = 0;
	map->sprite[nb_sprite].size = 0;
	map->sprite[nb_sprite].distance = 0;
	nb_sprite++;
	return (nb_sprite);
}

int	find_sprite(t_map *map)
{
	long int		i;
	long int		j;
	unsigned int	nb_sprite;

	i = 0;
	nb_sprite = 0;
	while (map->lines[i])
	{
		j = 0;
		while (map->lines[i][j])
		{
			if (map->lines[i][j] == '2' && map->nb_sprite > nb_sprite)
			{
				nb_sprite = init_sprite(map, nb_sprite, i, j);
			}
			j++;
		}
		i++;
	}
	return (nb_sprite);
}

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

	size = (int)floor(map->sprite[nb_sprite].size);
	width_left = (map->res_x / 2)
		+ (int)floor(map->sprite[nb_sprite].x_sprite) - (size / 2);
	if (width_left < 0)
		width_left = 0;
	while (width > width_left)
	{
		map->sprite[nb_sprite].u = ((width_left - (map->res_x / 2)
					- (int)floor(map->sprite[nb_sprite].x_sprite)
					+ (size / 2)) + size) * map->image[5].width / size;
		while_height(map, bottom, nb_sprite, width_left);
		width_left++;
	}
}

void	sprite_mapping(t_map *map, unsigned int nb_sprite, int square_size)
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

void	distance_math(t_map *map, unsigned int nb_sprite, int square_size)
{
	while (nb_sprite > 0)
	{
		nb_sprite--;
		map->sprite[nb_sprite].distance =
			sqrt(pow((double)map->sprite[nb_sprite].y
					- (square_size * (map->player.pos_y + 1.0)), 2)
				+ pow((double)map->sprite[nb_sprite].x
					- (square_size * (map->player.pos_x + 1.0)), 2));
	}
}

void	quicksort_sprite(t_map *map, t_sprite *sprite,
		unsigned int nb_sprite, int square_size)
{
	unsigned int	i;
	unsigned int	j;
	double			k;

	i = 0;
	j = 0;
	distance_math(map, nb_sprite, square_size);
	nb_sprite = map->nb_sprite;
	while (nb_sprite > i)
	{
		j = 0;
		while (nb_sprite - i - 1 > j)
		{
			if (sprite[j].distance > sprite[j + 1].distance)
			{
				ft_swap(&sprite[j], &sprite[j + 1]);
			}
			j++;
		}
		i++;
	}
}

/** We need to quicksort the sprite from distance, sprites will be displayed from the nearest to the farthest **/

void	display_sprite(t_map *map, int square)
{
	unsigned int	nb_spt;

	nb_spt = map->nb_sprite;
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
		map->sprite[nb_spt].size = ((map->res_x / 2) / tan(0.523599))
			/ (cos(map->sprite[nb_spt].degree)
					* (map->sprite[nb_spt].distance));
		map->sprite[nb_spt].x_sprite = tan(map->sprite[nb_spt].degree)
			* ((map->res_x / 2) / tan(0.523599));
		map->sprite[nb_spt].x_sprite = -map->sprite[nb_spt].x_sprite;
		sprite_mapping(map, nb_spt, square);
	}
}
