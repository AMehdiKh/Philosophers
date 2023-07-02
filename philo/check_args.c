/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:45:20 by ael-khel          #+#    #+#             */
/*   Updated: 2023/07/02 12:16:15 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_args(int ac)
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

size_t	ft_atol(const char *s)
{
	size_t	result;

	result = 0;
	while (*s <= 32 && *s)
		++s;
	if ((*s == '+' || *s == '-'))
		if (*s++ == '-')
			return (printf("Error: Only positive values accepted.\n"), 0);
	while (*s >= '0' && *s <= '9')
	{
		result = (result * 10) + (*s++ - 48);
		if (result > INT_MAX)
			return (printf("Error: The number is too much big.\n"), 0);
	}
	while (*s <= 32 && *s)
		++s;
	if (*s)
		return (printf("Error: Only numbers accepted.\n"), 0);
	if (!result)
		return (printf("Error: '0' is not accepted.\n"), 0);
	return (result);
}

int	ft_check_args(t_switch *context, int ac, char **av)
{
	if (ft_error_args(ac))
		return (EXIT_FAILURE);
	context->n_philo = ft_atol(av[1]);
	context->t_die = ft_atol(av[2]);
	context->t_eat = ft_atol(av[3]);
	context->t_sleep = ft_atol(av[4]);
	if (context->n_philo == 0 || context->t_die == 0 || context->t_eat == 0
		|| context->t_sleep == 0)
		return (EXIT_FAILURE);
	if (av[5])
	{
		context->n_times = ft_atol(av[5]);
		if (context->n_times == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
