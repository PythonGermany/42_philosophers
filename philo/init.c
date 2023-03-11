/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:17:46 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/10 02:17:46 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_diff(struct timeval *start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start->tv_sec) * 1000 + \
	(double)(now.tv_usec - start->tv_usec) / 1000);
}

static int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb * 10 + str[i] - '0' < nb && sign == 1)
			return (-1);
		else if (nb * 10 + str[i] - '0' < nb && sign == -1)
			return (0);
		nb = nb * 10 + str[i++] - '0';
	}
	return (nb * sign);
}

static void	init_philo(t_data *data, char **arg, int i)
{
	data->philo_data[i].running = &data->running;
	data->philo_data[i].philo_count = data->philo_count;
	data->philo_data[i].id = i + 1;
	data->philo_data[i].tt_die = ft_atoi(arg[1]);
	data->philo_data[i].tt_eat = ft_atoi(arg[2]);
	data->philo_data[i].tt_sleep = ft_atoi(arg[3]);
	data->philo_data[i].forks = data->forks;
	if (arg[4] != NULL)
		data->philo_data[i].max_eat = ft_atoi(arg[4]);
	else
		data->philo_data[i].max_eat = 0;
	data->philo_data[i].times_eaten = 0;
	data->philo_data[i].output = &data->output;
	data->philo_data[i].time = &data->time;
	data->philo_data[i].last_meal = 0;
}

t_data	*init_data(char **arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->running = 1;
	data->philo_count = ft_atoi(arg[0]);
	pthread_mutex_init(&data->output, NULL);
	data->philo_threads = \
		(pthread_t *)malloc(ft_atoi(arg[0]) * sizeof(pthread_t));
	data->philo_data = (t_philo *)malloc(ft_atoi(arg[0]) * sizeof(t_philo));
	data->forks = \
		(pthread_mutex_t *)malloc(ft_atoi(arg[0]) * sizeof(pthread_mutex_t));
	if (data->philo_threads == NULL || data->philo_data == NULL \
		|| data->forks == NULL)
		return (data);
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	gettimeofday(&data->time, NULL);
	i = -1;
	while (++i < data->philo_count)
		init_philo(data, arg, i);
	return (data);
}

void	terminate_data(t_data *data)
{
	if (data->philo_threads != NULL && data->philo_data != NULL \
		&& data->forks != NULL)
		while (data->philo_count-- > 0)
			pthread_mutex_destroy(data->forks + data->philo_count);
	pthread_mutex_destroy(&data->output);
	if (data->philo_threads != NULL)
		free(data->philo_threads);
	else
		printf("ERROR: data->philo_threads malloc fail\n");
	if (data->philo_data != NULL)
		free(data->philo_data);
	else
		printf("ERROR: data->philo_data malloc fail\n");
	if (data->forks != NULL)
		free(data->forks);
	else
		printf("ERROR: data->forks malloc fail\n");
	free(data);
}
