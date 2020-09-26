#include "../includes/cub.h"

int	close_program(void *param)
{
	int	i;
	t_map *map;

	i = 0;
	map = (t_map *)param;
	free(map->full_line);	
	if (map->mlx_window)
		mlx_destroy_window(map->mlx_ptr, map->mlx_window);
	if (map->mlx_ptr)
		free(map->mlx_ptr);
	//if (map->mlx_image)
	//	mlx_destroy_image(map->mlx_ptr, map->mlx_image);
	/*if (map->lines)
	{
		while (map->lines[i] != 0)
		{
			free(map->lines[i]);
			i++;
		}
		free(map->lines);
	}
	*/
	exit(0);
	return (0);
}

int		ft_open_fd(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Can't open file.", 2);
		return (-1);
	}
	return (fd);
}

int		ft_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr_fd("Can't close file.", 2);
	}
	return (fd);
}

#include <stdio.h>
int	main(int argc, char *argv[])
{
	t_map	map;
	int	fd;
	int	i;
(void)argc;
	fd = ft_open_fd(argv[1]);
	i = 0;
	//printf("fd=%d", fd);
	if (fd != -1)
	{
		map.full_line = get_line_fd(fd);
		//parse_line_fd(&map);
		//map.lines = ft_split(string_map, '|');
		//if (map.lines)
			initialization_map(&map);
		//if (map.lines)
	//	{
	/*		while (map.lines[i] != 0)
			{
				free(map.lines[i]);
				i++;
			}
			free(map.lines);
		}*/
		free(map.full_line);
	}
	return (0);
}
