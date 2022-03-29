/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:57:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 16:22:43 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
