/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:13:22 by baschnit          #+#    #+#             */
/*   Updated: 2024/07/10 20:00:22 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include "t_square.h"
#include "t_brush.h"
#include "pnl.h"
#include "parse_file.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE (int) 7e6

void	print_result(t_map *task, t_brush charset, t_square solution)
{
	int		x;
	int		y;

	y = -1;
	while (++y < task->len_y)
	{
		x = -1;
		while (++x < task->len_x)
		{
			if (x >= solution.x && y >= solution.y && x <= solution.x
				+ solution.len - 1 && y <= solution.y + solution.len - 1)
				write(1, &(charset.solution), 1);
			else if (get_map_value(task, x, y) == 1)
				write(1, &(charset.obstacle), 1);
			else
				write(1, &(charset.empty), 1);
			if (x == task->len_x - 1)
				write(1, "\n", 1);
		}
	}
}	

int	print_error(void)
{
	write(2, "map error\n", 10);
	return (0);
}

void	free_task_map(int *ptr)
{
	if (ptr)
		free(ptr);
}

int	main(int argc, char **argv)
{
	t_map		task;
	t_square	solution;
	t_brush		charset;
	int			i;
	int			fd;

	i = -1;
	while (++i < argc - 1 || (argc == 1 && i == 0))
	{
		task.len_x = 0;
		if (argc == 1)
			fd = 0;
		else
			fd = open(argv[i + 1], O_RDONLY);
		if (fd == (-1) || read_task(fd, &task, &charset) == (-1))
			if (!print_error())
				continue ;
		close(fd);
		set_square(&solution, -1, -1, 0);
		get_best_square(&task, &solution);
		print_result(&task, charset, solution);
		free_task_map(task.map);
	}
	return (0);
}
