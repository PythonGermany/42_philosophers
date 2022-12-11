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

typedef struct s_philo
{
	int				*running;
	int				philo_count;
	int				id;
	int				*is_alive;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	pthread_mutex_t	*forks_mutex;
	int				*forks;
	pthread_mutex_t	*output;
	int				max_eat;
	int				times_eaten;
	struct timeval	last_meal;
	struct timeval	*time;
}	t_philo;

typedef struct s_data
{
	int				running;
	int				philo_count;
	pthread_t		*philos;
	t_philo			**philo_data;
	pthread_mutex_t	*forks_mutex;
	int				*forks;
	pthread_mutex_t	output;
	struct timeval	time;
}	t_data;

t_data	*init_data(char **arg);
void	print_message(t_philo *data, char *msg);
void	*philo_routine(void *data);

#endif