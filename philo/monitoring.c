/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:00:57 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/15 12:24:28 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (!*data->philo_data[i++]->is_alive)
				break ;
		}
		if (eat_limit == -data->philo_count)
			break ;
		if (!*data->philo_data[i - 1]->is_alive)
		{
			print_message(data->philo_data[i - 1], "died");
			data->running = 0;
		}
		usleep(10);
	}
	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i], NULL);
}

int	get_time_diff(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000 + \
	((double)now.tv_usec - start.tv_usec) / 1000);
}

int	check_vitals(t_philo *data)
{
	usleep(10);
	if (get_time_diff(data->last_meal) > data->tt_die)
	{
		*data->is_alive = 0;
		return (1);
	}
	return (0);
}

void	check_and_wait(t_philo *data, int time_to_wait)
{
	int	i;

	i = 0;
	while (i++ < time_to_wait * 100)
		if (check_vitals(data))
			return ;
}
