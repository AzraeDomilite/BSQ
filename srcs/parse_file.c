/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:05:28 by blucken           #+#    #+#             */
/*   Updated: 2025/07/16 17:05:28 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include "t_brush.h"
#include "ft_split.h"
#include "strings.h"
#include "parse_file.h"
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 30000000

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
	if (rows != rows_read || rows <= 0)
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
	if (charset->empty == charset->obstacle || 
		charset->empty == charset->solution || 
		charset->obstacle == charset->solution ||
		charset->empty < 32 || charset->empty > 126 ||
		charset->obstacle < 32 || charset->obstacle > 126 ||
		charset->solution < 32 || charset->solution > 126)
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
		if (task->len_x == 0 || task->len_x > 10000)
			return (-1);
		task->map = malloc(task->len_x * task->len_y * sizeof (int));
		if (!task->map)
			return (-1);
	}
	j = 0;
	while (*line && j < task->len_x)
	{
		if (*line == charset->obstacle || *line == charset->empty)
			value = (*line == charset->obstacle);
		else
			return (free_on_error(task->map));
		set_map_value(task, j, row_number, value);
		line++;
		j++;
	}
	if (j != task->len_x)
		return (free_on_error(task->map));
	return (0);
}

int	read_task(int fd, t_map *task, t_brush *charset)
{
	char	*buffer;
	char	**lines;
	char	**lines_start;
	int		rows;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (-1);

	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read == -1 || bytes_read == 0)
	{
		free(buffer);
		return (-1);
	}
	if (bytes_read == BUFFER_SIZE - 1)
	{
		free(buffer);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	lines = ft_split(buffer, "\n");
	free(buffer);
	if (!lines)
		return (-1);
	rows = count_splits(lines) - 1;
	if (rows <= 0 || rows > 10000)
		return (on_error_free_splits(lines));
	if (parse_first_line(*lines, charset, rows) == (-1))
		return (on_error_free_splits(lines));
	task->len_y = rows;
	task->len_x = 0;
	task->map = 0;
	rows = -1;
	lines_start = lines;
	while (*(++lines) && (++rows >= 0))
		if (parse_line(*lines, task, rows, charset) == (-1))
			return (on_error_free_splits(lines_start));
	free_splits(lines_start);
	if (validate_map(task) == (-1))
	{
		free_on_error(task->map);
		return (-1);
	}
	return (0);
}

int	validate_map(t_map *task)
{
	if (!task || !task->map)
		return (-1);
	if (task->len_x <= 0 || task->len_y <= 0)
		return (-1);
	if (task->len_x > 10000 || task->len_y > 10000)
		return (-1);
	return (0);
}
