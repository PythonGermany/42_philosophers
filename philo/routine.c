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
	pthread_mutex_lock(data->mutex_running);
	if (*data->running != 0)
	{
		printf("%llu %d %s\n", time_diff(data->time) / 1000, data->id, msg);
		for (int i = 0; i < data->philo_count; i++)
		{
			printf("%i ", data->fork_state[i]);
		}
		printf("\n");
	}
	if (disable_output != 0)
		*data->running = 0;
	pthread_mutex_unlock(data->mutex_running);
	pthread_mutex_unlock(data->output);
}

static int	check_vitals(t_philo *data)
{
	int	rn;

	if (time_diff(data->time) - data->last_meal >= data->tt_die)
		print_message(data, "died", 1);
	pthread_mutex_lock(data->mutex_running);
	rn = *data->running;
	pthread_mutex_unlock(data->mutex_running);
	return (rn);
}

static int	change_fork_state(t_philo *data, int fork_id, int new_state)
{
	int	state;

	pthread_mutex_lock(&data->forks[fork_id]);
	if (!data->fork_state[fork_id] || data->fork_state[fork_id] == data->id)
		data->fork_state[fork_id] = (new_state != 0) * data->id;
	state = data->fork_state[fork_id];
	pthread_mutex_unlock(&data->forks[fork_id]);
	return (state == data->id);
}

static void	take_forks(t_philo *data)
{
	while (check_vitals(data) && (!change_fork_state(data, data->id - 1, 1) \
		|| !change_fork_state(data, data->id % data->philo_count, 1)))
		continue ;
	data->last_meal = time_diff(data->time);
	print_message(data, "has taken a fork", 0);
	if (data->philo_count > 1)
		print_message(data, "has taken a fork", 0);
	else
		while (check_vitals(data))
			continue ;
}

void	*philo_routine(void *arg)
{
	t_philo			*data;
	struct timeval	start_eat;
	struct timeval	start_sleep;

	data = (t_philo *)arg;
	while (check_vitals(data))
	{
		take_forks(data);
		gettimeofday(&start_eat, NULL);
		print_message(data, "is eating", 0);
		while (check_vitals(data) && time_diff(&start_eat) < data->tt_eat)
			usleep(10);
		change_fork_state(data, data->id - 1, 0);
		if (data->philo_count > 1)
			change_fork_state(data, data->id % data->philo_count, 0);
		gettimeofday(&start_sleep, NULL);
		if (data->max_eat && ++data->times_eaten >= data->max_eat)
			break ;
		print_message(data, "is sleeping", 0);
		while (check_vitals(data) && time_diff(&start_sleep) < data->tt_sleep)
			usleep(10);
		print_message(data, "is thinking", 0);
	}
	return (NULL);
}
