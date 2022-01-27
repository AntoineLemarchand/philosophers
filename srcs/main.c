/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:54:52 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/27 22:03:45 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_timenow(void)
{
	struct timeval	curr;

	if (gettimeofday(&curr, NULL) < 0)
		return (0);
	return (curr.tv_sec * 1000 + curr.tv_usec / 1000);
}

t_table	*init_table(int ac, char **av)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	table->timestamp = get_timenow();
	if (!table || ac < 5 || ft_atol(av[1]) <= 0 || ft_atol(av[2]) <= 0
		|| ft_atol(av[3]) <= 0 || ft_atol(av[4]) <= 0)
	{
		free(table);
		return (NULL);
	}
	table->nb_philo = (int)ft_atol(av[1]);
	table->t_die = (unsigned int)ft_atol(av[2]);
	table->t_eat = (unsigned int)ft_atol(av[3]);
	table->t_sleep = (unsigned int)ft_atol(av[4]);
	if (av[5] && (int)ft_atol(av[5]) <= 0)
	{
		free(table);
		return (NULL);
	}
	else if (av[5])
		table->eat_amount = (int)ft_atol(av[5]);
	else
		table->eat_amount = 0;
	return (table);
}

int	sit_philo(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philo[i].id = i;
		table->philo[i].lfork = table->forks[i];
		table->philo[i].t_die = table->t_die;
		table->philo[i].t_eat = table->t_eat;
		table->philo[i].t_sleep = table->t_sleep;
		table->philo[i].eat_amount = table->eat_amount;
		if (i < table->nb_philo - 1)
			table->philo[i].rfork = table->forks[i + 1];
		else
			table->philo[i].rfork = table->forks[0];
		if (pthread_create(&table->philo[i].thread, NULL, &routine,
				&table->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	set_table(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc((table->nb_philo + 1) * sizeof(t_philo));
	if (!table->philo)
		return (1);
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->forks)
	{
		free(table->philo);
		return (1);
	}
	while (i < table->nb_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
	if (sit_philo(table))
		return (1);
	while (i >= 0)
	{
		pthread_join(table->philo[i].thread, NULL);
		i--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table *table;

	table = init_table(ac, av);
	if (!table || set_table(table))
	{
		write(2, "Argument error\n", 15);
		return (22);
	}
	free(table->philo);
	free(table->forks);
	free(table);
	return (0);
}
