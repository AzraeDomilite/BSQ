/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:09 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/10 14:13:02 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

int		in_str(char c, char *charset);
void	ft_strncpy(char *dest, char *src, int n);
int		next_char_in_charset(char *str, char *charset);
int		ft_strlen(char *str);

#endif
