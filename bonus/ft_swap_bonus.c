/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:48:44 by cmois             #+#    #+#             */
/*   Updated: 2022/04/12 13:48:45 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	ft_swap(t_sprite *a, t_sprite *b)
{
	t_sprite	c;

	c = *a;
	*a = *b;
	*b = c;
}
