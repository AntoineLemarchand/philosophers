/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:54:52 by alemarch          #+#    #+#             */
/*   Updated: 2022/04/05 16:35:19 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->timestamp = get_timenow();
	if (!table || ac < 5 || check_args(av))
	{
		free(table);
		return (NULL);
	}
	table->nb_philo = (int)ft_atol(av[1]);
	table->time[DIE] = (unsigned)ft_atol(av[2]);
	table->time[EAT] = (unsigned)ft_atol(av[3]);
	table->time[SLEEP] = (unsigned)ft_atol(av[4]);
	if (av[5] && check_args(av + 1))
	{
		free(table);
		return (NULL);
	}
	else if (av[5])
		table->eat_amount = (int)ft_atol(av[5]);
	else
		table->eat_amount = -1;
	return (table);
}

static void	init_philo(int i, t_table *table)
{
	table->philo[i].id = i + 1;
	table->philo[i].time[DIE] = table->time[DIE];
	table->philo[i].time[EAT] = table->time[EAT];
	table->philo[i].time[SLEEP] = table->time[SLEEP];
	table->philo[i].eat_amount = table->eat_amount;
	table->philo[i].amount_eaten = 0;
	table->philo[i].timestamp = table->timestamp;
	table->philo[i].last_eat = table->timestamp;
	table->philo[i].dead = 0;
	table->philo[i].status = &table->status[i];
	table->philo[i].print = &table->print;
	table->philo[i].lfork = &table->forks[i];
	if (i == table->nb_philo - 1)
		table->philo[i].rfork = &table->forks[0];
	else
		table->philo[i].rfork = &table->forks[i + 1];
}

static int	sit_philo(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
		init_philo(i++, table);
	i = 0;
	if (table->nb_philo == 1)
		only_philo(table);
	while (table->nb_philo != 1 && i < table->nb_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &routine,
				&table->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	set_table(t_table *table, int i)
{
	table->philo = malloc((table->nb_philo) * sizeof(t_philo));
	if (!table->philo)
		return (1);
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->forks)
	{
		free(table->philo);
		return (1);
	}
	table->status = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->status)
	{
		free(table->philo);
		free(table->forks);
		return (1);
	}
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->status[i++], NULL);
	}
	pthread_mutex_init(&table->print, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = init_table(ac, av);
	if (!table || set_table(table, 0))
	{
		write(2, "Argument error\n", 15);
		return (22);
	}
	if (sit_philo(table))
		return (1);
	if (table->nb_philo != 1)
		end_check(table);
	end_program(table);
	free(table->philo);
	free(table->forks);
	free(table->status);
	free(table);
	return (0);
}
