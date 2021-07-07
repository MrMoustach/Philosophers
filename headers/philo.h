/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:01:39 by zed               #+#    #+#             */
/*   Updated: 2021/07/07 09:19:53 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include "clist.h"
# include "types.h"
# include "utils.h"

t_table	add_philo(t_table table);
t_philo *ft_new_philo(int id, suseconds_t added);
void *routine(void *content);

pthread_mutex_t lock;
#endif