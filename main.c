/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:20:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/15 14:10:43 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int	main(int ac, char **av)
{
	g_table = init_table(ac, av);
	if (g_table.error)
	{
		write (2, "Error\n", 7);
		return (1);
	}
	start_simulation();
	return (supervisor());
}
