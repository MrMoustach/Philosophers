/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:55:03 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/30 18:28:38 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

t_philo ft_new_philo(int id, suseconds_t added)
{
	t_philo ret;

	ret.id = id;
	ret.time_added = added;
	ret.n_slept = 0;
	ret.n_ate = 0;
	ret.n_thought = 0;
	ret.last_slept = 0;
	ret.last_ate = 0;
	ret.last_thought = 0;
	ret.status = 0;
	pthread_mutex_init(&ret.the_fork, NULL);
	pthread_create(&(ret.tid), NULL, &routine, NULL);
	return (ret);
}

t_table	add_philo(t_table table)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ft_add_clist(&table.philos, ft_new_clist(ft_new_philo(table.count++ + 1, tv.tv_usec)));
	return (table);	
}