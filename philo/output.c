/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:44:13 by rburgsta          #+#    #+#             */
/*   Updated: 2023/03/13 14:52:43 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *data, char *msg, int disable_output)
{
	pthread_mutex_lock(data->output);
	if (*data->running)
		printf("%d %d %s\n", time_diff(data->time), data->id, msg);
	if (disable_output)
		*data->running = 0;
	pthread_mutex_unlock(data->output);
}
