/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:12:54 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/09 20:14:16 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "strings.h"

int	count_splits(char **splits)
{
	int	i;

	i = 0;
	while (*splits)
	{
		i++;
		splits++;
	}	
	return (i);
}

void	free_splits(char **splits)
{
	char	**split;

	if (!splits)
		return ;
	split = splits;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(splits);
}

void	set_splits(char **tab, char *str, char *charset)
{
	char	*i;
	int		len;
	int		count;

	count = 0;
	i = str - 1;
	while ((*++i))
	{
		if ((i - 1 < str || in_str(*(i - 1), charset)) && !in_str(*i, charset))
		{
			len = next_char_in_charset(i, charset);
			*tab = malloc((len + 1) * sizeof (char));
			if (*tab)
				ft_strncpy(*tab, i, len);
			count++;
			tab++;
		}
	}
	*tab = 0;
}

char	**ft_split(char *str, char *charset)
{
	char	*i;
	char	**tab;
	int		count;

	if (!*str)
	{
		tab = (char **) malloc(sizeof (char *));
		*tab = 0;
		return (tab);
	}
	count = 0;
	i = str - 1;
	while (*(++i))
		if ((i - 1 < str || in_str(*(i - 1), charset)) && !in_str(*i, charset))
			count++;
	tab = (char **) malloc((count + 1) * sizeof (char *));
	if (tab)
		set_splits(tab, str, charset);
	return (tab);
}