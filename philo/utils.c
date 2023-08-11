/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:25:46 by ael-khel          #+#    #+#             */
/*   Updated: 2023/08/11 18:31:37 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->context->print);
	if (philo->context->died)
		return (pthread_mutex_unlock(&philo->context->print), EXIT_FAILURE);
	printf("%zu %zu %s\n", ft_get_time() - philo->start, philo->id, status);
	return (pthread_mutex_unlock(&philo->context->print), EXIT_SUCCESS);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(t_philo *philo, size_t last_action,
	size_t current_action, int eating)
{
	while ((ft_get_time() - last_action) < current_action)
	{
		if ((ft_get_time() - philo->last_meal) >= philo->t_die)
		{
			pthread_mutex_lock(&philo->context->print);
			philo->context->died = 1;
			pthread_mutex_unlock(&philo->context->print);
			if (eating)
				return (pthread_mutex_unlock(philo->r_fork),
					pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
	}
	if (eating)
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	ft_destroy_data(t_switch *context)
{
	int	i;

	i = -1;
	while (++i < (int)context->n_philo)
		pthread_join(context->philo[i].thread, NULL);
	i = -1;
	while (++i < (int)context->n_philo)
		pthread_mutex_destroy(&context->forks[i]);
	pthread_mutex_destroy(&context->meal);
	pthread_mutex_destroy(&context->print);
	free(context->forks);
	free(context->philo);
	free(context);
}
