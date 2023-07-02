/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:25:46 by ael-khel          #+#    #+#             */
/*   Updated: 2023/07/02 18:03:25 by ael-khel         ###   ########.fr       */
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
