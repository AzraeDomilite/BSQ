/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_best.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:28:48 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/08 17:05:39 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_square.h"

void	set_square(t_square *best, int x, int y, int len)
{
	best->x = x;
	best->y = y;
	best->len = len;
}
