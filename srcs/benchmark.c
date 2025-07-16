/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:30:00 by blucken           #+#    #+#             */
/*   Updated: 2025/07/16 17:05:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "benchmark.h"
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

// Variables globales pour le benchmark
int g_benchmark_mode = 0;
FILE *g_benchmark_log = NULL;

struct timeval	get_current_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv);
}

double	get_time_diff(struct timeval start, struct timeval end)
{
	double start_time = start.tv_sec + start.tv_usec / 1000000.0;
	double end_time = end.tv_sec + end.tv_usec / 1000000.0;
	return (end_time - start_time);
}

void	print_benchmark_header(FILE *log_file)
{
	if (!log_file)
		return;
	
	fprintf(log_file, "# BSQ Benchmark Results\n");
	fprintf(log_file, "# Format: filename,map_width,map_height,map_size,parse_time(s),algo_time(s),total_time(s)\n");
	fprintf(log_file, "filename,map_width,map_height,map_size,parse_time,algo_time,total_time\n");
	fflush(log_file);
}

void	log_benchmark_result(t_benchmark_stats *stats, FILE *log_file)
{
	if (!log_file || !stats)
		return;
	
	// Extraire juste le nom du fichier sans le chemin
	char *filename_only = strrchr(stats->filename, '/');
	if (filename_only)
		filename_only++;
	else
		filename_only = stats->filename;
	
	fprintf(log_file, "%s,%d,%d,%d,%.6f,%.6f,%.6f\n",
		filename_only,
		stats->map_width,
		stats->map_height,
		stats->map_size,
		stats->parse_time,
		stats->algo_time,
		stats->total_time);
	
	fflush(log_file);
	
	// Afficher aussi sur stderr pour feedback immédiat
	fprintf(stderr, "BENCHMARK: %s - Parse: %.6fs, Algo: %.6fs, Total: %.6fs\n",
		filename_only,
		stats->parse_time,
		stats->algo_time,
		stats->total_time);
}
