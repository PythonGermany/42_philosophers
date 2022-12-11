/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:54:57 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/09 21:54:57 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	check_int(char **str)
{
	int	i;
	int	i2;

	i = 0;
	while (str[i] != NULL)
	{
		if ((ft_strlen(str[i]) > 10) || *str[i] == '0')
			return (1);
		i2 = -1;
		while (++i2 < ft_strlen(str[i]))
			if (str[i][i2] < '0' || str[i][i2] > '9' \
			|| (str[i][i2] > "2147483647"[i2] && ft_strlen(str[i]) > 9))
				return (1);
		i++;
	}
	return (0);
}

void	terminate_data(t_data *data)
{
	while (--data->philo_count >= 0)
	{
		free(data->philo_data[data->philo_count]->is_alive);
		free(data->philo_data[data->philo_count]);
		pthread_mutex_destroy(&data->forks_mutex[data->philo_count]);
	}
	pthread_mutex_destroy(&data->output);
	free(data->philos);
	free(data->philo_data);
	free(data->forks_mutex);
	free(data->forks);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (argc < 5 || argc > 6 || check_int(argv + 1))
	{
		printf("Use: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	else
	{
		data = init_data(argv + 1);
		i = -1;
		while (++i < data->philo_count)
			pthread_create(&data->philos[i], NULL, &philo_routine, (void *)data->philo_data[i]);
		while (data->running)
		{
			i = 0;
			while (i < data->philo_count)
				if (!*(data->philo_data[i++]->is_alive))
					break ;
			if (!*(data->philo_data[i - 1]->is_alive))
			{
				print_message(data->philo_data[i - 1], "died");
				data->running = 0;
			}
		}
		i = -1;
		while (++i < data->philo_count)
			pthread_join(data->philos[i], NULL);
		terminate_data(data);
	}
}
