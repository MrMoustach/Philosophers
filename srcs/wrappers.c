/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:00:36 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/14 19:02:18 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

/** 
 * @brief  function that get time of day in miliseconds
 * @note   
 * @param  Void: 
 * @returns size_t time of day in miliseconds
 */
size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((tv.tv_usec +  (tv.tv_sec * 1000000))) / 1000) - g_table.started_at );
}

/** 
 * @brief  wrapper function for usleep and corrects a 60ms innacuraccy.
 * @note   
 * @param  size_t time to sleep in miliseconds: 
 * @retval None
 */
void	n_sleep(size_t time)
{
	ssize_t	actual_sleep;
	ssize_t	curr;

	curr = get_time();
	actual_sleep = time - 60;
	usleep(actual_sleep * 1000);
	while ((get_time() - curr) < (time))
	{
	}
}
