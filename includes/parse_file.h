/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:08:07 by baschnit          #+#    #+#             */
/*   Updated: 2025/07/16 16:29:03 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FILE_H
# define PARSE_FILE_H

int	read_task(int fd, t_map *task, t_brush *charset);
int	validate_map(t_map *task);

#endif
