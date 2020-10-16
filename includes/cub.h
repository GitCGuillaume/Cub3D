#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "get_next_line.h"
# include "libft.h"
# include "../minilibx-linux/mlx.h"

# define KEYPRESS 2

typedef struct		s_player
{
	char		start_position;
	int		pos_x;
	int		pos_y;
}		t_player;

typedef struct	s_map
{
	unsigned short	is_north;
	unsigned short	is_east;
	unsigned short	is_west;
	unsigned short	is_south;
	unsigned short	is_sprite;
	unsigned short	is_resolution;
	int		colour_counter;
	int		player_exist;
	char		**colour;
	char		**resolution;
	char		*north_path;
	char		*east_path;
	char		*west_path;
	char		*south_path;
	char		*sprite_path;
	char		*full_line;
	char		**lines;
	char		*mlx_get_data;
	void		*mlx_ptr;
	void		*mlx_window;
	void		*mlx_image;
	t_player	player;

}		t_map;

/* MAIN */
/* PLAYER */
int	initialization_player(t_player *player);
int	close_program_key(int keycode, void *param, char *message, int msg_number);
int	search_player(t_map *map, char **lines, int i);
int	control_player(int keycode, void *param);
/* MAP */
int	initialization_map(t_map *map);
int	initialization_map_struct(t_map *map);
/* COLOUR */
/* PARSE MAP FILE */
char	*get_line_fd(t_map *map, int fd);
int	parse_line_fd(t_map *map);
int	is_line_correct(int i, char *line, t_map *map);
char	*get_number(t_map *map, unsigned int *i, char *line);
char	*get_number_two(t_map *map, unsigned int *i, char *line);
char	*get_texture(t_map *map, unsigned int i, char *line);
void	find_texture(char *line, unsigned int old_i, t_map *map);
void	find_texture_two(char *line, unsigned int *i, unsigned int old_i, t_map *map);
/* CHECK VALIDITY MAP */
int	check_indicator_full(t_map *map);
int	check_first_character(t_map *map);
int		check_validity_map(t_map *map);
int		check_valid_character(t_map *map);
/* UTILS */
int	is_other(char c);
int	is_tab(char c);
int		is_space(char c);
/* CLOSE */
int	close_program(t_map *map, char *message, int msg_number);
int	close_program_ok(t_map *map, char *message, int msg_number);
int	close_program_gnl(t_map *map, char *message, int msg_number);
void	clear_array(t_map *map);
void	clear_array_two(t_map *map);

#endif
