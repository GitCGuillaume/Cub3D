#include "../../includes/cub.h"

int	ft_open_bmp(t_map *map, char *path)
{
	int	fd;
	char	*bmp_file;
	char	*substr;

	substr = ft_substr(path, 0, ft_strlen(path) - 4);
	bmp_file = ft_strjoin(substr, ".bmp");
	if (bmp_file == NULL)
		close_program(map, "Can't get name bmp.\n", 2);
	fd = open(bmp_file, O_RDWR | O_CREAT, 0777);
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
/*
 * filesize = taille header + resolution d ecran (nb pixel)
*/
void	create_bmp(t_map *map, char *argv)
{
	int		fd;
	unsigned int	filesize;

	fd = ft_open_bmp(map, argv);
	filesize = 54 + (map->res_x * map->res_y);
	if (fd != 1)
	{
		ft_putstr_fd("BM", fd);
		write(fd, &filesize, sizeof(filesize));
		ft_putchar_fd((unsigned)0, fd);
		ft_putchar_fd((unsigned)0, fd);
		ft_putchar_fd((unsigned)0, fd);
		ft_putchar_fd((unsigned)0, fd);
		filesize = 54;
		write(fd, &filesize, sizeof(filesize));
	}
	if (fd != -1)
	{
		ft_close_fd(fd);
		close_program_cross(map, "Screenshot taken successfully.\n", 1);
	}
}
