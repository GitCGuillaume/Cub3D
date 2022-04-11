/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:41:51 by gchopin           #+#    #+#             */
/*   Updated: 2022/04/11 16:56:54 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "cub.h"

/** BONUS **/
int		find_sprite(t_map *map);
void	display_sprite(t_map *map, int square, unsigned int nb_spt);
void	quicksort_sprite(t_map *map, t_sprite *sprite,
			unsigned int nb_sprite, int square_size);
void	sprite_values_check(t_map *map, unsigned int nb_spt);
void	degree_check_divide(t_map *map, int nb_spt);
void	ft_swap(t_sprite *a, t_sprite *b);
void	write_in_image_one(t_map *map, int u, int v, int pixel);
void	write_in_image_two(t_map *map, int u, int v, int pixel);
void	tick_handler(t_map *map);
void	print_sprite(t_map *map, int pixel, int nb_sprite, int height);

#endif
