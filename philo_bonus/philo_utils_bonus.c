/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:22:26 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/13 10:25:52 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	while ((str[i] <= '9' && str[i] >= '0') && str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > __INT_MAX__)
		return (-1);
	return (nb);
}

int	check_param(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (!av[i][0])
		{
			write(2, "Error, arguments must be only digits\n", 37);
			return (-1);
		}
		while (av[i][j])
		{
			if ((av[i][j] < 48 || av[i][j] > 57))
			{
				write(2, "Error, arguments must be only digits\n", 37);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}