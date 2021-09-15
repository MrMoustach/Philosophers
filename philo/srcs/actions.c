/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:15:49 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/15 14:16:04 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

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
