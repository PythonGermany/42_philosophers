/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:22:25 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/10 02:22:25 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef unsigned long long	t_llu;

typedef struct s_philo
{
	int				*running;
	int				philo_count;
	int				id;
	t_llu			tt_die;
	t_llu			tt_eat;
	t_llu			tt_sleep;
	pthread_mutex_t	*forks;
	int				*forks_state;
	pthread_mutex_t	*output;
	pthread_mutex_t	*mutex_running;
	int				max_eat;
	int				times_eaten;
	int				last_meal;
	struct timeval	eat;
	struct timeval	sleep;
	struct timeval	*time;
}	t_philo;

typedef struct s_data
{
	int				running;
	int				philo_count;
	pthread_t		*philo_threads;
	t_philo			*philo_data;
	pthread_mutex_t	*forks;
	int				*forks_state;
	pthread_mutex_t	output;
	pthread_mutex_t	mutex_running;
	struct timeval	time;
}	t_data;

t_data	*init_data(char **arg);
void	terminate_data(t_data *data);
void	*philo_routine(void *data);
t_llu	time_diff(struct timeval *start);

#endif