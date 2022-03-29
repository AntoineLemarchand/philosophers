/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:34:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 15:01:53 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	end_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		pthread_detach(table->philo[i++].thread);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philo[i].lfork);
		pthread_mutex_destroy(&table->philo[i].rfork);
		pthread_mutex_destroy(&table->status[i]);
		i++;
	}
}

int	check_status(int i, int ate, t_table *table)
{
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philo[i].status_mutex);
		if (table->philo[i].status)
		{
			if (table->philo[i].status == DEAD)
			{
				putstatus(i, "has died");
				return (1);
			}
			else
				ate++;
		}
		if (ate == table->nb_philo)
		{
			pthread_mutex_unlock(&table->philo[i].status_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i].status_mutex);
		i++;
	}
	return (0);
}

void	end_check(t_table *table)
{
	while (1)
	{
		if (check_status(0, 0, table))
			break ;
	}
}
