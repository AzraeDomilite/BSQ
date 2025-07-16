/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:19:57 by blucken           #+#    #+#             */
/*   Updated: 2024/07/10 20:00:45 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include "t_square.h"
#include <stdlib.h>

int	get_obstacles(t_map *density, int x, int y, int len)
{
	int	result;

	result = 0;
	result += get_map_value(density, x, y);
	result += get_map_value(density, x + len, y + len);
	result -= get_map_value(density, x + len, y);
	result -= get_map_value(density, x, y + len);
	return (result);
}

int	check_solution_for_point(t_map *density, t_square *best, int x, int y)
{
	int			len;
	int			count;
	int			break_total;

	break_total = 0;
	count = 0;
	while (1)
	{
		len = best->len + 1;
		if (x + len > density->len_x || y + len > density->len_y)
			break ;
		else
		count = get_obstacles(density, x - 1, y - 1, len);
		if (!break_total && count == 0)
			set_square(best, x, y, len);
		else
		{
			if (x + len - 1 >= density->len_x && y + len - 1 >= density->len_y)
				break_total = 1;
			break ;
		}
	}
	return (break_total);
}

void	find_solution(t_map *density, t_square *best)
{
	int	x;
	int	y;
	int	break_total;

	y = -1;
	break_total = 0;
	while (!break_total && ++y < density->len_y)
	{
		x = -1;
		while (!break_total && ++x < density->len_x)
			break_total = check_solution_for_point(density, best, x, y);
	}
}

t_map	*create_density_map(t_map *task)
{
	t_map	*density;
	int		x;
	int		y;

	y = -1;
	density = allocate_map(task->len_x, task->len_y);
	while (++y < task->len_y)
	{
		x = -1;
		while (++x < task->len_x)
			set_map_value(density, x, y,
				+ get_map_value(task, x, y)
				+ get_map_value(density, x, y - 1)
				+ get_map_value(density, x - 1, y)
				- get_map_value(density, x - 1, y - 1));
	}
	return (density);
}

void	get_best_square(t_map *task, t_square *best)
{
	t_map	*density;

	density = create_density_map(task);
	find_solution(density, best);
	free_map(density);
}
