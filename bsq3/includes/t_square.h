/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_square.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:38:04 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/09 19:29:20 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SQUARE_H
# define T_SQUARE_H

typedef struct s_square {
	int	x;
	int	y;
	int	len;	
}	t_square;

void	set_square(t_square *best, int x, int y, int len);

#endif
