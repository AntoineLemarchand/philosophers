/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:57:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 16:56:43 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_onlydigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_onlydigit(av[i]))
			return (1);
		i++;
	}
	if (ft_atol(av[1]) <= 0 || ft_atol(av[2]) <= 0
		|| ft_atol(av[3]) <= 0 || ft_atol(av[4]) <= 0)
		return (1);
	else if (ft_atol(av[1]) >= 2147483848 || ft_atol(av[2]) >= 2147483848
		|| ft_atol(av[3]) >= 2147483848 || ft_atol(av[4]) >= 2147483848)
		return (1);
	return (0);
}

void	putstatus(int i, char *s)
{
	printf("%u %i %s\n", get_timenow(), i, s);
}

unsigned int	get_timenow(void)
{
	struct timeval	curr;

	if (gettimeofday(&curr, NULL) < 0)
		return (0);
	return (curr.tv_sec * 1000 + curr.tv_usec / 1000);
}

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
