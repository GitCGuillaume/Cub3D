#include "../../includes/cub.h"

int	register_texture(t_map *map)
{
	int	endian;

	endian = 0;
	map->image[1].mlx_image = mlx_xpm_file_to_image(map->mlx_ptr, map->north_path,
			&map->image[1].width, &map->image[1].height);
	if (map->image[1].mlx_image == NULL)
		return (0);
	map->image[1].mlx_get_data = mlx_get_data_addr(map->image[1].mlx_image, &map->image[1].bpp, &map->image[1].line_bytes, &endian);
	if (map->image[1].mlx_get_data == NULL)
		return (0);
	map->image[2].mlx_image = mlx_xpm_file_to_image(map->mlx_ptr, map->west_path,
			&map->image[2].width, &map->image[2].height);
	if (map->image[2].mlx_image == NULL)
		return (0);
	map->image[2].mlx_get_data = mlx_get_data_addr(map->image[2].mlx_image, &map->image[2].bpp, &map->image[2].line_bytes, &endian);
	if (map->image[2].mlx_get_data == NULL)
		return (0);
	map->image[3].mlx_image = mlx_xpm_file_to_image(map->mlx_ptr, map->east_path,
			&map->image[3].width, &map->image[3].height);
	if (map->image[3].mlx_image == NULL)
		return (0);
	map->image[3].mlx_get_data = mlx_get_data_addr(map->image[3].mlx_image, &map->image[3].bpp, &map->image[3].line_bytes, &endian);
	if (map->image[3].mlx_get_data == NULL)
		return (0);
	map->image[4].mlx_image = mlx_xpm_file_to_image(map->mlx_ptr, map->south_path,
			&map->image[4].width, &map->image[4].height);
	if (map->image[4].mlx_image == NULL)
		return (0);
	map->image[4].mlx_get_data = mlx_get_data_addr(map->image[4].mlx_image, &map->image[4].bpp, &map->image[4].line_bytes, &endian);
	if (map->image[4].mlx_get_data == NULL)
		return (0);
	map->image[5].mlx_image = mlx_xpm_file_to_image(map->mlx_ptr, map->sprite_path,
			&map->image[5].width, &map->image[5].height);
	if (map->image[5].mlx_image == NULL)
		return (0);
	map->image[5].mlx_get_data = mlx_get_data_addr(map->image[5].mlx_image, &map->image[5].bpp, &map->image[5].line_bytes, &endian);
	if (map->image[5].mlx_get_data == NULL)
		return (0);
	return (1);
}
