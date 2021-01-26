#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "get_next_line.h"
# include "libft.h"
# include "../minilibx-linux/mlx.h"

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESS_MASK 1L << 0
# define KEYRELEASE_MASK 1L << 1

typedef struct		s_ray
{
	double		inter_x;
	double		inter_y;
	double		length_case_x;
	double		length_case_y;
	double		distance_x;
	double		distance_y;
	double		distance_wall;
	int		pos_x;
	int		pos_y;
	int		is_wall;
}			t_ray;

typedef struct		s_player
{
	char		start_position;
	int		fill_x;
	int		fill_y;
	double		pos_x;
	double		pos_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		ray_dir;
	double		inter_x;
	double		inter_y;
	double		pi_x;
	double		pi_y;
	double		cross_x;
	double		cross_y;
	double		rotation_lr;
	double		side_ray_x;
	double		side_ray_y;
	double		length_case_x;
	double		length_case_y;
	double		perpendicular_distance;
	double		distance_wall;
	double		offset_tex;
	double		degree;
	double		degree_raycast;
	int		slice_height;
	int		step_x;
	int		step_y;
	int		side_ray;
	int		is_wall;
	int		height_wall;
	int		bottom_wall;
	t_ray		ray_horizontal;
	t_ray		ray_vertical;
}		t_player;

typedef struct		s_image
{
	void		*mlx_image;
	char		*mlx_get_data;
	int		width;
	int		height;
	int		line_bytes;
	int		bpp;

}		t_image;

typedef struct s_control
{
	int	forward;
	int	backward;
	int	ss_left;
	int	ss_right;
	int	t_left;
	int	t_right;
}		t_control;

typedef struct	s_sprite
{
	double	x_sprite;
	double	degree;
	double	distance;
	double	size;
	int	x;
	int	y;
}		t_sprite;

typedef struct	s_map
{
	unsigned short	is_north;
	unsigned short	is_east;
	unsigned short	is_west;
	unsigned short	is_south;
	unsigned short	is_sprite;
	unsigned short	is_resolution;
	unsigned int	nb_sprite;
	int		colour_counter;
	int		player_exist;
	int		ceiling_colour;
	int		floor_colour;
	char		**colour;
	char		**resolution;
	char		*north_path;
	char		*east_path;
	char		*west_path;
	char		*south_path;
	char		*sprite_path;
	char		*full_line;
	char		**lines;
	char		**lines_copy;
	char		*mlx_get_data;
	void		*mlx_ptr;
	void		*mlx_window;
	t_image		image[6];
	t_player	player;
	t_control	*control;
	t_sprite	*sprite;
	int	x_tmp;
	int	y_tmp;
	int	res_x;
	int	res_y;

}		t_map;

/* MAIN */
/* PLAYER */
void	init_player(t_map *map);
int	close_program_key(int keycode, void *param, char *message, int msg_number);
int	search_player(t_map *map, char **lines, int i);
int	control_press(int keycode, void *param);
int	control_release(int keycode, void *param);
int	control_player(void *param);
/* MAP */
void	put_pixel(t_map *map, int x, unsigned int line_bytes, int bpp, int colour);
int	initialization_map(t_map *map);
int	initialization_map_struct(t_map *map);
/* COLOUR */
unsigned int	manage_bit_colour_floor(t_map *map);
unsigned int	manage_bit_colour_ceil(t_map *map);
/* PARSE MAP FILE */
char	*get_line_fd(t_map *map, int fd);
int	parse_line_fd(t_map *map);
int	is_full_line_ok(char *line);
void	is_printable(t_map *map, char *line, unsigned int *i);
char	*get_number(t_map *map, unsigned int *i, char *line);
char	*get_number_two(t_map *map, unsigned int *i, char *line);
char	*get_texture(t_map *map, unsigned int i, char *line);
void	find_texture(char *line, unsigned int old_i, t_map *map);
void	find_texture_two(char *line, unsigned int *i, unsigned int old_i, t_map *map);
void	find_texture_three(char *line, unsigned int i, t_map *map);
/* CHECK VALIDITY MAP */
int	check_indicator_full(t_map *map);
unsigned int	check_first_character(t_map *map);
int		check_validity_map(t_map *map);
int		check_valid_character(t_map *map);
/* UTILS */
int	is_other(char c);
int	is_tab(char c);
int	is_space(char c);
void	ft_swap(void *a, void *b);
int	register_texture(t_map *map);
/* CLOSE */
int	close_program(t_map *map, char *message, int msg_number);
int	close_program_ok(t_map *map, char *message, int msg_number);
int	close_program_gnl(t_map *map, char *message, int msg_number);
void	clear_array(t_map *map);
void	clear_array_two(t_map *map);
/** RAYCASTER **/
void	raycast(t_map *map);
int	start_ray_direction(t_map *map);
//void	camera_wall(t_map *map);
/** RAYCASTER MOVEMENT **/
int	move_camera_lr(int keycode, void *param);
t_image			*ft_lstlast(t_image *lst);

/** SPRITE **/
int	find_sprite(t_map *map);

void	black_pixel(t_map *map, int x, unsigned int line_bytes, int bpp, int colour);
unsigned int	black_colour(t_map *map);
double	correct_distance(double value);
double	degree_to_radian(double degree);

#endif
