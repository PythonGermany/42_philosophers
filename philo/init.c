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

static t_philo	init_philo(t_data *data, char **arg, int id)
{
	t_philo	philo;

	philo.running = &data->running;
	philo.philo_count = data->philo_count;
	philo.id = id;
	philo.is_done = 1;
	philo.tt_die = ft_atoi(arg[1]);
	philo.tt_eat = ft_atoi(arg[2]);
	philo.tt_sleep = ft_atoi(arg[3]);
	philo.forks = data->forks;
	if (arg[4] != NULL)
		philo.max_eat = ft_atoi(arg[4]);
	else
		philo.max_eat = 0;
	philo.times_eaten = 0;
	philo.output = &data->output;
	philo.time = &data->time;
	gettimeofday(&philo.last_meal, NULL);
	return (philo);
}

t_data	*init_data(char **arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	data->running = 1;
	data->philo_count = ft_atoi(arg[0]);
	data->philos = (pthread_t *)malloc(ft_atoi(arg[0]) * sizeof(pthread_t));
	data->philo_data = (t_philo *)malloc(ft_atoi(arg[0]) * sizeof(t_philo));
	data->forks = \
	(pthread_mutex_t *)malloc(ft_atoi(arg[0]) * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->output, NULL);
	gettimeofday(&data->time, NULL);
	i = -1;
	while (++i < data->philo_count)
		data->philo_data[i] = init_philo(data, arg, i + 1);
	return (data);
}

void	terminate_data(t_data *data)
{
	while (--data->philo_count >= 0)
		pthread_mutex_destroy(&data->forks[data->philo_count]);
	pthread_mutex_destroy(&data->output);
	free(data->philos);
	free(data->philo_data);
	free(data->forks);
	free(data);
}
