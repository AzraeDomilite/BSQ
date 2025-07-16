/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:36:41 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/09 19:28:57 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H

typedef struct s_map {
	int	len_x;
	int	len_y;
	int	*map;
}	t_map;

int		get_map_value(t_map *map, int x, int y);
void	set_map_value(t_map *map, int x, int y, int value);
t_map	*allocate_map(int len_x, int len_y);
void	free_map(t_map *map);

#endif
