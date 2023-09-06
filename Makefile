PATH_MAP	= ./srcs/map

PATH_UTILS	= ./srcs/utils

PATH_CHECK	= ./srcs/check_map

PATH_PARSE	= ./srcs/parse_map

PATH_PLAYER	= ./srcs/player

PATH_RAYCAST	= ./srcs/raycast

PATH_GNL	= ./srcs/gnl

PATH_BONUS	= ./bonus

SRCS		= $(PATH_GNL)/get_next_line.c $(PATH_GNL)/get_next_line_utils.c \
		$(PATH_UTILS)/ft_isspace.c $(PATH_UTILS)/close_program.c $(PATH_UTILS)/clear_program.c \
		$(PATH_UTILS)/free_array.c $(PATH_UTILS)/colour.c $(PATH_UTILS)/xpm_image.c $(PATH_UTILS)/raycast_tools.c $(PATH_UTILS)/raycast_tools_two.c \
		$(PATH_PARSE)/parse_map_file.c $(PATH_PARSE)/parse_map_file_two.c $(PATH_PARSE)/parse_map_file_three.c $(PATH_PARSE)/parse_map_file_four.c \
		srcs/main.c $(PATH_CHECK)/check_validity_map.c $(PATH_CHECK)/check_validity_map_two.c $(PATH_CHECK)/check_validity_map_three.c \
		$(PATH_PLAYER)/player.c $(PATH_PLAYER)/control_player.c \
		$(PATH_MAP)/map.c $(PATH_MAP)/map_setting.c \
		$(PATH_RAYCAST)/raycast.c $(PATH_RAYCAST)/raycast_hor.c $(PATH_RAYCAST)/raycast_ver.c $(PATH_RAYCAST)/raycast_free.c \
		$(PATH_RAYCAST)/raycast_tex.c $(PATH_RAYCAST)/raycast_tex_two.c

SRCS_BONUS		= $(PATH_GNL)/get_next_line.c $(PATH_GNL)/get_next_line_utils.c \
		$(PATH_UTILS)/ft_isspace.c $(PATH_UTILS)/close_program.c $(PATH_UTILS)/clear_program.c \
		$(PATH_UTILS)/free_array.c $(PATH_UTILS)/colour.c $(PATH_UTILS)/xpm_image.c $(PATH_UTILS)/raycast_tools.c $(PATH_UTILS)/raycast_tools_two.c \
		$(PATH_PARSE)/parse_map_file.c $(PATH_PARSE)/parse_map_file_two.c $(PATH_PARSE)/parse_map_file_three.c $(PATH_PARSE)/parse_map_file_four.c \
		srcs/main.c $(PATH_CHECK)/check_validity_map.c $(PATH_CHECK)/check_validity_map_two.c $(PATH_CHECK)/check_validity_map_three.c \
		$(PATH_PLAYER)/player.c $(PATH_BONUS)/control_player_bonus.c \
		$(PATH_MAP)/map.c $(PATH_MAP)/map_setting.c \
		$(PATH_RAYCAST)/raycast.c $(PATH_RAYCAST)/raycast_hor.c $(PATH_RAYCAST)/raycast_ver.c $(PATH_RAYCAST)/raycast_free.c \
		$(PATH_RAYCAST)/raycast_tex.c $(PATH_RAYCAST)/raycast_tex_two.c


OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

NAME		= cub3D

NAME_BONUS	= cub3D_bonus

RM		= rm -f

.c.o:
		clang -Wall -Wextra -Werror -Iincludes -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
		$(MAKE) all -C ./libft/
		$(MAKE) -C ./minilibx-linux/
		clang -Wall -Wextra -Werror -L./minilibx-linux -L./includes -o $(NAME) $(OBJS) ./libft/libft.a -lm -lmlx -lXext -lX11

$(NAME_BONUS):	$(OBJS_BONUS)
		$(MAKE) all -C ./libft/
		$(MAKE) -C ./minilibx-linux/
		clang -Wall -Wextra -Werror -L./minilibx-linux -L./includes -o $(NAME_BONUS) $(OBJS_BONUS) ./libft/libft.a -lm -lmlx -lXext -lX11


all:		$(NAME)

clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C ./libft/
		$(MAKE) clean -C ./minilibx-linux/

fclean:		clean
		$(MAKE) fclean -C ./libft/
		$(MAKE) clean -C ./minilibx-linux/
		$(RM) ./$(NAME)

re:		fclean all

fclean_bonus:
		$(RM) $(OBJS_BONUS)
		$(MAKE) clean -C ./libft/
		$(MAKE) clean -C ./minilibx-linux/
		$(RM) $(NAME_BONUS)

bonus:		$(NAME_BONUS)

.PHONY:		all clean fclean re
