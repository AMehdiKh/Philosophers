/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:25:46 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/27 13:00:57 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->check);
	if (!philo->context->died)
		printf("%zu %zu is thinking\n", ft_get_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->context->check);
	return (EXIT_SUCCESS);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->context->check);
	philo->last_meal = ft_get_time();
	if (!philo->context->died)
		printf("%zu %zu has taken a fork\n", philo->last_meal - philo->start,
			philo->id);
	pthread_mutex_unlock(&philo->context->check);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->context->check);
	if (!philo->context->died)
		printf("%zu %zu is eating\n", ft_get_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->context->check);
	while (ft_get_time()
		< (philo->last_meal + philo->t_eat) && !is_dead(philo))
		;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->context->check);
	if (philo->context->died)
		return (pthread_mutex_unlock(&philo->context->check), EXIT_FAILURE);
	return (pthread_mutex_unlock(&philo->context->check), EXIT_SUCCESS);
}

int	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->check);
	if (!philo->context->died)
		printf("%zu %zu is sleeping\n", ft_get_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->context->check);
	while (ft_get_time()
		< (philo->last_meal + philo->t_eat + philo->t_sleep)
		&& !is_dead(philo))
		;
	pthread_mutex_lock(&philo->context->check);
	if (philo->context->died)
		return (pthread_mutex_unlock(&philo->context->check), EXIT_FAILURE);
	return (pthread_mutex_unlock(&philo->context->check), EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	size_t		i;

	philo = arg;
	philo->start = ft_get_time();
	philo->last_meal = philo->start;
	i = 1;
	while (1)
	{
		if (ft_thinking(philo))
			return (NULL);
		if (ft_eating(philo))
			return (NULL);
		if (ft_sleeping(philo))
			return (NULL);
		if (philo->n_times && (i >= philo->n_times))
			return (NULL);
		++i;
	}
}

int	main(int ac, char **av)
{
	t_switch	*context;
	int			i;

	context = malloc(sizeof(t_switch));
	if (!context)
		return (EXIT_FAILURE);
	if (ft_set_data(context, ac, av))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < (int)context->n_philo)
	{
		pthread_create(&context->philo[i].thread, NULL, routine,
			&context->philo[i]);
		usleep(40);
	}
	i = -1;
	while (++i < (int)context->n_philo)
		pthread_join(context->philo[i].thread, NULL);
	i = -1;
	while (++i < (int)context->n_philo)
		pthread_mutex_destroy(&context->forks[i]);
	pthread_mutex_destroy(&context->check);
	return (free(context->forks), free(context->philo), free(context),
		EXIT_SUCCESS);
}
