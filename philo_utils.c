/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:20:58 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/09 17:06:00 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
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

void	assign_spoon(t_program *table, t_philo **philo, int i)
{
	if (i % 2 == 0)
	{
		philo[i]->spoon[0] = i;
		if (i == 0)
			philo[i]->spoon[1] = table->nb_p - 1;
		else
			philo[i]->spoon[1] = i - 1;
	}
	else if (i % 2 != 0)
	{
		philo[i]->spoon[0] = i - 1;
		philo[i]->spoon[1] = i;
	}
}
