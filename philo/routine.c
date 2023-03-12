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

static void	print_message(t_philo *data, char *msg, int disable_output)
{
	pthread_mutex_lock(data->output);
	if (*data->running)
	{
		if (disable_output)
			*data->running = 0;
		printf("%d %d %s\n", time_diff(data->time), data->id, msg);
	}
	pthread_mutex_unlock(data->output);
}

int	check_vitals(t_philo *data)
{
	if (time_diff(data->time) - data->last_meal >= data->tt_die)
		return (print_message(data, "died", 1), 0);
	return (1);
}

static void	take_fork(t_philo *data, struct timeval	*start_eat)
{
	pthread_mutex_lock(&data->forks[data->id - 1]);
	if (data->philo_count > 1)
		pthread_mutex_lock(&data->forks[data->id % data->philo_count]);
	gettimeofday(start_eat, NULL);
	data->last_meal = time_diff(data->time);
	print_message(data, "has taken a fork", 0);
	if (data->philo_count > 1)
		print_message(data, "has taken a fork", 0);
	else
		while (*data->running)
			continue ;
}

void	*philo_routine(void *arg)
{
	t_philo			*data;
	struct timeval	start_eat;
	struct timeval	start_sleep;

	data = (t_philo *)arg;
	while (*data->running != 0)
	{
		take_fork(data, &start_eat);
		print_message(data, "is eating", 0);
		while (*data->running && time_diff(&start_eat) < data->tt_eat)
			usleep(10);
		pthread_mutex_unlock(&data->forks[data->id] - 1);
		if (data->philo_count > 1)
			pthread_mutex_unlock(&data->forks[data->id % data->philo_count]);
		gettimeofday(&start_sleep, NULL);
		if (data->max_eat && ++data->times_eaten >= data->max_eat)
			break ;
		print_message(data, "is sleeping", 0);
		while (*data->running && time_diff(&start_sleep) < data->tt_sleep)
			usleep(10);
		print_message(data, "is thinking", 0);
	}
	if (data->max_eat && data->times_eaten >= data->max_eat)
		data->times_eaten = -1;
	return (NULL);
}
