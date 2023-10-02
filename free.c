/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:55:01 by mapoirie          #+#    #+#             */
/*   Updated: 2023/10/02 16:34:58 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_program *table)
{
	int	i;

	i = 0;
	while(i < table->nb_p)
	{
		free(table->philos[i]);
		i++;
	}
	free(table->lock_write);
	free(table->philos);
	free(table);

}