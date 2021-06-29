/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:55:03 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/29 11:12:09 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

t_philo ft_new_philo(int id)
{
	t_philo ret;

	ret.id = id;
	ret.n_slept = 0;
	ret.n_ate = 0;
	ret.n_thought = 0;
	ret.last_slept = 0;
	ret.last_ate = 0;
	ret.last_thought = 0;
	ret.status = 0;
	return (ret);
}

t_table	add_philo(t_table table)
{
	ft_add_clist(&table.philos, ft_new_clist(ft_new_philo(table.count++)));
	return (table);	
}