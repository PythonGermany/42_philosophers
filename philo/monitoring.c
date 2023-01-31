/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:00:57 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/31 15:24:08 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_diff(struct timeval *start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start->tv_sec) * 1000 + \
	(double)(now.tv_usec - start->tv_usec) / 1000);
}

static int	check_vitals(t_philo *data)
{
	if (get_time_diff(data->time) - data->last_meal > data->tt_die)
	{
		*data->running = 0;
		data->is_done = 0;
		print_message(data, "died", 1);
		return (0);
	}
	return (1);
}

void	monitor_simulation(t_data *data)
{
	int	eat_limit;
	int	i;

	while (data->running)
	{
		i = -1;
		eat_limit = 0;
		while (++i < data->philo_count)
		{
			if (check_vitals(data->philo_data + i) == 0)
				break ;
			eat_limit += data->philo_data[i].is_done;
		}
		if (eat_limit == 0)
			data->running = 0;
	}
	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i], NULL);
}

void	print_message(t_philo *data, char *msg, int print)
{
	pthread_mutex_lock(data->output);
	if (*data->running || print)
		printf("%d %d %s\n", get_time_diff(data->time), data->id, msg);
	// else
	// 	printf("DEBUG: %d %d %s\n", get_time_diff(data->time), data->id, msg);
	pthread_mutex_unlock(data->output);
}
