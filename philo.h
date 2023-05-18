/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:51:01 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/18 13:15:00 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> //FOR PRINTF! REMOVE!
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_to_eat;
	t_philo		**philosophers;
}				t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			times_eaten;
	// int			slept;
	// int			fork_l;
	// int			fork_r;
	t_data	*data;

}				t_philo;

int	check_input(char *arg);
int	is_num(char *arg, int check);
int	is_negative(char *arg, int check);
int	ft_strlen(char *str);
int	check_validity(char *arg, int num, t_data *data);
int	ft_atoi(const char *str);
int	init_args(int arg_i, int num, t_data *data);
void	*routine();
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
