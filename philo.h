/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:51:01 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/22 15:00:31 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef long long t_mcrosec;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					philo_count;
	t_mcrosec			time_to_die;
	t_mcrosec			time_to_eat;
	t_mcrosec			time_to_sleep;
	t_mcrosec 			starting_time;
	int					nb_to_eat;
	int					stop_simulation;
	pthread_mutex_t		*fork_lock;
	pthread_mutex_t		eating;
	pthread_mutex_t		sleeping;
	pthread_mutex_t		printing;
	pthread_mutex_t		routine;
	t_philo				*philo;
}				t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					times_eaten;
	t_mcrosec			last_meal;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	t_data				*data;
}				t_philo;

int	check_input(char *arg);
int	is_num(char *arg, int check);
int	is_negative(char *arg, int check);
int	ft_strlen(char *str);
int	check_validity(char *arg, int num, t_data *data);
int	ft_atoi(const char *str);
int	init_args(int arg_i, int num, t_data *data);
int	init_mutexes(t_data *data);
void	*routine();
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	join_and_free(t_data *data);
void	eating(t_philo *philo, t_mcrosec time_to_eat);
void	sleeping(t_philo *philo, t_mcrosec time_to_eat);
t_data	*init_data(int argc, char **argv);
t_philo *init_philos(t_data *data);
void	philo_wait(t_mcrosec time_to_eat);
int	get_the_time();

#endif
