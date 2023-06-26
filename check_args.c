/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:45:20 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/26 06:09:45 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;
	
	len = 0;
	while (s[len])
		++len;
	return (len);
}

long	ft_atol(const char *s)
{
	long long int	result;

	result = 0;
	while (*s <= 32 && *s)
		++s;
	if ((*s == '+' || *s == '-') && ft_strlen(s) != 1)
		if (*s++ == '-')
			return (printf("Error: Only positive values accepted\n"), -1);
	while (*s >= '0' && *s <= '9')
	{
		result = (result * 10) + (*s++ - 48);
		if (result > INT_MAX)
			return (printf("Error: The number is too much big\n"), -1);
	}
	while (*s <= 32 && *s)
		++s;
	if (*s)
		return (printf("Error: Only numbers accepted\n"), -1);
	if (!result)
		return (printf("Error: 0 value is not accepted\n"), -1);
	return (result);
}

int	error_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Your program should take the following arguments:\n");
		printf("* number_of_philosophers.\n");
		printf("* time_to_die (in milliseconds).\n");
		printf("* time_to_eat (in milliseconds).\n");
		printf("* time_to_sleep (in milliseconds).\n");
		printf("* number_of_times_each_philosopher_must_eat "
			"(optional argumen).\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_check_args(t_switch *context, int ac, char **av)
{
	if (error_args(ac))
		return (EXIT_FAILURE);
	context->n_philo = ft_atol(av[1]);
	context->t_die = ft_atol(av[2]);
	context->t_eat = ft_atol(av[3]);
	context->t_sleep = ft_atol(av[4]);
	if (av[5])
		context->n_times = ft_atol(av[5]);
	if (context->n_philo < 0 || context->t_die < 0 || context->t_eat < 0
		|| context->t_sleep < 0 || context->n_times < 0)
		return (EXIT_FAILURE);
	return (0);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
