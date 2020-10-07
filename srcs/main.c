#include "../includes/cub.h"
#include <stdio.h>
int	close_program(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	free(map->full_line);	
	if (map->mlx_window)
		mlx_destroy_window(map->mlx_ptr, map->mlx_window);
	free(map->mlx_ptr);
	//if (map->mlx_image)
	//	mlx_destroy_image(map->mlx_ptr, map->mlx_image);
	if (map->lines)
	{
		while (map->lines[i] != 0)
		{
			free(map->lines[i]);
			i++;
		}
		free(map->lines);
	}
	i = 0;
	if (map->check_lines)
	{
		while (map->check_lines[i] != 0)
		{
			free(map->check_lines[i]);
			i++;
		}
		free(map->check_lines);
	}
	i = 0;
	if (map->colour)
	{
		while (i < 6)
		{
			free(map->colour[i]);
			i++;
		}
		free(map->colour);
	}
	i = 0;
	if (map->resolution)
	{
		while (i < 2)
		{
			free(map->resolution[i]);
			i++;
		}
		free(map->resolution);
	}
	free(map->north_path);
	free(map->east_path);
	free(map->west_path);
	free(map->south_path);
	free(map->sprite_path);
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
	int	i;
	int	fd;
	t_map	map;
	char	*result;

	i = 0;
	fd = -1;
	if (argc == 2)
	{
		result = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
		if (result != NULL)
		{
			if (ft_strncmp(result, ".cub", 4) == 0)
				fd = ft_open_fd(argv[1]);
			if (fd != -1)
			{
				if (!(initialization_map_struct(&map)))
					return (0);
				map.full_line = get_line_fd(fd);	
				initialization_map(&map);
			}
			if (fd != -1)
				ft_close_fd(fd);
		}
		else
			ft_putstr_fd("No map found.", 2);
	}
	return (0);
}
