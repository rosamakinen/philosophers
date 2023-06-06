/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:51:01 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/06 15:35:45 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h> //!!!!!!
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
	int					exit_flag; // REMOVE??
	int					buffer;
	int					all_eaten;
	pthread_mutex_t		*fork_lock;
	pthread_mutex_t		printing;
	pthread_mutex_t		routine;
	pthread_mutex_t		checking;
	pthread_mutex_t		finish;
	t_philo				*philo;
}				t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					times_eaten;
	t_mcrosec			last_meal;
	int					flag;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	pthread_mutex_t		eating;
	t_data				*data;
}				t_philo;

//checks

int		check_input(char *arg);
int		is_num(char *arg, int check);
int		is_negative(char *arg, int check);
int		ft_strlen(char *str);
int		check_validity(char *arg, int num, t_data *data);

//init
int		init_args(int arg_i, int num, t_data *data);
int		init_mutexes(t_data *data);
t_data	*init_data(int argc, char **argv);
t_philo *init_philos(t_data *data);
t_philo	*assign_forks(t_philo *temp_philo);

//utils
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	destroy_free(t_data *data);

//routine

void	*routine(void *philo);
int		eating(t_philo *philo, t_mcrosec time_to_eat);
int		sleeping(t_philo *philo);
int		eating_alone(t_philo *philo);
int		take_forks(t_philo *philo);

//monitoring & printing
void			philo_wait(t_data *data, t_mcrosec time_to_eat);
long long		get_the_time();
int				monitoring(t_data *data);
int				print_message(t_philo *philo, char *message);
int				check_if_dead(t_philo *philo);
int				check_flag(t_data *data, int flag);
int				check_last_meal(t_philo *philo);

#endif
