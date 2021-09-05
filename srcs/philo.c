/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:55:03 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/04 18:47:26 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

t_philo *ft_new_philo(int id, suseconds_t added)
{
	t_philo *ret;
	
	ret = (t_philo *)malloc(sizeof(t_philo));
	ret->id = id;
	ret->time_added = added;
	ret->n_slept = 0;
	ret->n_ate = 0;
	ret->n_thought = 0;
	ret->last_slept = 0;
	ret->last_ate = 0;
	ret->last_thought = 0;
	ret->status = 0;
	return (ret);
}

t_table	add_philo(t_table table, int id)
{
	struct timeval	tv;
	t_philo			*philo;

	gettimeofday(&tv, NULL);
	philo = ft_new_philo(id + 1, tv.tv_usec);
	ft_add_clist(&table.philos, ft_new_clist(philo));
	pthread_mutex_init(&table.forks[id], NULL);
	printf("philo %d added\n", philo->id);
	
	pthread_create(&(philo->tid), NULL, &routine, (void *)(philo));
	return (table);
}