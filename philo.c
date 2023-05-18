/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:21:30 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/18 14:11:35 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine()
{
	printf("whatever is routine\n");
	return (0);
}

// int	make_philos(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	data->philosophers = ft_calloc(data->philo_count, sizeof(t_philo));
// 	if (data->philosophers == NULL)
// 		return (1);
// 	while (i < data->philo_count)
// 	{
// 		data->philosophers->id = (i + 1);
// 		data->philosophers->times_eaten = 0;
// 		data->philosophers->data = data;
// 		i++;
// 	}
// 	return (0);
// }

// int	make_threads(t_data *data)
// {
	// int			i;
	//pthread_t		temp_thread;

	// i = 1;
	// printf("count: %i\n", data->philo_count);
	// printf("i : %i\n", i);
	//temp_thread = NULL;
	// while(i <= data->philo_count)
	// {
	// 	printf("philo->thread[%i] created\n", i);
	// 	if (pthread_create(&data->philosophers[i].thread, NULL, &routine, NULL) != 0)
	// 		return (1);
	// 	printf("huh?\n");
		//data->philo[i]->thread = temp_thread;
	// 	i++;
	// }
	// printf("nb of philos %i\n", data->philo_count);
	// i = 0;
	// while(i < data->philo_count)
	// {
	// 	printf("philo->thread[%i] joined", i);
	// 	if(pthread_join(data->philo[i]->thread, NULL) != 0)
	// 	i++;
	// }
// 	return (0);
// }

// int	start_routine(t_data *data)
// {
// 	make_philos(data);
// 	make_threads(data);
// 	return (0);
// }

t_philo **init_philos(t_data *data)
{
	t_philo **philos;
	int		i;

	i = 0;
	philos = ft_calloc(data->philo_count, sizeof(t_philo));
	if (!philos)
		return (NULL);
	while (i < data->philo_count)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->times_eaten = 0;
		pthread_create(&philos[i]->thread, NULL, &routine, NULL);
		i++;
	}
	return (philos);
}

t_data	*init_data(int argc, char **argv)
{
	t_data *data;
	int		i;

	i = 1;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	while (i < argc)
	{
		check_input(argv[i]);
		check_validity(argv[i], i, data);
		i++;
	}
	data->philosophers = init_philos(data);
	if (!data->philosophers)
		return (NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
		exit (1);
	i = 1;
	data = init_data(argc, argv);
	if (!data)
		return (0);
	printf("yes?");
	//start_routine(data);
	printf("yes?");
	return (0);
}
