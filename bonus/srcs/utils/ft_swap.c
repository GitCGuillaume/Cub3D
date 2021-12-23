#include "../../includes/cub.h"

void	ft_swap(t_sprite *a, t_sprite *b)
{
	t_sprite c;

	c = *a;
	*a = *b;
	*b = c;
}
