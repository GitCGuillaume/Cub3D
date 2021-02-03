#include "../includes/cub.h"
#include <stdio.h>

int		ft_open_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror("Can't open file");
		return (-1);
	}
	return (fd);
}

int		ft_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror("Can't close file");
		return (-1);
	}
	return (fd);
}

int	save_check(t_map *map, char *save)
{
	if (save[0] == '-' && save[1] == '-' && save[2] == 's'
			&& save[3] == 'a' && save[4] == 'v' && save[5] == 'e'
			&& save[6] == '\0')
	{
		map->save = 1;
		return (1);
	}
	else
	{
		ft_putstr_fd("Error\n--save command is wrong.\n", 2);
		exit(0);
	}
	return (0);
}

void	display_game(t_map *map, int argc, char *argv, char *result)
{
	if (ft_strncmp(result, ".cub", 4) == 0)
		map->fd = ft_open_fd(argv);
	else
		ft_putstr_fd("Error\nWrong name format.\n", 2);
	if (map->fd != -1)
	{
		init_player(map);
		if (!(initialization_map_struct(map)))
			ft_putstr_fd("Error\nMap struct allocation failed.\n", 2);
		else
		{
			map->full_line = get_line_fd(map, map->fd);
			if (map->full_line)
			{
				parse_line_fd(map);
				initialization_map(map, argv, argc);
			}
		}
	}
	if (map->fd != -1)
		ft_close_fd(map->fd);
}

int	main(int argc, char *argv[])
{
	char	*result;
	char	*save;
	t_map	map;

	map.save = 0;
	map.fd = -1;
	save = NULL;
	if (argc == 2 || argc == 3)
	{
		result = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
		if (argc == 3)
		{
			save = argv[2];
			save_check(&map, save);
		}
		if (result != NULL)
			display_game(&map, argc, argv[1], result);
		else
			ft_putstr_fd("Error\nWrong name format.\n", 2);
	}
	else
		ft_putstr_fd("Error\nPlease enter a file path.\n", 2);
	return (0);
}
