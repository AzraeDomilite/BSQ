/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:44:04 by blucken           #+#    #+#             */
/*   Updated: 2025/07/16 16:46:57 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_H
# define BENCHMARK_H

# include <sys/time.h>
# include <stdio.h>

typedef struct s_benchmark_stats {
	double	parse_time;
	double	algo_time;
	double	total_time;
	int		map_width;
	int		map_height;
	int		map_size;
	char	*filename;
}	t_benchmark_stats;

// Fonctions utilitaires pour le benchmark
double		get_time_diff(struct timeval start, struct timeval end);
void		log_benchmark_result(t_benchmark_stats *stats, FILE *log_file);
void		print_benchmark_header(FILE *log_file);
struct timeval	get_current_time(void);

// Variables globales pour le benchmark
extern int g_benchmark_mode;
extern FILE *g_benchmark_log;

#endif
