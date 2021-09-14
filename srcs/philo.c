/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:55:03 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/14 18:35:43 by iharchi          ###   ########.fr       */
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
// TODO: change this
t_table	add_philo(t_table table, int id)
{
	struct timeval	tv;
	t_philo			*philo;

	gettimeofday(&tv, NULL);
	philo = ft_new_philo(id + 1, tv.tv_usec);
	ft_add_clist(&table.philos, ft_new_clist(philo));
	pthread_mutex_init(&table.forks[id], NULL);
	// pthread_create(&(philo->tid), NULL, &routine, (void *)(philo));
	return (table);
}

void	philo_think(t_philo *philo)
{
	philo->status = THINKING;
	express(*philo, get_time());
	philo->last_thought = get_time();
	philo->n_thought++;
}

void	philo_sleep(t_philo *philo)
{
	philo->status = SLEEPING;
	express(*philo, get_time());
	philo->last_slept = get_time();
	n_sleep(g_table.time_to_sleep);
	philo->n_slept++;
}

void	philo_eat(t_philo *philo)
{
	size_t	time;
	int		fork_index;
	
	fork_index = philo->id % g_table.count;
	pthread_mutex_lock(&g_table.forks[philo->id - 1]);
	philo->status = FORK_1;
	express(*philo, get_time());
	pthread_mutex_lock(&g_table.forks[fork_index]);
	philo->status = FORK_2;
	express(*philo, get_time());
	philo->status = EATING;
	express(*philo, get_time());
	philo->last_ate = get_time();
	n_sleep(g_table.time_to_eat);
	philo->n_ate++;
	pthread_mutex_unlock(&g_table.forks[philo->id - 1]);
	pthread_mutex_unlock(&g_table.forks[fork_index]);
}