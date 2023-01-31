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
	pthread_mutex_lock(&data->forks[data->id - 1]);
	if (data->philo_count > 1)
		pthread_mutex_lock(&data->forks[data->id % data->philo_count]);
	//printf("DEBUG: %i %i\n", data->id, get_time_diff(data->time) - data->last_meal);
	data->last_meal = get_time_diff(data->time);
	//printf("DEBUG: %i %i\n", data->id, get_time_diff(data->time) - data->last_meal);
	print_message(data, "has taken a fork", 0);
	if (data->philo_count > 1)
		print_message(data, "has taken a fork", 0);
	else
		while (*data->running == 1)
			continue ;
}

static void	return_fork(t_philo *data)
{
	pthread_mutex_unlock(&data->forks[data->id] - 1);
	if (data->philo_count > 1)
		pthread_mutex_unlock(&data->forks[data->id % data->philo_count]);
	data->times_eaten++;
}

void	*philo_routine(void *arg)
{
	t_philo			*data;
	struct timeval	start_eat;
	struct timeval	start_sleep;

	data = (t_philo *)arg;
	while (*data->running)
	{
		take_fork(data);
		gettimeofday(&start_eat, NULL);
		print_message(data, "is eating", 0);
		while (*data->running && get_time_diff(&start_eat) < data->tt_eat)
			usleep(10);
		return_fork(data);
		if (data->max_eat && data->times_eaten >= data->max_eat)
			break ;
		gettimeofday(&start_sleep, NULL);
		print_message(data, "is sleeping", 0);
		while (*data->running && get_time_diff(&start_sleep) < data->tt_sleep)
			usleep(10);
		print_message(data, "is thinking", 0);
	}
	if (data->max_eat && data->times_eaten >= data->max_eat)
		data->is_done = 0;
	return (NULL);
}
