/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:05:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/10 19:38:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include "t_brush.h"
#include "ft_split.h"
#include "strings.h"
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE (int) 7e6

int	on_error_free_splits(char **splits)
{
	free_splits(splits);
	return (-1);
}

int	free_on_error(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = 0;
	}
	return (-1);
}

int	parse_first_line(char *line, t_brush *charset, int rows_read)
{
	int	rows;

	line = line - 1;
	rows = 0;
	while (*(++line) && *line >= '0' && *line <= '9' && rows < rows_read)
		rows = 10 * rows + *line - '0';
	if (rows != rows_read)
		return (-1);
	rows = 0;
	while (*line)
	{
		if (rows == 0)
			charset->empty = *line;
		else if (rows == 1)
			charset->obstacle = *line;
		else if (rows == 2)
			charset->solution = *line;
		rows++;
		line++;
	}
	if (rows != 3)
		return (-1);
	return (0);
}

int	parse_line(char *line, t_map *task, int row_number, t_brush *charset)
{
	int		j;
	int		value;

	if (task->len_x == 0)
	{
		task->len_x = ft_strlen(line);
		if (task->len_x != 0)
			task->map = malloc(task->len_x * task->len_y * sizeof (int));
		if (task->len_x == 0 || !task->map)
			return (-1);
	}
	j = 0;
	while (*line && ++j)
	{
		if (*line == charset->obstacle || *line == charset->empty)
			value = (*line == charset->obstacle);
		else
			return (free_on_error(task->map));
		set_map_value(task, j, row_number, value);
		line++;
	}
	if (j != task->len_x)
		return (free_on_error(task->map));
	return (0);
}

int	read_task(int fd, t_map *task, t_brush *charset)
{
	char	buffer[BUFFER_SIZE];
	char	**lines;
	char	**lines_start;
	int		rows;

	rows = 0;
	rows = read(fd, buffer, BUFFER_SIZE);
	if (rows == -1 || rows == BUFFER_SIZE)
		return (-1);
	buffer[rows] = '\0';
	lines = ft_split(buffer, "\n");
	rows = count_splits(lines) - 1;
	if (rows <= 0)
		return (on_error_free_splits(lines));
	if (parse_first_line(*lines, charset, rows) == (-1))
		return (on_error_free_splits(lines));
	task->len_y = rows;
	rows = -1;
	lines_start = lines;
	while (*(++lines) && (++rows >= 0))
		if (parse_line(*lines, task, rows, charset) == (-1))
			return (on_error_free_splits(lines_start));
	free_splits(lines_start);
	return (0);
}