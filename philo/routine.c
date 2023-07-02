/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:07:40 by ael-khel          #+#    #+#             */
/*   Updated: 2023/07/02 17:55:51 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_thinking(t_philo *philo)
{
	if (ft_print(philo, "is thinking"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->context->meal);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->context->meal);
	if (ft_print(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
	if (philo->n_philo == 1)
		return (pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
	pthread_mutex_lock(philo->r_fork);
	if (ft_print(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_eating(t_philo *philo)
{
	if (ft_print(philo, "is eating"))
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
	while (ft_get_time() - philo->last_meal < philo->t_eat)
	{
		if (ft_get_time() - philo->last_meal >= philo->t_die)
		{
			pthread_mutex_lock(&philo->context->print);
			philo->context->died = 1;
			pthread_mutex_unlock(&philo->context->print);
			return (pthread_mutex_unlock(philo->r_fork),
				pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
		}
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (EXIT_SUCCESS);
}

int	ft_sleeping(t_philo *philo)
{
	if (ft_print(philo, "is sleeping"))
		return (EXIT_FAILURE);
	while (ft_get_time() - (philo->last_meal + philo->t_eat) < philo->t_sleep)
	{
		if (ft_get_time() - philo->last_meal >= philo->t_die)
		{
			pthread_mutex_lock(&philo->context->print);
			philo->context->died = 1;
			pthread_mutex_unlock(&philo->context->print);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_eat_times(t_philo *philo, size_t i)
{
	if (philo->n_times && (i >= philo->n_times))
	{
		pthread_mutex_lock(&philo->context->meal);
		philo->life = 0;
		++philo->context->total_eat;
		pthread_mutex_unlock(&philo->context->meal);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
