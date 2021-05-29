/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:24:42 by gchopin           #+#    #+#             */
/*   Updated: 2021/05/29 13:40:50 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int		ft_close_fd(int fd, t_map *map)
{
	int	quit;

	quit = -1;
	if (fd != -1)
		quit = close(fd);
	if (quit == -1 && map != NULL)
		close_program(map, "Can't close file\n", 2);
	if (quit == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror("Can't close file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int		save_check(t_map *map, char *save)
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

void	display_game(t_map *map, int argc, char *argv)
{
	map->fd = ft_open_fd(argv);
	if (map->fd != -1)
	{
		init_player(map);
		if (!(initialization_map_struct(map)))
			close_program(map, "Map struct allocation failed.\n", 2);
		else
		{
			get_line_fd(map, map->fd);
			if (map->full_line == NULL)
				close_program(map, "The engine can't retrieve map parameters.", 2);
			if (map->full_line && map->fd != -1)
			{
				parse_line_fd(map);
				initialization_map(map, argv, argc);
			}
		}
	}
}

int		main(int argc, char *argv[])
{
	char	*result;
	char	*save;
	t_map	map;

	map.save = 0;
	map.fd = -1;
	save = NULL;
	if ((argc == 2 || argc == 3))
	{
		result = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
		if (result == NULL)
			close_program(0, "Wrong name format.\n", 2);
		if (ft_strcmp(result, ".cub") != 0)
			close_program(0, "Wrong name format.\n", 2);
		if (argc == 3)
		{
			save = argv[2];
			save_check(&map, save);
		}
		if (result != NULL)
			display_game(&map, argc, argv[1]);
		close_program(0, "Something went wrong.", 2);
	}
	else
		close_program(0, "Please enter a file path.", 2);
	return (0);
}
