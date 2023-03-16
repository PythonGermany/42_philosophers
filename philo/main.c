/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:54:57 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/09 21:54:57 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_llu	time_diff(struct timeval *start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start->tv_sec) * 1000000 + \
	(now.tv_usec - start->tv_usec));
}

static int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	check_int(char **str)
{
	int	i;
	int	i2;

	i = -1;
	while (str[++i] != NULL)
	{
		if ((ft_strlen(str[i]) > 10) || *str[i] == '0' || *str[i] == '\0')
			return (1);
		i2 = -1;
		while (++i2 < ft_strlen(str[i]))
			if (str[i][i2] < '0' || str[i][i2] > '9' \
			|| (str[i][i2] > "2147483647"[i2] && ft_strlen(str[i]) > 9))
				return (1);
	}
	return (0);
}

static void	start_threads(t_data *data, int start)
{
	while (start-- > 0)
	{
		if ((start + 1) % 2)
		{
			data->forks_state[start] = start + 1;
			if (data->philo_count > 1)
				data->forks_state[(start + 1) % data->philo_count] = start + 1;
		}
		pthread_create(data->philo_threads + start, NULL, &philo_routine, \
			(void *)(data->philo_data + start));
	}
	pthread_mutex_lock(&data->mutex_running);
	data->running = 1;
	gettimeofday(&data->time, NULL);
	pthread_mutex_unlock(&data->mutex_running);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (argc < 5 || argc > 6 || check_int(argv + 1))
	{
		printf("Use: %s number_of_philosophers time_die time_eat", argv[0]);
		printf(" time_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	else
	{
		data = init_data(argv + 1);
		if (data == NULL)
			return (printf("ERROR: data malloc fail\n"), 1);
		if (data->philo_threads == NULL || data->philo_data == NULL \
			|| data->forks == NULL || data->forks_state == NULL)
			return (terminate_data(data), 1);
		start_threads(data, data->philo_count);
		i = -1;
		while (++i < data->philo_count)
			pthread_join(data->philo_threads[i], NULL);
		terminate_data(data);
	}
	return (0);
}
