#include "cub_bonus.h"

int	is_line_wrong(const char *line)
{
	unsigned int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] != 0 && line[i] != ' ' && line[i] != '1'
				&& line[i] != '0' && line[i] != '2'
				&& line[i] != 'N' && line[i] != 'S'
				&& line[i] != 'E' && line[i] != 'W')
			{
				return (0);
			}
			i++;
		}
	}
	return (1);
}
