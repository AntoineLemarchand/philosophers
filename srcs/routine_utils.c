/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:34:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 13:52:44 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	end_check(t_table *table)
{
	int	i;
	int end;
	int ate;

	end = 0;
	ate = 0;
	while (!end)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&table->philo[i].status_mutex);
			if (table->philo[i].status)
			{
				if (table->philo[i].status == DEAD)
				{
					putstatus(i, "has died");
					end = 1;
					pthread_mutex_unlock(&table->philo[i].status_mutex);
					break;
				}
				else
					ate++;
			}
			if (ate == table->nb_philo)
			{
				end = 1;
				pthread_mutex_unlock(&table->philo[i].status_mutex);
				break;
			}
			pthread_mutex_unlock(&table->philo[i].status_mutex);
			i++;
		}
	}
	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philo[i++].thread, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philo[i].lfork);
		pthread_mutex_destroy(&table->philo[i].rfork);
		pthread_mutex_destroy(&table->status[i]);
		i++;
	}
	return (end);
}
