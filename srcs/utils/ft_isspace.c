#include "../../includes/cub.h"

/*int	is_tab(char c)
{
	if (c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	is_other(char c)
{
	if (c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}*/

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
