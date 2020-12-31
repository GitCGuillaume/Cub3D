#include "../../includes/cub.h"

void	ft_swap(void *a, void *b)
{
	void *c;

	c = (char *)a;
	a = (char *)b;
	b = (char *)c;
}
