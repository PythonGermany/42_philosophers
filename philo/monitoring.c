/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:00:57 by rburgsta          #+#    #+#             */
/*   Updated: 2023/03/10 17:01:41 by rburgsta         ###   ########.fr       */
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

int	check_vitals(t_philo *data)
{
	if (get_time_diff(data->time) - data->last_meal > data->tt_die)
		print_message(data, " died", 1);
	return (*data->running);
}

void	monitor_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i], NULL);
}

void	print_message(t_philo *data, char *msg, int disable_output)
{
	pthread_mutex_lock(data->output);
	if (*data->running)
		printf("%d %d %s\n", get_time_diff(data->time), data->id, msg);
	if (disable_output)
		*data->running = 0;
	pthread_mutex_unlock(data->output);
}
