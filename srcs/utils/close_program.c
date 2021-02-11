#include "../../includes/cub.h"

int	close_program_gnl(t_map *map, char *message, int msg_number)
{
	int	i;

	i = 0;
	if (map->full_line)
		free(map->full_line);
	clear_array(map);
	clear_array_two(map);
	if (map->north_path)
		free(map->north_path);
	if (map->east_path)
		free(map->east_path);
	if (map->west_path)
		free(map->west_path);
	if (map->south_path)
		free(map->south_path);
	if (map->sprite_path)
		free(map->sprite_path);
	map->fd = ft_close_fd(map->fd);
	if (message != NULL)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(message, msg_number);
	}
	exit(1);
	return (0);
}

int	close_program_ok(t_map *map, char *message, int msg_number)
{
	int	i;

	i = 0;
	if (map->full_line)
		free(map->full_line);
	if (map->z_buffer)
		free(map->z_buffer);
	clear_array(map);
	clear_array_two(map);
	clear_image(map);
	clear_path(map);
	map->fd = ft_close_fd(map->fd);
	if (message != NULL)
		ft_putstr_fd(message, msg_number);
	exit(0);
	return (0);
}

int	close_program_cross(t_map *map, char *message, int msg_number)
{
	int	i;

	i = 0;
	if (map->full_line)
		free(map->full_line);
	if (map->z_buffer)
		free(map->z_buffer);
	clear_image(map);
	clear_array(map);
	clear_array_two(map);
	clear_path(map);
	map->fd = ft_close_fd(map->fd);
	if (message != NULL)
	{
		ft_putstr_fd(message, msg_number);
	}
	ft_putstr_fd("Closed OK\n", 1);
	exit(0);
	return (0);
}

int	close_program(t_map *map, char *message, int msg_number)
{
	int	i;

	i = 0;
	if (map->full_line)
		free(map->full_line);
	if (map->z_buffer)
		free(map->z_buffer);
	clear_array(map);
	clear_array_two(map);
	clear_image(map);
	clear_path(map);
	map->fd = ft_close_fd(map->fd);
	if (message != NULL)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(message, msg_number);
	}
	exit(1);
	return (0);
}
