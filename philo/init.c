/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:27:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/27 13:01:20 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_set_data(t_switch *context, int ac, char **av)
{
	int	i;

	if (ft_check_args(memset(context, 0, sizeof(t_switch)), ac, av))
		return (free(context), EXIT_FAILURE);
	context->philo = malloc(sizeof(t_philo) * context->n_philo);
	if (!context->philo)
		return (free(context), EXIT_FAILURE);
	context->forks = malloc(sizeof(pthread_mutex_t) * context->n_philo);
	if (!context->forks)
		return (free(context->philo), free(context), EXIT_FAILURE);
	i = -1;
	while (++i < (int)context->n_philo)
		pthread_mutex_init(&context->forks[i], NULL);
	pthread_mutex_init(&context->check, NULL);
	ft_init_data(context);
	return (EXIT_SUCCESS);
}

void	ft_init_data(t_switch *context)
{
	int	i;

	i = -1;
	while (++i < (int)context->n_philo)
	{
		context->philo[i].id = i + 1;
		context->philo[i].n_philo = context->n_philo;
		context->philo[i].t_die = context->t_die;
		context->philo[i].t_eat = context->t_eat;
		context->philo[i].t_sleep = context->t_sleep;
		context->philo[i].n_times = context->n_times;
		context->philo[i].context = context;
		context->philo[i].l_fork = &context->forks[i];
		context->philo[i].r_fork = &context->forks[(i + 1) % context->n_philo];
	}
}

int	is_dead(t_philo *philo)
{
	size_t	death_time;

	death_time = ft_get_time();
	if (death_time >= (philo->last_meal + philo->t_die))
	{
		pthread_mutex_lock(&philo->context->check);
		if (!philo->context->died)
		{
			philo->context->died = 1;
			printf("%zu %zu died\n", death_time - philo->start, philo->id);
		}
		return (pthread_mutex_unlock(&philo->context->check), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
