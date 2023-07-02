/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:27:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/07/02 18:02:41 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_data(t_switch *context)
{
	int	i;

	i = -1;
	while (++i < (int)context->n_philo)
	{
		context->philo[i].id = i + 1;
		context->philo[i].life = 1;
		context->philo[i].n_philo = context->n_philo;
		context->philo[i].t_die = context->t_die;
		context->philo[i].t_eat = context->t_eat;
		context->philo[i].t_sleep = context->t_sleep;
		context->philo[i].n_times = context->n_times;
		context->philo[i].l_fork = &context->forks[i];
		context->philo[i].r_fork = &context->forks[(i + 1) % context->n_philo];
		context->philo[i].context = context;
	}
}

int	ft_set_data(t_switch *context)
{
	int	i;

	context->philo = malloc(sizeof(t_philo) * context->n_philo);
	if (!context->philo)
		return (free(context), EXIT_FAILURE);
	context->forks = malloc(sizeof(pthread_mutex_t) * context->n_philo);
	if (!context->forks)
		return (free(context->philo), free(context), EXIT_FAILURE);
	i = -1;
	while (++i < (int)context->n_philo)
		pthread_mutex_init(&context->forks[i], NULL);
	pthread_mutex_init(&context->meal, NULL);
	pthread_mutex_init(&context->print, NULL);
	ft_init_data(context);
	return (EXIT_SUCCESS);
}
