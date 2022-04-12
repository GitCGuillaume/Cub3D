/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:48:15 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:48:16 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	close_program_gnl(t_map *map, char *message, int msg_number)
{
	int	i;

	i = 0;
	if (map == NULL)
	{
		map->fd = ft_close_fd(map->fd);
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(message, msg_number);
		exit(EXIT_FAILURE);
	}
	if (map->full_line)
		free(map->full_line);
	clear_array(map);
	clear_array_two(map);
	clear_path(map);
	map->fd = ft_close_fd(map->fd);
	if (message != NULL)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(message, msg_number);
	}
	exit(EXIT_FAILURE);
}

void	close_program_ok(t_map *map, char *message, int msg_number)
{
	int	i;

	i = 0;
	if (map == NULL)
	{
		map->fd = ft_close_fd(map->fd);
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(message, msg_number);
		exit(EXIT_FAILURE);
	}
	if (map->z_buffer)
		free(map->z_buffer);
	if (map->full_line)
		free(map->full_line);
	clear_array(map);
	clear_array_two(map);
	clear_image(map);
	clear_path(map);
	map->fd = ft_close_fd(map->fd);
	if (message != NULL)
		ft_putstr_fd(message, msg_number);
	exit(0);
}

int	close_program_cross(t_map *map)
{
	int	i;

	i = 0;
	if (map->full_line)
		free(map->full_line);
	clear_image(map);
	clear_array(map);
	clear_array_two(map);
	clear_path(map);
	map->fd = ft_close_fd(map->fd);
	ft_putstr_fd("Closed OK\n", 1);
	exit(0);
	return (0);
}

void	close_program(t_map *map, char *message, int msg_number)
{
	int	i;

	i = 0;
	if (map == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(message, msg_number);
		exit(EXIT_FAILURE);
	}
	if (map->full_line)
		free(map->full_line);
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
	exit(EXIT_FAILURE);
}
