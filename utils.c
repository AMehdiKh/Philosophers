/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:16:17 by ael-khel          #+#    #+#             */
/*   Updated: 2023/06/19 21:44:04 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}

unsigned int	ft_atol(const char *s)
{
	unsigned int	result;

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
	return (result);
}
