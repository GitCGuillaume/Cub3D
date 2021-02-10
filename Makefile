PATH_MAP	= ./srcs/map

PATH_UTILS	= ./srcs/utils

PATH_CHECK	= ./srcs/check_map

PATH_PARSE	= ./srcs/parse_map

PATH_PLAYER	= ./srcs/player

PATH_RAYCAST	= ./srcs/raycast

PATH_BMP	= ./srcs/bmp

PATH_GNL	= ./srcs/gnl

SRCS		= $(PATH_GNL)/get_next_line.c $(PATH_GNL)/get_next_line_utils.c \
		$(PATH_UTILS)/ft_isspace.c $(PATH_UTILS)/ft_swap.c $(PATH_UTILS)/close_program.c $(PATH_UTILS)/clear_program.c \
		$(PATH_UTILS)/colour.c $(PATH_UTILS)/xpm_image.c $(PATH_UTILS)/raycast_tools.c $(PATH_UTILS)/raycast_tools_two.c \
		$(PATH_PARSE)/parse_map_file.c $(PATH_PARSE)/parse_map_file_two.c $(PATH_PARSE)/parse_map_file_three.c \
		srcs/main.c $(PATH_CHECK)/check_validity_map.c $(PATH_CHECK)/check_validity_map_two.c \
		$(PATH_PLAYER)/player.c $(PATH_PLAYER)/control_player.c \
		$(PATH_MAP)/map.c $(PATH_MAP)/map_setting.c \
		$(PATH_RAYCAST)/raycast.c $(PATH_RAYCAST)/raycast_hor.c $(PATH_RAYCAST)/raycast_ver.c $(PATH_RAYCAST)/raycast_free.c \
		$(PATH_RAYCAST)/raycast_tex.c $(PATH_RAYCAST)/sprite.c $(PATH_RAYCAST)/sprite_tools.c $(PATH_RAYCAST)/sprite_tools_two.c \
		$(PATH_BMP)/bmp.c

OBJS		= $(SRCS:.c=.o)

NAME		= Cub3D

RM		= rm -f

.c.o:
		clang -Wall -Wextra -Werror -Iincludes -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
		$(MAKE) all -C srcs/libft/
		$(MAKE) -C ./minilibx-linux/
		clang -Wall -Wextra -Werror -L./minilibx-linux -L./includes -o $(NAME) $(OBJS) ./srcs/libft/libft.a -lm -lmlx -lXext -lX11

all:		$(NAME)

clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C ./srcs/libft/
		$(MAKE) clean -C ./minilibx-linux/

fclean:		clean
		$(MAKE) fclean -C ./srcs/libft/
		$(RM) ./$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
