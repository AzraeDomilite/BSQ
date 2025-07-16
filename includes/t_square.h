/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_square.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:05:55 by blucken           #+#    #+#             */
/*   Updated: 2025/07/16 17:12:59 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SQUARE_H
# define T_SQUARE_H

typedef struct s_square
{
	int	x;
	int	y;
	int	len;	
}	t_square;

void	set_square(t_square *best, int x, int y, int len);

#endif
