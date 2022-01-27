/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:43:22 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/27 22:06:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philo;
	int		amount_eaten;

	amount_eaten = 0;
	philo = (t_philo *)args;
	while (amount_eaten < philo->eat_amount)
	{
		printf("%u philo %i is eating\n", get_timenow(), philo->id);
		usleep(philo->t_eat * 1000);
		amount_eaten++;
		printf("%u philo %i is sleeping\n", get_timenow(), philo->id);
		usleep(philo->t_sleep * 1000);
		printf("%u philo %i is thinking\n", get_timenow(), philo->id);
		usleep(100000);
	}
	return (NULL);
}
