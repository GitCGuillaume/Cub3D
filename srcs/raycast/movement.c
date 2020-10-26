#include "../../includes/cub.h"

int	move_camera_lr(int keycode, void *param)
{
	t_map *map;

	map = (t_map *)param;
	if (keycode == 65361)
		map->player.rotation_lr = map->player.rotation_lr - 0.01;
	else if (keycode == 65363)
		map->player.rotation_lr = map->player.rotation_lr + 0.01;
	return (0);
}
