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
	data->philo_data[i].tt_die = ft_atoi(arg[1]) * 1000;
	data->philo_data[i].tt_eat = ft_atoi(arg[2]) * 1000;
	data->philo_data[i].tt_sleep = ft_atoi(arg[3]) * 1000;
	data->philo_data[i].forks = data->forks;
	data->philo_data[i].forks_state = data->forks_state;
	if (arg[4] != NULL)
		data->philo_data[i].max_eat = ft_atoi(arg[4]);
	else
		data->philo_data[i].max_eat = 0;
	data->philo_data[i].times_eaten = 0;
	data->philo_data[i].output = &data->output;
	data->philo_data[i].mutex_running = &data->mutex_running;
	data->philo_data[i].time = &data->time;
	data->philo_data[i].last_meal = 0;
}

static void	allocate_data_members(t_data *data, char **arg)
{
	data->philo_threads = \
		(pthread_t *)malloc(ft_atoi(arg[0]) * sizeof(pthread_t));
	data->philo_data = (t_philo *)malloc(ft_atoi(arg[0]) * sizeof(t_philo));
	data->forks = \
		(pthread_mutex_t *)malloc(ft_atoi(arg[0]) * sizeof(pthread_mutex_t));
	data->forks_state = (int *)malloc(ft_atoi(arg[0]) * sizeof(int));
}

t_data	*init_data(char **arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->running = 0;
	data->philo_count = ft_atoi(arg[0]);
	pthread_mutex_init(&data->output, NULL);
	pthread_mutex_init(&data->mutex_running, NULL);
	allocate_data_members(data, arg);
	if (data->philo_threads == NULL || data->philo_data == NULL \
		|| data->forks == NULL || data->forks_state == NULL)
		return (data);
	i = -1;
	while (++i < data->philo_count)
	{
		data->forks_state[i] = 0;
		pthread_mutex_init(&data->forks[i], NULL);
	}
	gettimeofday(&data->time, NULL);
	i = -1;
	while (++i < data->philo_count)
		init_philo(data, arg, i);
	return (data);
}

void	terminate_data(t_data *data)
{
	if (data->philo_threads != NULL && data->philo_data != NULL \
		&& data->forks != NULL && data->forks_state != NULL)
		while (data->philo_count-- > 0)
			pthread_mutex_destroy(data->forks + data->philo_count);
	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->mutex_running);
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
	if (data->forks_state != NULL)
		free(data->forks_state);
	else
		printf("ERROR: data->forks_state malloc fail\n");
	free(data);
}
