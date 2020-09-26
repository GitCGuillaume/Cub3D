#include "../includes/cub.h"

char	*get_line_fd(int fd)
{
	char	*line;
	char	*tmp_line;
	char	*join_str;
	int	ret;
	
	line = NULL;
	tmp_line = NULL;
	join_str = NULL;
	if (!(line = malloc(sizeof(char))))
		return (NULL);
	line[0] = '\0';
	while ((ret = get_next_line(fd, &tmp_line)) > 0)
	{
		join_str = ft_strjoin(line, tmp_line);
		free(line);
		line = join_str;
		free(tmp_line);
		tmp_line = ft_strjoin(line, "|");
		free(line);
		line = tmp_line;
	}
	free(tmp_line);
	return (line);
}
#include <stdio.h>
int	parse_line_fd(t_map *map)
{
	printf("map->full_line=%s", map->full_line);
	return (0);
}
