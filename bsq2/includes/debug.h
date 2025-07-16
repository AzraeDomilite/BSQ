/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:41:38 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/09 19:27:12 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

t_map	*debug_create_map_from_str(char *str, int len_x, int len_y);
void	debug_print_map_colored(t_map *map, int x1, int y1);
void	debug_print_map(t_map *map);

#endif
