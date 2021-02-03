/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:25:16 by gchopin           #+#    #+#             */
/*   Updated: 2021/02/03 17:26:35 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int		ft_open_bmp(t_map *map, char *path)
{
	int		fd;
	char	*bmp_file;
	char	*substr;

	substr = ft_substr(path, 0, ft_strlen(path) - 4);
	bmp_file = ft_strjoin(substr, ".bmp");
	if (bmp_file == NULL)
		close_program(map, "Can't get name bmp.\n", 2);
	fd = open(bmp_file, O_CREAT | O_RDWR, 0777);
	if (substr)
		free(substr);
	if (bmp_file)
		free(bmp_file);
	if (fd == -1)
	{
		close_program(map, "Can't open bmp file.\n", 2);
	}
	return (fd);
}

void	write_header(t_map *map, int fd)
{
	unsigned short		two_bytes;
	unsigned int		four_bytes;
	int					s_four_bytes;

	four_bytes = 54 + (map->res_x * map->res_y);
	s_four_bytes = 0;
	two_bytes = 0;
	ft_putstr_fd("BM", fd);
	write(fd, &four_bytes, sizeof(four_bytes));
	write(fd, &two_bytes, sizeof(unsigned short));
	write(fd, &two_bytes, sizeof(unsigned short));
	four_bytes = 54;
	write(fd, &four_bytes, sizeof(four_bytes));
}

void	write_header_img(t_map *map, int fd)
{
	unsigned short		two_bytes;
	unsigned int		four_bytes;
	int					s_four_bytes;

	four_bytes = 40;
	write(fd, &four_bytes, sizeof(unsigned int));
	write(fd, &map->res_x, sizeof(signed int));
	write(fd, &map->res_y, sizeof(signed int));
	two_bytes = 1;
	write(fd, &two_bytes, sizeof(unsigned short));
	two_bytes = (unsigned short)map->image[0].bpp;
	write(fd, &two_bytes, sizeof(unsigned short));
	four_bytes = 0;
	write(fd, &four_bytes, sizeof(unsigned int));
	write(fd, &four_bytes, sizeof(unsigned int));
	write(fd, &s_four_bytes, sizeof(signed int));
	write(fd, &s_four_bytes, sizeof(signed int));
	write(fd, &four_bytes, sizeof(unsigned int));
	write(fd, &four_bytes, sizeof(unsigned int));
}

void	write_img(t_map *map, int fd)
{
	int	x;
	int	y;
	int	pixel;

	x = 0;
	y = map->res_y;
	pixel = 0;
	while (y > 0)
	{
		x = 0;
		y--;
		while (map->res_x > x)
		{
			pixel = (y * map->image[0].line_bytes) + (x * 4);
			write(fd, &map->image[0].mlx_get_data[pixel], sizeof(int));
			x++;
		}
	}
}

/*
 ** Source : https://medium.com/sysf/
 ** bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
*/

void	create_bmp(t_map *map, char *argv)
{
	int	fd;

	fd = ft_open_bmp(map, argv);
	if (fd != 1)
	{
		if (map->image[0].mlx_get_data != NULL)
		{
			write_header(map, fd);
			write_header_img(map, fd);
			write_img(map, fd);
		}
		else
		{
			close_program(map, "Can't take screenshot\n", 2);
			ft_close_fd(fd);
		}
	}
	if (fd != -1)
	{
		ft_close_fd(fd);
		close_program_cross(map, "Screenshot taken successfully.\n", 1);
	}
}
