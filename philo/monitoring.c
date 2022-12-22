/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:00:57 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/22 14:30:56 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_vitals(t_philo *data)
{
	if (get_time_diff(data->last_meal) > data->tt_die)
		*data->is_alive = 0;
	return (*data->is_alive);
}

void	monitor_simulation(t_data *data)
{
	int	eat_limit;
	int	i;

	while (data->running)
	{
		i = 0;
		eat_limit = 0;
		while (i < data->philo_count)
		{
			eat_limit += *data->philo_data[i]->is_alive;
			if (!check_vitals(data->philo_data[i++]))
				break ;
		}
		if (eat_limit == -data->philo_count)
			data->running = 0;
		if (!*data->philo_data[i - 1]->is_alive)
		{
			print_message(data->philo_data[i - 1], "died");
			data->running = 0;
		}
	}
	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i], NULL);
}
