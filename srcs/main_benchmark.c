/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_benchmark.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:46:02 by blucken           #+#    #+#             */
/*   Updated: 2025/07/16 17:05:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include "t_square.h"
#include "t_brush.h"
#include "debug.h"
#include "pnl.h"
#include "parse_file.h"
#include "benchmark.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

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

int	process_file_with_benchmark(char *filename, FILE *log_file)
{
	t_map		task;
	t_square	solution;
	t_brush		charset;
	int			fd;
	struct timeval	start_total, end_parse, end_algo;
	t_benchmark_stats stats;

	// Initialisation
	task.len_x = 0;
	memset(&stats, 0, sizeof(stats));
	stats.filename = filename;
	
	// Ouverture du fichier
	if (strcmp(filename, "stdin") == 0)
		fd = 0;
	else
		fd = open(filename, O_RDONLY);
	
	if (fd == -1)
		return (print_error());
	
	// Début du timing total
	start_total = get_current_time();
	
	// Phase 1: Parsing
	if (read_task(fd, &task, &charset) == -1)
	{
		close(fd);
		return (print_error());
	}
	
	// Fin du parsing
	end_parse = get_current_time();
	close(fd);
	
	// Phase 2: Algorithme
	set_square(&solution, -1, -1, 0);
	get_best_square(&task, &solution);
	
	// Fin de l'algorithme
	end_algo = get_current_time();
	
	// Calcul des statistiques
	stats.parse_time = get_time_diff(start_total, end_parse);
	stats.algo_time = get_time_diff(end_parse, end_algo);
	stats.total_time = get_time_diff(start_total, end_algo);
	stats.map_width = task.len_x;
	stats.map_height = task.len_y;
	stats.map_size = task.len_x * task.len_y;
	
	// Log du résultat
	if (log_file)
		log_benchmark_result(&stats, log_file);
	
	// En mode benchmark, aussi écrire sur stdout pour le script
	if (g_benchmark_mode)
	{
		printf("%s,%d,%d,%d,%.6f,%.6f,%.6f\n",
			(strrchr(stats.filename, '/') ? strrchr(stats.filename, '/') + 1 : stats.filename),
			stats.map_width,
			stats.map_height,
			stats.map_size,
			stats.parse_time,
			stats.algo_time,
			stats.total_time);
	}
	
	// Afficher le résultat seulement si pas en mode benchmark
	if (!g_benchmark_mode)
		print_result(&task, charset, solution);
	
	free_task_map(task.map);
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	FILE	*log_file = NULL;
	
	// Vérifier le mode benchmark
	if (argc > 1 && strcmp(argv[1], "--benchmark") == 0)
	{
		g_benchmark_mode = 1;
		
		// Ouvrir le fichier de log
		log_file = fopen("benchmark_results.csv", "w");
		if (!log_file)
		{
			write(2, "Erreur: Impossible d'ouvrir le fichier de log\n", 47);
			return (1);
		}
		
		print_benchmark_header(log_file);
		
		// Décaler les arguments
		argc--;
		argv++;
	}
	
	// Traitement des fichiers
	i = -1;
	while (++i < argc - 1 || (argc == 1 && i == 0))
	{
		if (argc == 1)
			process_file_with_benchmark("stdin", log_file);
		else
			process_file_with_benchmark(argv[i + 1], log_file);
	}
	
	// Fermer le fichier de log
	if (log_file)
	{
		fclose(log_file);
		if (g_benchmark_mode)
			fprintf(stderr, "Résultats du benchmark sauvegardés dans benchmark_results.csv\n");
	}
	
	return (0);
}
