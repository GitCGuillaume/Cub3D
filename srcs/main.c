#include "../includes/cub.h"
#include <stdio.h>

int		ft_open_fd(char *path)
{
	int fd;

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
			else
				ft_putstr_fd("Error\nWrong name format.\n", 2);
			if (fd != -1)
			{
				if (!(initialization_map_struct(&map)))
					ft_putstr_fd("Error\n, Map struct allocation failed.\n", 2);
				else
				{
					map.full_line = get_line_fd(&map, fd);
					if (map.full_line)
					{
						parse_line_fd(&map);
						initialization_map(&map);
					}
				}
			}
			if (fd != -1)
				ft_close_fd(fd);
		}
		else
			ft_putstr_fd("Error\nWrong name format.\n", 2);
	}
	else
		ft_putstr_fd("Error\nPlease enter a file.\n", 2);
	return (0);
}
