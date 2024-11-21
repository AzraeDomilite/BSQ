/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:24:13 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/09 19:30:59 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include <unistd.h>
#include <stdio.h>

t_map	*debug_create_map_from_str(char *str, int len_x, int len_y)
{
	t_map	*map;
	int		i;

	map = allocate_map(len_x, len_y);
	i = 0;
	while (*str)
	{
		set_map_value(map, i % len_x, i / len_x, *str - '0');
		i++;
		str++;
	}
	return (map);
}

void	debug_print_nbr(int nbr)
{
	char	out;

	if (nbr / 10 != 0)
		debug_print_nbr(nbr / 10);
	out = nbr % 10 + '0';
	write (1, &out, 1);
}

void	debug_print_map(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->len_y)
	{
		x = -1;
		while (++x < map->len_x)
		{
			debug_print_nbr(get_map_value(map, x, y));
			if (x == map->len_x - 1)
				write(1, "\n", 1);
		}
	}
}

void	debug_print_map_colored(t_map *map, int x1, int y1)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->len_y)
	{
		x = -1;
		while (++x < map->len_x)
		{
			if ((x == x1 && y == y1))
				printf("\x1b[31m%d\x1b[0m", get_map_value(map, x, y));
			else
				printf("%d", get_map_value(map, x, y));
			if (x == map->len_x - 1)
				printf("\n");
		}
	}
}
