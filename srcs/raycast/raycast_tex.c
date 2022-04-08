#include "cub.h"

int	text_map_u(t_map *map, t_image *img)
{
	double	pos_u;
	int		u;

	u = 0;
	pos_u = 0.000000;
	if (map->player.ray_horizontal.distance_wall
			< map->player.ray_vertical.distance_wall)
	{
		pos_u = map->player.ray_horizontal.pos_y
			+ (map->player.ray_horizontal.length_case_x
					/ map->player.ray_horizontal.distance_y);
	}
	else
	{
		pos_u = map->player.ray_vertical.pos_x
			+ (map->player.ray_vertical.length_case_y
					/ map->player.ray_vertical.distance_x);
	}
	pos_u -= floor(pos_u);
	pos_u = pos_u * (double)img->width;
	u = (int)floor(pos_u);
	return (u);
}

/*
	>> 1 == / 2
*/

int	text_map_v(t_map *map, int height, double zoom)
{
	double	pos_v;
	int		v;

	if (height >= 2147483647
			|| map->player.bottom_wall >= 2147483647 || height < 0)
		close_program(map,
				"Size window exceed the limit handled by the engine\n.", 2);
	pos_v = (height - (map->res_y >> 1) + (map->player.slice_height >> 1)) * zoom;
	v = (int)floor(pos_v);
	return (v);
}

/*
	>> 3 == / 8
*/

void	texture_mapping(t_map *map, int x, t_image *img)
{
	double	zoom;
	int		height;
	int		pixel;
	int		v;
	int		u;

	height = map->player.height_wall;
	pixel = 0;
	v = 0;
	zoom = (double)img->height / (double)map->player.slice_height;
	u = text_map_u(map, img);
	//if (height > map->player.bottom_wall)
	//	close_program(map, "An error occured while rendering.\n", 2);
	if (map->res_y > height)
	{
		while (map->player.bottom_wall > height)
		{
			v = text_map_v(map, height, zoom);
			pixel = (height * map->image[0].line_bytes) + (x * (map->image[0].bpp >> 3));
			if (img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 0])
				map->image[0].mlx_get_data[pixel + 0] =
					img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 0];
			if (img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 1])
				map->image[0].mlx_get_data[pixel + 1] =
					img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 1];
			if (img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 2])
				map->image[0].mlx_get_data[pixel + 2] =
					img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 2];
			if (img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 3])
				map->image[0].mlx_get_data[pixel + 3] =
					img->mlx_get_data[((v * img->line_bytes) + u * (map->image[0].bpp >> 3)) + 3];
			height++;
		}
	}
}

/*
	>> 3 == / 8
*/

void	ceil_mapping(t_map *map, int x, int ceil_colour)
{
	int	y_pix;
	int	pixel;

	y_pix = map->player.height_wall;
	//if (y_pix < 0)
	//	close_program(map, "An error occured while rendering in ceil mapping.\n", 2);
	pixel = 0;
	//printf("y_pix_ceil=%d pos_x=%f pos_y=%f\n", y_pix, map->player.pos_x, map->player.pos_y);
	if (y_pix < map->res_y)
	{
		while (y_pix >= 0)
		{
			pixel = (y_pix * map->image[0].line_bytes) + (x * (map->image[0].bpp >> 3));
			if (map->image[0].mlx_get_data[pixel + 0] == 0)
				map->image[0].mlx_get_data[pixel + 0] = (ceil_colour) & 0xFF;
			if (map->image[0].mlx_get_data[pixel + 1] == 0)
				map->image[0].mlx_get_data[pixel + 1] = (ceil_colour >> 8) & 0xFF;
			if (map->image[0].mlx_get_data[pixel + 2] == 0)
				map->image[0].mlx_get_data[pixel + 2] = (ceil_colour >> 16) & 0xFF;
			if (map->image[0].mlx_get_data[pixel + 3] == 0)
				map->image[0].mlx_get_data[pixel + 3] = (ceil_colour >> 24) & 0xFF;
			y_pix--;
		}
	}
}

/*
	>> 3 == / 8
*/

void	floor_mapping(t_map *map, int x, int floor_colour)
{
	int	i;
	int	pixel;

	i = map->player.bottom_wall;
	pixel = 0;
	//if (i > map->res_y)
	//	close_program(map, "An error occured while rendering in floor mapping.\n", 2);
	if (map->res_y != map->player.bottom_wall && map->player.height_wall < map->res_y)
	{
		while (map->res_y > i)
		{
			pixel = (i * map->image[0].line_bytes) + (x * (map->image[0].bpp >> 3));
			map->image[0].mlx_get_data[pixel + 0] = (floor_colour) & 0xFF;
			map->image[0].mlx_get_data[pixel + 1] = (floor_colour >> 8) & 0xFF;
			map->image[0].mlx_get_data[pixel + 2] = (floor_colour >> 16) & 0xFF;
			map->image[0].mlx_get_data[pixel + 3] = (floor_colour >> 24) & 0xFF;
			i++;
		}
	}
}
