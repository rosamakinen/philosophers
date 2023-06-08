/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:51:01 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/08 07:55:23 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					philo_count;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			starting_time;
	int					nb_to_eat;
	int					exit_flag;
	int					all_eaten;
	int					buffer;
	pthread_mutex_t		*fork_lock;
	pthread_mutex_t		printing;
	pthread_mutex_t		routine;
	pthread_mutex_t		checking;
	t_philo				*philo;
}				t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					times_eaten;
	int					flag;
	long long			last_meal;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	pthread_mutex_t		eating;
	t_data				*data;
}				t_philo;

//checks
int			check_input(int argc, char **argv);
int			is_num(char *arg, int check);
int			is_negative(char *arg, int check);
int			check_validity(int c, int argc, char **argv);

//init
int			init_args(int arg_i, int num, t_data *data);
int			init_mutexes(t_data *data);
t_data		*init_data(int argc, char **argv);
t_philo		*init_philos(t_data *data);

//utils
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			destroy_free(t_data *data);

//routine

void		*routine(void *philo);
int			eating(t_philo *philo, long long time_to_eat);
int			sleeping(t_philo *philo);
int			eating_alone(t_philo *philo);
int			take_forks(t_philo *philo);

//monitoring & printing
void		philo_wait(t_data *data, long long time_to_eat);
int			monitoring(t_data *data);
int			print_message(t_philo *philo, char *message);
int			check_if_dead(t_philo *philo);
int			check_flag(t_data *data, int flag);
int			check_last_meal(t_philo *philo);
long long	get_the_time(void);

#endif
