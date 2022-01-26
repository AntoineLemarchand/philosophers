/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:54:52 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/26 11:21:51 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + nptr[i++] - 48;
	if (result >= 0)
		return (result * sign);
	else
		return (-1);
}

t_table	*set_table(int ac, char **av)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (!table || ac < 5 || ft_atol(av[1]) <= 0 || ft_atol(av[2]) < 0
		|| ft_atol(av[3]) < 0 || ft_atol(av[4]) < 0)
	{
		free(table);
		return (NULL);
	}
	table->nb_philo = (unsigned int)ft_atol(av[1]);
	table->t_die = (unsigned int)ft_atol(av[2]);
	table->t_eat = (unsigned int)ft_atol(av[3]);
	table->t_sleep = (unsigned int)ft_atol(av[4]);
	if (av[5] && (unsigned int)ft_atol(av[5]) < 0)
	{
		free(table);
		return (NULL);
	}
	else if (av[5])
		table->eat_amount = (unsigned int)ft_atol(av[5]);
	else
		table->eat_amount = 0;
	return (table);
}

int	main(int ac, char **av)
{
	t_table *table;

	table = set_table(ac, av);
	if (!table)
	{
		write(2, "Argument error\n", 15);
		return (22);
	}
	printf("nb_philo: %u\n", table->nb_philo);
	printf("t_die: %u\n", table->t_die);
	printf("t_eat: %u\n", table->t_eat);
	printf("t_sleep: %u\n", table->t_sleep);
	printf("eat_amount: %u\n", table->eat_amount);
	free(table);
	return (0);
}
