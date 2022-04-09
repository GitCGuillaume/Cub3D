#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "get_next_line.h"
# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESS_MASK 1L << 0
# define KEYRELEASE_MASK 1L << 1
# define STRUCTURENOTIFYMASK 1L << 17
# define PI 3.1415

typedef struct		s_ray
{
	int		pos_x;
	int		pos_y;
	int		is_wall;
	double		length_case_x;
	double		length_case_y;
	double		distance_x;
	double		distance_y;
	double		distance_wall;
}			t_ray;

typedef struct		s_player
{
	char		start_position;
	int		fill_x;
	int		fill_y;
	int		slice_height;
	int		is_wall;
	int		height_wall;
	int		bottom_wall;
	double		pos_x;
	double		pos_y;
	double		distance_wall;
	double		degree;
	double		degree_raycast;
	t_ray		ray_horizontal;
	t_ray		ray_vertical;
}		t_player;

typedef struct		s_image
{
	int		height;
	int		line_bytes;
	int		width;
	int		bpp;
	char		*mlx_get_data;
	void		*mlx_image;
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

typedef struct  s_sprite
{
        int     x;
        int     y;
        int     u;
        double  x_sprite;
        double  degree;
        double  size;
        double  distance;
}               t_sprite;

typedef struct	s_map
{
	unsigned short	is_north;
	unsigned short	is_east;
	unsigned short	is_west;
	unsigned short	is_south;
	unsigned short	is_resolution;
	unsigned short	is_sprite;
	unsigned int	nb_sprite;
	int		fd;
	int		save;
	int		colour_counter;
	int		player_exist;
	int		ceiling_colour;
	int		floor_colour;
	int		x_tmp;
	int		y_tmp;
	int		res_x;
	int		res_y;
	void		*mlx_ptr;
	char		*north_path;
	char		*east_path;
	char		*west_path;
	char		*south_path;
	char		*full_line;
	char		*sprite_path;
	char		**colour;
	char		**resolution;
	char		**lines;
	void		*mlx_window;
	char		**lines_copy;
	double		*z_buffer;
	t_control	control;
	t_image		image[6];
	t_player	player;
	t_sprite	*sprite;
}		t_map;

/* MAIN */
int		ft_close_fd(int fd);

/* PLAYER */
void		init_player(t_map *map);
int			close_program_key(int keycode, void *param, char *message, int msg_number);
int			search_player(t_map *map, char **lines, int i);
int			control_press(int keycode, void *param);
int			control_release(int keycode, void *param);
int			control_player(void *param);

/* MAP */
int			initialization_map(t_map *map);
int			initialization_map_struct(t_map *map);

/* MAP SETTING */
int	initialization_map_struct(t_map *map);
void	init_map_two(t_map *map);
int	init_map_three(t_map *map);
void	init_map_four(t_map *map);
void	get_screen_size(t_map *map);

/* COLOUR */
unsigned int	manage_bit_colour_floor(t_map *map);
unsigned int	manage_bit_colour_ceil(t_map *map);

/* PARSE MAP FILE */
void	get_line_fd(t_map *map, int fd);
int	parse_line_fd(t_map *map);
short int	is_full_line_ok(char *line);
void	is_printable(t_map *map, char *line, unsigned int *i);
char	*get_number(unsigned int *i, char *line);
char	*get_number_two(t_map *map, unsigned int *i, char *line);
char	*get_texture(t_map *map, unsigned int i, char *line);
void	find_texture(char *line, unsigned int i, t_map *map);
int	find_resolution(char *line, unsigned int *i, t_map *map);
int	find_colour(char *line, unsigned int *i,
	unsigned int old_i, t_map *map);
void	find_texture_two(char *line, unsigned int i, t_map *map);

/* CHECK VALIDITY MAP */
int	check_indicator_full(t_map *map);
unsigned int	check_first_character(t_map *map);
int		check_validity_map(t_map *map);
int		check_valid_character(t_map *map);

/* UTILS */
int	is_space(char c);
int	register_texture(t_map *map);
void	free_array(char **ptr);

/* CLOSE */
int	close_program_cross(t_map *map);
void	close_program(t_map *map, char *message, int msg_number);
void	close_program_ok(t_map *map, char *message, int msg_number);
void	close_program_gnl(t_map *map, char *message, int msg_number);

/* CLEAR PROGRAM */
void	clear_array(t_map *map);
void	clear_array_two(t_map *map);
void	clear_image(t_map *map);
void	clear_path(t_map *map);

/** RAYCASTER **/
void	raycast(t_map *map);

/** RAYCASTER TOOLS TWO **/
size_t	max_lines(t_map *map);
double	correct_distance(double value);

/** RAYCASTER VER **/
void	instanciate_pos_ver(t_map *map, double square_size);
void	instanciate_length_ver(t_map *map, double tang, double square_size);
void	vertical_check(t_map *map, double *length_case_x,
		double *length_case_y, double square);
void	vertical_detection(t_map *map, int number_lines, double square_size);

/** RAYCASTER HOR **/
void	instanciate_pos_hor(t_map *map, double square_size);
void	instanciate_length_hor(t_map *map, double tang, double square_size);
void	horizontal_check(t_map *map, double *length_case_x,
		double *length_case_y, double square);
void	horizontal_detection(t_map *map, int number_lines, double square_size);

/** RAYCASTER TOOLS **/
int	cpr_equal(double a, double b);
int	start_ray_direction(t_map *map);
double	radian_to_degree(double radian);
double	degree_to_radian(double degree);
double	max_case(char *line);

/** RAYCASTER TEX **/
int	text_map_u(t_map *map, t_image *img);
int	text_map_v(t_map *map, int height, double zoom);
void	texture_mapping(t_map *map, int x, t_image *img);
void	ceil_mapping(t_map *map, int x, int ceil_colour);
void	floor_mapping(t_map *map, int x, int floor_colour);

/** RAYCASTER ERRORS OR FREE **/
void check_error_ln_hor(t_map *map, double floor_pos_y);
void check_error_ln_ver(t_map *map, double floor_pos_x);
void	check_loop_cast_hor(t_map *map);
void	check_loop_cast_ver(t_map *map);
void	check_distance(t_map *map);

/** BONUS **/
int     find_sprite(t_map *map);
void    display_sprite(t_map *map, int square, unsigned int nb_spt);
void    quicksort_sprite(t_map *map, t_sprite *sprite,
                unsigned int nb_sprite, int square_size);
void    sprite_values_check(t_map *map, unsigned int nb_spt);
void    degree_check_divide(t_map *map, int nb_spt);
void    ft_swap(t_sprite *a, t_sprite *b);

#endif
