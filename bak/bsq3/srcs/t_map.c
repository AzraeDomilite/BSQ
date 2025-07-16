/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:28:55 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/09 19:43:33 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include <stdlib.h>

int	get_map_value(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->len_x || y >= map->len_y)
		return (0);
	else
		return (*(map->map + (y * map->len_x + x)));
}

void	set_map_value(t_map *map, int x, int y, int value)
{
	if (x < 0 || y < 0 || x >= map->len_x || y >= map->len_y)
		return ;
	else
		*(map->map + (y * map->len_x + x)) = value;
}

t_map	*allocate_map(int len_x, int len_y)
{
	t_map	*map;

	map = malloc(sizeof (t_map));
	map->len_x = len_x;
	map->len_y = len_y;
	map->map = malloc(len_x * len_y * sizeof (int));
	return (map);
}

void	free_map(t_map *map)
{
	free(map->map);
	free(map);
}
