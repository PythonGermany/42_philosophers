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
		if ((ft_strlen(str[i]) > 10) || *str[i] == '0')
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
	while (start >= 0)
	{
		pthread_create(data->philos + start, NULL, &philo_routine, \
			(void *)(data->philo_data + start));
		start -= 2;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6 || check_int(&argv[1]))
	{
		printf("Use: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	else
	{
		data = init_data(argv + 1);
		start_threads(data, data->philo_count - 1);
		//usleep(10);
		start_threads(data, data->philo_count - 2);
		monitor_simulation(data);
		terminate_data(data);
	}
	return (0);
}
