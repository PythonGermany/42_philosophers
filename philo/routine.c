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

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

int	get_time_diff(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000 + \
	((double)now.tv_usec - start.tv_usec) / 1000);
}

void	print_message(t_philo *data, char *msg)
{
	pthread_mutex_lock(data->output);
	if (*data->running)
		printf("%d %d %s\n", get_time_diff(*data->time), data->id, msg);
	pthread_mutex_unlock(data->output);
}

void	take_fork(t_philo *data)
{
	struct timeval	now;

	while (data->philo_count < 2 || data->forks[data->id - 1] \
	|| data->forks[data->id % data->philo_count])
	{
		if (get_time_diff(data->last_meal) * 1000 > data->tt_die)
		{
			*data->is_alive = 0;
			return ;
		}
	}
	pthread_mutex_lock(&data->forks_mutex[data->id - 1]);
	pthread_mutex_lock(&data->forks_mutex[data->id % data->philo_count]);
	data->forks[data->id - 1] = 1;
	data->forks[data->id % data->philo_count] = 1;
	print_message(data, "has taken a fork");
	print_message(data, "has taken a fork");
	gettimeofday(&now, NULL);
	data->last_meal = now;
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
	while (1)
	{
		take_fork(data);
		if (*data->is_alive)
		{
			print_message(data, "is eating");
			usleep(data->tt_eat);
			return_fork(data);
			if ((data->max_eat && data->times_eaten >= data->max_eat) \
				|| !*data->is_alive || !*data->running)
				break ;
			print_message(data, "is sleeping");
			usleep(data->tt_sleep);
			print_message(data, "is thinking");
		}
		else
			break ;
	}
	return (NULL);
}
