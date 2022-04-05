/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:00:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/04/05 16:09:54 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define EAT 0
# define SLEEP 1
# define DIE 2

# define DEAD 1
# define FULL 2

typedef struct s_philo
{
	int				id;
	unsigned int	time[3];
	long			timestamp;
	pthread_t		thread;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*status;
	pthread_mutex_t	*print;
	long			last_eat;
	int				eat_amount;
	int				amount_eaten;
	int				dead;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*status;
	pthread_mutex_t	print;
	int				nb_philo;
	unsigned int	time[3];
	int				eat_amount;
	unsigned int	timestamp;
}	t_table;

// utils.c
long			ft_atol(const char *nptr);
unsigned int	get_timenow(void);
void			putstatus(t_philo *philo, char *msg);
int				check_args(char	**av);
// routine_utils.c
void			end_program(t_table *table);
void			end_check(t_table *table);
// routine.c
void			only_philo(t_table *table);
void			*routine(void *data);
#endif
