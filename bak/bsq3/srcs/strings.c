/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:12:03 by blucken           #+#    #+#             */
/*   Updated: 2025/07/16 16:12:38 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	in_str(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

void	ft_strncpy(char *dest, char *src, int n)
{
	int		index;

	index = 0;
	while (*src && index < n)
	{
		*dest = *src;
		src++;
		dest++;
		index++;
	}
	*dest = '\0';
}

int	next_char_in_charset(char *str, char *charset)
{
	int	index;

	index = 0;
	while (*str && !in_str(*str, charset))
	{
		str++;
		index++;
	}
	return (index);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

