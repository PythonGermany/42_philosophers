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

static void	take_fork(t_philo *data)
{
	struct timeval	now;

	pthread_mutex_lock(&data->forks[data->id - 1]);
	pthread_mutex_lock(&data->forks[data->id % data->philo_count]);
	gettimeofday(&now, NULL);
	data->last_meal = now;
	print_message(data, "has taken a fork", 0);
	print_message(data, "has taken a fork", 0);
}

static void	return_fork(t_philo *data)
{
	pthread_mutex_unlock(&data->forks[data->id] - 1);
	pthread_mutex_unlock(&data->forks[data->id % data->philo_count]);
	data->times_eaten++;
}

void	*philo_routine(void *arg)
{
	t_philo	*data;
	struct timeval	start_eating;
	struct timeval	start_sleeping;

	data = (t_philo *)arg;
	while (data->is_alive && *data->running)
	{
		gettimeofday(&start_eating, NULL);
		take_fork(data);
		print_message(data, "is eating", 0);
		while (data->is_alive && *data->running
			&& get_time_diff(&start_eating) < data->tt_eat)
			usleep(10);
		return_fork(data);
		if (data->max_eat && data->times_eaten >= data->max_eat)
			break ;
		gettimeofday(&start_sleeping, NULL);
		print_message(data, "is sleeping", 0);
		while (data->is_alive && *data->running
			&& get_time_diff(&start_sleeping) < data->tt_sleep)
			usleep(10);
		print_message(data, "is thinking", 0);
	}
	if (data->max_eat && data->times_eaten >= data->max_eat)
		data->is_alive = -1;
	return (NULL);
}
