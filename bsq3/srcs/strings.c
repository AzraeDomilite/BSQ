/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:12:48 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/10 14:13:28 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
