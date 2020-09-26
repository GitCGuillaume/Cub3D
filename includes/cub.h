#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"
# include "../minilibx-linux/mlx.h"

# define KEYPRESS 2

typedef struct		s_player
{
	int		pos_x;
	int		pos_y;
}		t_player;

typedef struct	s_map
{
	char	colour[2];
	unsigned short	north;
	unsigned short	east;
	unsigned short	west;
	unsigned short	south;
	unsigned short	sprite;
	char	*north_path;
	char	*east_path;
	char	*west_path;
	char	*south_path;
	char	*sprite_path;
	char	*full_line;
	char	**lines;
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_image;
	char	*mlx_get_data;
	t_player	player;


}		t_map;

/* MAIN */
int	close_program(void *param);
/* PLAYER */
int	initialization_player(t_player *player);
int	close_program_key(int keycode, void *param);
int	control_player(int keycode, void *param);
/* MAP */
int	initialization_map(t_map *map);
/* COLOUR */

/* PARSE MAP FILE */
char	*get_line_fd(int fd);
int	parse_line_fd(t_map *map);

#endif
