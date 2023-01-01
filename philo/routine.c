/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:18:10 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/09 23:18:10 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *data)
{
	struct timeval	now;

	pthread_mutex_lock(&data->forks_mutex[data->id - 1]);
	pthread_mutex_lock(&data->forks_mutex[data->id % data->philo_count]);
	data->forks[data->id - 1] = 1;
	data->forks[data->id % data->philo_count] = 1;
	gettimeofday(&now, NULL);
	data->last_meal = now;
	print_message(data, "has taken a fork", 0);
	print_message(data, "has taken a fork", 0);
}

void	return_fork(t_philo *data)
{
	data->forks[data->id - 1] = 0;
	data->forks[data->id % data->philo_count] = 0;
	pthread_mutex_unlock(&data->forks_mutex[data->id] - 1);
	pthread_mutex_unlock(&data->forks_mutex[data->id % data->philo_count]);
	data->times_eaten++;
}

void	*philo_routine(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	while (data->is_alive && *data->running)
	{
		take_fork(data);
		print_message(data, "is eating", 0);
		if (data->is_alive && *data->running)
			usleep(data->tt_eat * 1000);
		return_fork(data);
		if (data->max_eat && data->times_eaten >= data->max_eat)
			break;
		print_message(data, "is sleeping", 0);
		if (data->is_alive && *data->running)
			usleep(data->tt_sleep * 1000);
		print_message(data, "is thinking", 0);
	}
	if (data->max_eat && data->times_eaten >= data->max_eat)
		data->is_alive = -1;
	return (NULL);
}
